# Task 4.3D – Arduino Nano 33 IoT with Multiple Inputs and Timer Interrupts

## 📌 Overview

This task demonstrates how to manage **multiple external interrupts** together with a **timer interrupt** on the Arduino Nano 33 IoT (SAMD21 microcontroller). The system integrates user inputs (button and sensors), automatic tasks (via timer), and environmental monitoring using **ultrasonic** and **DHT sensors**.

The objective is to show how interrupt-driven programming keeps the system **responsive and efficient**, without relying on blocking delays in the main loop.

---

## 🎯 Learning Objectives

* Understand and implement **multiple external interrupts**.
* Configure and use a **timer interrupt** on the SAMD21 microcontroller.
* Integrate **real-world sensors** (Ultrasonic, DHT) with interrupt-driven logic.
* Design a system that is responsive to **immediate events** while still performing **periodic tasks**.
* Practice modular coding and documentation for embedded systems.

---

## ⚙️ Hardware Used

* **Arduino Nano 33 IoT (SAMD21)**
* **Push button** (with pull-up enabled)
* **Two external inputs** (can be sensors such as PIR/motion, LDR module, sound sensor, or simulated using push buttons)
* **Ultrasonic sensor (HC-SR04)** for distance measurement
* **DHT11/DHT22** temperature and humidity sensor
* **Three LEDs** (with current-limiting resistors)
* Jumper wires and breadboard

---

## 🛠️ Software Used

* **Arduino IDE / Arduino Web Editor**
* **Libraries required:**

  * SAMDTimerInterrupt (by Khoi Hoang)
  * DHT sensor library (by Adafruit)

---

## 🔌 System Connections (Wiring)

* **Button** → Pin 2 (external interrupt)
* **Sensor1** → Pin 3 (external interrupt)
* **Sensor2** → Pin 4 (external interrupt)
* **LED1** → Pin 5 (toggled by button)
* **LED2** → Pin 6 (toggled by sensor1)
* **LED3** → Pin 7 (toggled by timer interrupt)
* **Ultrasonic Sensor:**

  * TRIG → Pin 8
  * ECHO → Pin 9
* **DHT Sensor:**

  * DATA → Pin 10 (with 10kΩ pull-up to 3.3V)
* **Common GND** for all components

---

## 🔄 Workflow of Operations

1. **Initialization**

   * All pins configured.
   * External interrupts attached to button, sensor1, and sensor2.
   * Timer interrupt configured to fire every **1 second**.
   * Serial Monitor started for event logging.

2. **External Interrupts**

   * **Button Press (pin 2):** Toggles **LED1** and logs a message.
   * **Sensor1 Trigger (pin 3):** Toggles **LED2** and logs a message.
   * **Sensor2 Trigger (pin 4):** Logs a message only.

3. **Timer Interrupt (every 1 second)**

   * Toggles **LED3** automatically.
   * Reads **Ultrasonic sensor** distance (in cm).
   * Reads **DHT sensor** temperature and humidity.
   * Logs all values to the Serial Monitor.

4. **System Behavior**

   * System responds **immediately** to events (button/sensor) via interrupts.
   * At the same time, periodic tasks run reliably via the timer.
   * The main `loop()` remains empty → fully interrupt-driven, non-blocking design.

---

## 📊 Testing Procedure

1. Open Serial Monitor at **115200 baud**.
2. Press the **button** → LED1 toggles, message logged.
3. Trigger **Sensor1** → LED2 toggles, message logged.
4. Trigger **Sensor2** → only a message logged.
5. Observe **LED3 blinking** automatically every second.
6. Check Serial Monitor → readings from ultrasonic and DHT sensors update every second.
