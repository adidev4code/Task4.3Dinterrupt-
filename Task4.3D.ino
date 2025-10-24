// Code:

#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>
#include <SAMDTimerInterrupt.h>
#include <SAMD_ISR_Timer.h>

// ---------- Pin Definitions ----------
#define BUTTON_PIN 2     // Button input (interrupt)
#define LED1_PIN 5       // LED1 toggled by button

#define TRIG_PIN 8       // Ultrasonic TRIG
#define ECHO_PIN 9       // Ultrasonic ECHO
#define LED2_PIN 6       // LED2 toggled by ultrasonic condition

#define LED3_PIN 7       // LED3 toggled every 1s by timer

// ---------- Global Variables ----------
volatile bool led1State = LOW;
volatile bool led2State = LOW;
volatile bool led3State = LOW;

unsigned long lastMillis = 0;          // software timer for 1s interval
float lastBrightness = -1;             // store last brightness level

BH1750 lightMeter;                     // BH1750 object

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

  // Attach button interrupt
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);

  // BH1750 init
  Wire.begin();       // Start I2C
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("BH1750 initialized successfully.");
  } else {
    Serial.println("Error initializing BH1750.");
  }

  Serial.println("Setup complete.");
}

// ---------- Main Loop ----------
void loop() {
  unsigned long currentMillis = millis();

  // --- Timer Interrupt (runs every 1 second) ---
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

    long duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30ms
    long distance = duration * 0.034 / 2;

    Serial.print("Ultrasonic distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 0 && distance < 20) {
      led2State = !led2State;
      digitalWrite(LED2_PIN, led2State);
      Serial.println("Ultrasonic condition met: LED2 toggled");
    }

    // --- BH1750 Light Sensor ---
    float lux = lightMeter.readLightLevel();
    if (lux < 0) {
      Serial.println("Error reading BH1750.");
    } else {
      // Only print if brightness changed significantly (>5 lux)
      if (abs(lux - lastBrightness) > 5) {
        if (lux > lastBrightness && lastBrightness != -1) {
          Serial.print("Brightness increased from ");
          Serial.print(lastBrightness);
          Serial.print(" → ");
          Serial.println(lux);
        } 
        else if (lux < lastBrightness && lastBrightness != -1) {
          Serial.print("Brightness decreased from ");
          Serial.print(lastBrightness);
          Serial.print(" → ");
          Serial.println(lux);
        } 
        else {
          Serial.print("Current Brightness: ");
          Serial.println(lux);
        }

        lastBrightness = lux; // update stored value
      }
    }
  }
}
