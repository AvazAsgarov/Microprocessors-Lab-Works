# Lab 1: Traffic Light Circuit with Pedestrian Lights and Musical Buzzer

## Objective
Design and simulate a basic traffic light system using Arduino, including pedestrian signals and a musical buzzer. The project demonstrates sequential control, timing, and basic Arduino programming.

---

## Components
- Arduino Uno R3 — 1
- Breadboard — 1
- LEDs — 5  
  - Traffic: Red, Yellow, Green  
  - Pedestrian: Red, Green
- Resistors — 5 × 220Ω  
- Buzzer (Piezo) — 1  
- Jumper wires — ~10–15

---

## Features
- Traffic light sequence: **Red → Green → Yellow**  
- Pedestrian lights synchronized with traffic lights  
- Musical buzzer during pedestrian crossing  
  - Melody option: `"Twinkle Twinkle Little Star"`  
  - Rhythmic beep option  
- Serial Monitor displays messages: `"STOP"`, `"WAIT"`, `"GO"`  

---

## Wiring Overview
- **Traffic LEDs**  
  - Red → Pin 13  
  - Yellow → Pin 12  
  - Green → Pin 11  
- **Pedestrian LEDs**  
  - Red → Pin 10  
  - Green → Pin 9  
- **Buzzer** → Pin 8  
- **Resistors**: One per LED, connected to the cathode and common ground rail  
- **Ground**: All components share Arduino GND  

---

## Code
Arduino sketch: `TrafficLight.ino`  
- Controls traffic and pedestrian lights  
- Plays a melody or rhythmic buzzer during pedestrian crossing  
- Prints `"STOP"`, `"WAIT"`, `"GO"` to Serial Monitor  

```cpp
// Traffic Light with Pedestrian Lights, Musical Buzzer, and Serial messages
// (Full code goes here, or link the .ino file)
