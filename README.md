# Task 4.3D: Arduino Multiple Inputs with Timer Interrupts

---

## 📌 Overview

This project is the implementation of **Task 4.3D – Arduino Multiple Inputs with Timer Interrupts**.

The main objective of the task is to demonstrate how an Arduino can handle **multiple inputs and interrupts** at the same time. The project integrates:

* A **button interrupt** to toggle LED1,
* An **ultrasonic sensor** to control LED2 when objects come close,
* A **light sensor** to monitor brightness changes and give feedback in Serial Monitor,
* A **timer interrupt** to toggle LED3 automatically every second.

This ensures that **external interrupts, sensor-driven events, and timer-based tasks** are all handled together in one Arduino sketch.

---

## ⚙️ Hardware Components

* **Arduino Nano 33 IoT** (SAMD-based or compatible)
* **1 Push Button**
* **3 LEDs** + resistors
* **Ultrasonic Sensor (HC-SR04)**
* **Light Sensor (analog AO output)**
* **Jumper wires**
* **Breadboard or direct wiring setup**

---

## 🔌 Hardware Connections

* **Button** → Digital Pin 2
* **LED1** → Digital Pin 5 (toggled by button)
* **Ultrasonic Sensor**

  * TRIG → Digital Pin 8
  * ECHO → Digital Pin 9
* **LED2** → Digital Pin 6 (toggled by ultrasonic condition)
* **Light Sensor** → AO → Analog Pin A0
* **LED3** → Digital Pin 7 (toggled by timer every 1 second)
* **VCC** → 5V or 3.3V (depending on module)
* **GND** → Common Ground

---

## 🧠 How It Works (Flow of Operations)

1. **Button Interrupt**

   * When the button is pressed, an **interrupt service routine (ISR)** is triggered.
   * LED1 toggles ON/OFF immediately.
   * A message is printed: *“Button interrupt: LED1 toggled”*.

2. **Timer Interrupt (1 second)**

   * Every second, LED3 toggles automatically.
   * Message: *“Timer interrupt: LED3 toggled”*.

3. **Ultrasonic Sensor**

   * Distance is measured every second.
   * If an object is closer than 20 cm, LED2 toggles.
   * Message: *“Ultrasonic condition met: LED2 toggled”*.

4. **Light Sensor**

   * The analog brightness is read every second.
   * If the brightness changes significantly (more than ±50 units), a message prints whether brightness increased or decreased.
   * Example: *“Brightness increased from 400 → 500”*.

---

## 📝 Features of the Code

* **Interrupt-driven design** → Button handled by ISR, timer by millis().
* **Efficient sensor usage** → Ultrasonic distance measured only at intervals.
* **Threshold-based feedback** → Light sensor reports only meaningful changes, avoiding spam.
* **Modular commenting style** → Code sections clearly separated and explained.

---

## 🔬 Testing the Project

1. **Button Test**

   * Press the button → LED1 toggles instantly.
   * Check Serial Monitor for the interrupt message.

2. **Timer Test**

   * Observe LED3 blinking every 1 second automatically.

3. **Ultrasonic Test**

   * Place your hand/object in front of the ultrasonic sensor.
   * If distance < 20 cm → LED2 toggles, and message is shown.

4. **Light Sensor Test**

   * Change the brightness (torchlight, covering sensor).
   * Observe messages like *“Brightness decreased from 700 → 300”*.

---


## 🚀 Conclusion

This project demonstrates **multiple types of interrupts** in Arduino:

* External interrupt (button),
* Sensor-driven interrupt-like behavior (ultrasonic and light),
* Timer-based interrupt (LED blinking).

It showcases how Arduino can manage multiple tasks **simultaneously and efficiently**, completing the requirements of **Task 4.3D**.

---
