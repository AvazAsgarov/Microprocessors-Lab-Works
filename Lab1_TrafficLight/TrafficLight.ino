// Traffic Light with Pedestrian Lights, Musical Buzzer, and Serial messages: "STOP", "WAIT", "GO"

// Pin definitions
const int trafficRed    = 13;
const int trafficYellow = 12;
const int trafficGreen  = 11;
const int pedRed        = 10;
const int pedGreen      = 9;
const int buzzer        = 8;

// Timing (milliseconds)
const unsigned long RED_TIME    = 5000;  // 5 seconds
const unsigned long GREEN_TIME  = 5000;  // 5 seconds
const unsigned long YELLOW_TIME = 2000;  // 2 seconds

// Musical notes (frequencies in Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

// Simple melody: "Twinkle Twinkle Little Star" beginning
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4
};

// Note durations: 4 = quarter note, 8 = eighth note, etc.
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 2
};

void setup() {
  // Outputs
  pinMode(trafficRed, OUTPUT);
  pinMode(trafficYellow, OUTPUT);
  pinMode(trafficGreen, OUTPUT);
  pinMode(pedRed, OUTPUT);
  pinMode(pedGreen, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  // Start with everything off
  digitalWrite(trafficRed, LOW);
  digitalWrite(trafficYellow, LOW);
  digitalWrite(trafficGreen, LOW);
  digitalWrite(pedRed, LOW);
  digitalWrite(pedGreen, LOW);
  digitalWrite(buzzer, LOW);
  
  // Serial for messages
  Serial.begin(9600);
  while (!Serial) { /* wait for Serial (optional) */ }
  Serial.println("Traffic Light Simulation started");
}

void playMelody() {
  // Play the melody during pedestrian crossing
  for (int thisNote = 0; thisNote < 7; thisNote++) {
    // Calculate the duration of each note
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzer, melody[thisNote], noteDuration);
    
    // To distinguish the notes, set a minimum time between them
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    // Stop the tone playing
    noTone(buzzer);
  }
}

void playWalkingBeep() {
  // Alternative: Rhythmic beeping pattern
  for (int i = 0; i < 8; i++) {
    tone(buzzer, NOTE_G4, 200);  // Short beep
    delay(300);
    noTone(buzzer);
    delay(200);
  }
}

void loop() {
  // ===== State 1: TRAFFIC GREEN (cars go) | PEDESTRIANS STOP =====
  digitalWrite(trafficRed, LOW);
  digitalWrite(trafficYellow, LOW);
  digitalWrite(trafficGreen, HIGH);
  digitalWrite(pedRed, HIGH);
  digitalWrite(pedGreen, LOW);
  
  // Serial message
  Serial.println("GO");     // drivers: GO (green)
  delay(GREEN_TIME);
  
  // ===== State 2: TRAFFIC YELLOW (cars wait) | PEDESTRIANS STOP =====
  digitalWrite(trafficRed, LOW);
  digitalWrite(trafficYellow, HIGH);
  digitalWrite(trafficGreen, LOW);
  digitalWrite(pedRed, HIGH);
  digitalWrite(pedGreen, LOW);
  
  // Serial message
  Serial.println("WAIT");   // drivers: WAIT (yellow)
  delay(YELLOW_TIME);
  
  // ===== State 3: TRAFFIC RED (cars stop) | PEDESTRIANS GO =====
  digitalWrite(trafficRed, HIGH);
  digitalWrite(trafficYellow, LOW);
  digitalWrite(trafficGreen, LOW);
  digitalWrite(pedRed, LOW);
  digitalWrite(pedGreen, HIGH);
  
  // Play melody while pedestrians cross
  Serial.println("STOP");   // drivers: STOP (red)
  
  // Choose one of these musical options:
  playMelody();           // Plays "Twinkle Twinkle Little Star"
  // playWalkingBeep();   // Uncomment this and comment above for rhythmic beeping
  
  // Fill remaining time with silence
  delay(RED_TIME - 3000); // Adjust based on melody length
  
  // The loop will now repeat correctly, going from Red back to Green.
}
