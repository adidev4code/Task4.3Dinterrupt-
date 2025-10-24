# Task 4.3D: Arduino Multiple Inputs with Timer Interrupts

---

## 📌 Overview

This project is the implementation of **Task 4.3D – Arduino Multiple Inputs with Timer Interrupts**.

The main aim of this task is to demonstrate how an **Arduino** can handle **multiple inputs, sensors, and timer-based events** all together in a single system.
The project includes:

* A **button interrupt** to toggle LED1,
* An **ultrasonic sensor** to toggle LED2 based on distance,
* A **BH1750 digital light sensor** to measure ambient brightness and show changes in the Serial Monitor,
* A **timer (software-based)** to toggle LED3 automatically every 1 second.

This demonstrates the concept of **concurrent event handling** using interrupts, sensor readings, and periodic operations in embedded systems.

---

## ⚙️ Hardware Components

* **Arduino MKR Board / Nano 33 IoT (SAMD architecture)**
* **1 Push Button**
* **3 LEDs** + Resistors
* **Ultrasonic Sensor (HC-SR04)**
* **BH1750 Light Sensor (I²C)**
* **Breadboard and Jumper Wires**

---

## 🔌 Hardware Connections

| Component                  | Pin Connection                           | Description                     |
| -------------------------- | ---------------------------------------- | ------------------------------- |
| **Button**                 | D2                                       | External interrupt input        |
| **LED1**                   | D5                                       | Toggled by button interrupt     |
| **Ultrasonic Sensor TRIG** | D8                                       | Sends trigger pulse             |
| **Ultrasonic Sensor ECHO** | D9                                       | Reads echo pulse                |
| **LED2**                   | D6                                       | Toggled when object < 20 cm     |
| **BH1750 Light Sensor**    | SDA → A4 / SDA pin<br>SCL → A5 / SCL pin | Communicates via I²C bus        |
| **LED3**                   | D7                                       | Toggled every 1 second by timer |
| **VCC**                    | 3.3V or 5V (depends on board)            | Power supply                    |
| **GND**                    | Common Ground                            | Ground for all components       |

---

## 🧠 How It Works (Flow of Operations)

1. **Button Interrupt**

   * When the button is pressed, an **ISR (Interrupt Service Routine)** is triggered.
   * LED1 toggles instantly.
   * Serial Monitor shows:
     `"Button interrupt: LED1 toggled"`

2. **Timer Function (Every 1 Second)**

   * A **software timer** runs using `millis()` to simulate a 1-second interrupt.
   * LED3 toggles automatically every second.
   * Serial Monitor shows:
     `"Timer interrupt: LED3 toggled"`

3. **Ultrasonic Sensor**

   * Measures the distance every second using trigger and echo pins.
   * If distance < 20 cm → LED2 toggles.
   * Serial Monitor shows:
     `"Ultrasonic condition met: LED2 toggled"`

4. **BH1750 Light Sensor**

   * Reads light intensity in **lux** through I²C communication.
   * If brightness changes by more than 5 lux, it logs whether brightness increased or decreased.
   * Example:
     `"Brightness decreased from 120 → 85 lux"`

---

## 📝 Features of the Code

* **Interrupt-driven button input** for real-time response.
* **Software timer** for periodic LED control and sensor checks.
* **I²C-based BH1750 sensor** for accurate digital light readings.
* **Efficient control flow**, avoiding continuous sensor polling.
* **Clean serial output** for clear debugging and observation.

---

## 🔬 Testing the Project

1. **Button Test**

   * Press the button — LED1 toggles instantly.
   * Check the Serial Monitor for confirmation message.

2. **Timer Test**

   * Observe LED3 blinking every 1 second automatically.

3. **Ultrasonic Test**

   * Move your hand or an object near the sensor.
   * If distance < 20 cm, LED2 toggles and message appears.

4. **Light Sensor Test**

   * Shine or block light near the BH1750 sensor.
   * Serial Monitor shows:
     `"Brightness increased/decreased from X → Y lux"`

---

## 🚀 Conclusion

This project successfully demonstrates the **integration of multiple interrupts and sensors** in a single embedded system:

* **Button interrupt (external)**
* **Ultrasonic and light sensor readings (sensor-driven events)**
* **Timer interrupt (software-based periodic task)**

It shows how **Arduino can multitask efficiently**, handling different types of inputs and timing events simultaneously — fulfilling the goal of **Task 4.3D** with precise and reliable performance.

---

