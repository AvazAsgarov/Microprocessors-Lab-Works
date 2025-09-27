// Digital Dice Roller with 7-Segment Display - FIXED VERSION
// Pin mapping
const int segPins[7] = {3, 4, 5, 6, 7, 8, 9}; // a, b, c, d, e, f, g
const int buttonPin   = 2;   // button (use INPUT_PULLUP)
const int seedPin     = A0;  // analog pin used to seed random (floating)

// Timing
const unsigned long DEBOUNCE_MS = 50;
const unsigned long LONG_PRESS_MS = 2000;
const unsigned long ROLL_ANIMATION_MS = 600;
const unsigned long ANIM_STEP_MS = 60;

// Stats
unsigned long totalRolls = 0;
unsigned long counts[6] = {0,0,0,0,0,0};

// 7-seg patterns for digits 1..6 (Common Cathode)
const uint8_t digitsPatterns[6][7] = {
  // a, b, c, d, e, f, g
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}  // 6
};

void setup() {
  // Segment pins as outputs
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
    digitalWrite(segPins[i], LOW);
  }

  // Button with internal pull-up
  pinMode(buttonPin, INPUT_PULLUP);

  // Seed random number generator
  randomSeed(analogRead(seedPin));

  // Serial communication
  Serial.begin(9600);
  while (!Serial) { /* wait */ }
  Serial.println("Dice Roller started!");
  Serial.println("Short press = roll dice");
  Serial.println("Long press = show statistics");
  
  // Display initial "6" to show the display works
  displayDigit(6);
  delay(1000);
  displayDigit(1); // Start with 1
  
  printStats();
}

void loop() {
  static int lastButtonState = HIGH;
  static int buttonState = HIGH;
  static unsigned long lastDebounceTime = 0;
  static unsigned long pressStartTime = 0;
  static bool longPressHandled = false;

  // Read button
  int reading = digitalRead(buttonPin);

  // Debounce
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_MS) {
    // Button state has stabilized
    if (reading != buttonState) {
      buttonState = reading;
      
      if (buttonState == LOW) {
        // Button just pressed
        pressStartTime = millis();
        longPressHandled = false;
        Serial.println("Button pressed...");
      } else {
        // Button just released
        if (!longPressHandled) {
          unsigned long pressDuration = millis() - pressStartTime;
          
          if (pressDuration >= LONG_PRESS_MS) {
            Serial.println("Long press detected!");
            printStats();
          } else {
            Serial.println("Short press - rolling dice!");
            performRoll();
          }
        }
      }
    }
    
    // Check for ongoing long press
    if (buttonState == LOW && !longPressHandled) {
      if (millis() - pressStartTime >= LONG_PRESS_MS) {
        Serial.println("Long press detected!");
        printStats();
        longPressHandled = true;
      }
    }
  }

  lastButtonState = reading;
}

// Display digit 1-6 on 7-segment display
void displayDigit(int num) {
  if (num < 1 || num > 6) {
    // Turn off all segments for invalid numbers
    for (int i = 0; i < 7; i++) {
      digitalWrite(segPins[i], LOW);
    }
    return;
  }
  
  int idx = num - 1;
  for (int s = 0; s < 7; s++) {
    digitalWrite(segPins[s], digitsPatterns[idx][s] ? HIGH : LOW);
  }
}

// Perform dice roll with animation
void performRoll() {
  Serial.println("Rolling...");
  
  // Rolling animation
  unsigned long startTime = millis();
  while (millis() - startTime < ROLL_ANIMATION_MS) {
    int randomFace = random(1, 7);
    displayDigit(randomFace);
    delay(ANIM_STEP_MS);
  }

  // Final result
  int result = random(1, 7);
  displayDigit(result);

  // Update statistics
  counts[result - 1]++;
  totalRolls++;

  // Print results
  Serial.print("Roll #");
  Serial.print(totalRolls);
  Serial.print(": ");
  Serial.println(result);

  Serial.print("Counts [1-6]: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(counts[i]);
    if (i < 5) Serial.print(", ");
  }
  Serial.println();

  Serial.print("Percentages: ");
  for (int i = 0; i < 6; i++) {
    float percentage = totalRolls > 0 ? (counts[i] * 100.0 / totalRolls) : 0.0;
    Serial.print(percentage, 1);
    Serial.print("%");
    if (i < 5) Serial.print(", ");
  }
  Serial.println();
  Serial.println("------------------------");
}

void printStats() {
  Serial.println("\n=== DICE STATISTICS ===");
  Serial.print("Total rolls: ");
  Serial.println(totalRolls);
  
  if (totalRolls == 0) {
    Serial.println("No rolls yet!");
  } else {
    Serial.println("Face | Count | Percentage");
    Serial.println("----- ----- ----------");
    for (int i = 0; i < 6; i++) {
      float percentage = (counts[i] * 100.0) / totalRolls;
      Serial.print("  ");
      Serial.print(i + 1);
      Serial.print("  |  ");
      Serial.print(counts[i]);
      Serial.print("   |   ");
      Serial.print(percentage, 1);
      Serial.println("%");
    }
  }
  Serial.println("=======================\n");
}
