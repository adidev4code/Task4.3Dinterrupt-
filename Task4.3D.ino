// Code:

#include <DHT.h>

// =========================
// Pin Definitions
// =========================
#define BUTTON_PIN 2     // Button (interrupt)
#define LED1_PIN 5       // LED1 toggled by button

#define TRIG_PIN 8       // Ultrasonic TRIG
#define ECHO_PIN 9       // Ultrasonic ECHO
#define LED2_PIN 6       // LED2 toggled by ultrasonic condition

#define DHTPIN 10        // DHT22 data pin
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define LED3_PIN 7       // LED3 toggled by timer

// =========================
// Global Variables
// =========================
volatile bool led1State = LOW;
bool led2State = LOW;
bool led3State = LOW;
unsigned long lastMillis = 0;

// =========================
// ISR: Button
// =========================
void buttonISR() {
  led1State = !led1State;
  digitalWrite(LED1_PIN, led1State);
  Serial.println("Button interrupt: LED1 toggled");
}

// =========================
// Setup
// =========================
void setup() {
  delay(1500);
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Task 4.3D: Starting...");

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  dht.begin();

  // External interrupt for button only
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);

  Serial.println("Setup complete.");
}

// =========================
// Main Loop
// =========================
void loop() {
  unsigned long currentMillis = millis();

  // Timer interrupt every 1s
  if (currentMillis - lastMillis >= 1000) {
    lastMillis = currentMillis;

    // Toggle LED3
    led3State = !led3State;
    digitalWrite(LED3_PIN, led3State);
    Serial.println("Timer interrupt: LED3 toggled");

    // Read Ultrasonic
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

    // LED2 toggles if object is near (<20 cm)
    if (distance > 0 && distance < 20) {
      led2State = !led2State;
      digitalWrite(LED2_PIN, led2State);
      Serial.println("Ultrasonic condition met: LED2 toggled");
    }

    // Read DHT22
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();
    if (isnan(temp) || isnan(hum)) {
      Serial.println("DHT read error!");
    } else {
      Serial.print("Temperature: ");
      Serial.print(temp);
      Serial.print(" °C | Humidity: ");
      Serial.print(hum);
      Serial.println(" %");
    }
  }
}
