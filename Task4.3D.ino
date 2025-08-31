// Code:

#include <SAMDTimerInterrupt.h>
#include <SAMD_ISR_Timer.h>
#include <DHT.h>

// =========================
// Pin Definitions
// =========================
#define BUTTON_PIN 2     
#define SENSOR1_PIN 3    
#define SENSOR2_PIN 4    
#define LED1_PIN 5       
#define LED2_PIN 6       
#define LED3_PIN 7       

// Ultrasonic pins
#define TRIG_PIN 8
#define ECHO_PIN 9

// DHT sensor
#define DHTPIN 10
#define DHTTYPE DHT11   // change to DHT22 if using DHT22
DHT dht(DHTPIN, DHTTYPE);

// =========================
// Global Variables
// =========================
volatile bool led1State = LOW;
volatile bool led2State = LOW;
volatile bool led3State = LOW;

// Timer setup (SAMD21 TC3 timer)
SAMDTimer ITimer(TIMER_TC3);
#define TIMER_INTERVAL_MS 1000  

// =========================
// Interrupt Service Routines (ISRs)
// =========================
void buttonISR() {
  led1State = !led1State;
  digitalWrite(LED1_PIN, led1State);
  Serial.println("Button interrupt: LED1 toggled");
}

void sensor1ISR() {
  led2State = !led2State;
  digitalWrite(LED2_PIN, led2State);
  Serial.println("Sensor1 interrupt: LED2 toggled");
}

void sensor2ISR() {
  Serial.println("Sensor2 interrupt: Message logged");
}

// Measure distance from Ultrasonic sensor
long readUltrasonic() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30ms
  long distance = duration * 0.034 / 2;           // cm
  return distance;
}

// Timer ISR: toggles LED3 + reads sensors
void TimerHandler() {
  led3State = !led3State;
  digitalWrite(LED3_PIN, led3State);

  Serial.println("Timer interrupt: LED3 toggled, reading sensors...");

  // Read ultrasonic
  long distance = readUltrasonic();
  Serial.print("Ultrasonic distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Read DHT
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

// =========================
// Setup Functions
// =========================
void setupPins() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(SENSOR1_PIN, INPUT_PULLUP);
  pinMode(SENSOR2_PIN, INPUT_PULLUP);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void setupInterrupts() {
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(SENSOR1_PIN), sensor1ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SENSOR2_PIN), sensor2ISR, RISING);
}

void setupTimer() {
  if (ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler)) {
    Serial.println("Timer interrupt initialized successfully");
  } else {
    Serial.println("Failed to initialize Timer interrupt");
  }
}

// =========================
// Arduino Core Functions
// =========================
void setup() {
  Serial.begin(115200);
  dht.begin();

  setupPins();
  setupInterrupts();
  setupTimer();
}

void loop() {
  // Nothing here – all handled by interrupts
}
