// Code:

#include <Arduino.h>
#include <SAMDTimerInterrupt.h>
#include <SAMD_ISR_Timer.h>

// ---------- Pin Definitions ----------
#define BUTTON_PIN 2     // Button input (interrupt)
#define LED1_PIN 5       // LED1 toggled by button

#define TRIG_PIN 8       // Ultrasonic TRIG
#define ECHO_PIN 9       // Ultrasonic ECHO
#define LED2_PIN 6       // LED2 toggled by ultrasonic condition

#define LIGHT_AO A0      // Light sensor AO pin (analog brightness level)

#define LED3_PIN 7       // LED3 toggled every 1s by timer

// ---------- Global Variables ----------
volatile bool led1State = LOW;
volatile bool led2State = LOW;
volatile bool led3State = LOW;

unsigned long lastMillis = 0;          // software timer for 1s interval
int lastBrightness = -1;               // store last brightness level

// ---------- ISR: Button ----------
void buttonISR() {
  led1State = !led1State;
  digitalWrite(LED1_PIN, led1State);
  Serial.println("Button interrupt: LED1 toggled");
}

// ---------- Setup ----------
void setup() {
  delay(1000); // short startup delay
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Task 4.3D: Starting...");

  // Pin setup
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LIGHT_AO, INPUT);

  // Attach button interrupt
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);

  Serial.println("Setup complete.");
}

// ---------- Main Loop ----------
void loop() {
  unsigned long currentMillis = millis();

  // --- Timer Task (runs every 1 second) ---
  if (currentMillis - lastMillis >= 1000) {
    lastMillis = currentMillis;

    // Toggle LED3
    led3State = !led3State;
    digitalWrite(LED3_PIN, led3State);
    Serial.println("Timer interrupt: LED3 toggled");

    // --- Ultrasonic Sensor ---
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    long distance = duration * 0.034 / 2;

    Serial.print("Ultrasonic distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 0 && distance < 20) {
      led2State = !led2State;
      digitalWrite(LED2_PIN, led2State);
      Serial.println("Ultrasonic condition met: LED2 toggled");
    }

    // --- Light Sensor (AO Reading) ---
    int brightness = analogRead(LIGHT_AO);

    // Only print if brightness changed significantly
    if (abs(brightness - lastBrightness) > 50) {
      if (brightness > lastBrightness && lastBrightness != -1) {
        Serial.print("Brightness increased from ");
        Serial.print(lastBrightness);
        Serial.print(" → ");
        Serial.println(brightness);
      } 
      else if (brightness < lastBrightness && lastBrightness != -1) {
        Serial.print("Brightness decreased from ");
        Serial.print(lastBrightness);
        Serial.print(" → ");
        Serial.println(brightness);
      } 
      else {
        Serial.print("Current Brightness: ");
        Serial.println(brightness);
      }

      lastBrightness = brightness; // update stored value
    }
  }
}
