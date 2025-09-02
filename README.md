# 📘 Task 4.3D – Arduino Multiple Inputs with Timer Interrupts

---

## 🎯 Objective

The purpose of this task is to implement **multiple input handling using interrupts** on an Arduino board. The program should be capable of:

1. Handling **external interrupts** via a push button.
2. Handling **sensor inputs** (Ultrasonic + DHT22).
3. Using a **timer interrupt** to perform a periodic task (LED blinking).
4. Displaying sensor readings and interrupt logs on the **Serial Monitor**.

This task demonstrates the principle of **asynchronous event-driven programming** in embedded systems.

---

## 🛠️ Hardware Requirements

* Arduino Nano 33 IoT (or compatible board)
* 1x Push Button
* 3x LEDs + 3x 220Ω resistors
* 1x Ultrasonic sensor (HC-SR04)
* 1x DHT22 Temperature & Humidity sensor (3-pin version)
* Breadboard and jumper wires

---

## 🔌 Hardware Setup (Pin Connections)

| Component       | Arduino Pin | Notes                                   |
| --------------- | ----------- | --------------------------------------- |
| Button          | D2          | Uses `INPUT_PULLUP`, toggles LED1       |
| LED1            | D5          | Toggled by button interrupt             |
| LED2            | D6          | Controlled by ultrasonic distance check |
| LED3            | D7          | Blinks every 1s via timer interrupt     |
| Ultrasonic TRIG | D8          | Trigger pulse output                    |
| Ultrasonic ECHO | D9          | Reads pulse width                       |
| DHT22 Data      | D10         | Data pin (pull-up 10kΩ recommended)     |
| Ultrasonic VCC  | 3.3V        | Power supply                            |
| DHT22 VCC       | 3.3V        | Power supply                            |
| All GND pins    | GND         | Common ground for all components        |

⚠️ Important: Use resistors with LEDs to prevent damage. Ensure all sensor grounds are common with Arduino GND.

---

## 📜 Procedure

### Step 1: Hardware Assembly

1. Connect **LED1 to pin D5**, **LED2 to pin D6**, **LED3 to pin D7**, each with a resistor.
2. Connect **Button to pin D2**, with one side to GND and use `INPUT_PULLUP`.
3. Connect **Ultrasonic sensor**:

   * VCC → 3.3V
   * GND → GND
   * TRIG → D8
   * ECHO → D9
4. Connect **DHT22**:

   * VCC → 3.3V
   * GND → GND
   * DATA → D10
   * Pull-up resistor 10kΩ between VCC and DATA if needed.

---

### Step 2: Software Implementation

1. Include the `DHT.h` library.
2. Define pin mappings for LEDs, button, and sensors.
3. Configure ISRs:

   * **Button ISR** → toggles LED1.
   * **Ultrasonic check (in loop)** → toggles LED2 when object < threshold.
   * **Timer (millis-based)** → toggles LED3 every 1s.
4. Print sensor data (Ultrasonic + DHT22) to Serial Monitor.

---

### Step 3: Workflow of Operation

1. **Button interrupt**: Pressing the button toggles **LED1** immediately.
2. **Ultrasonic sensor**:

   * Sends pulses, measures distance.
   * If an object is detected within 20 cm, **LED2 toggles**.
   * Distance is printed to Serial Monitor.
3. **DHT22 sensor**: Reads **temperature & humidity** values every cycle and logs them.
4. **Timer interrupt**: Every 1 second, **LED3 toggles ON/OFF automatically**.
5. **Serial Monitor**: Displays events, sensor data, and interrupt logs.

---

## 🔎 Flow of Operations

1. Press button → ISR triggers → LED1 toggled.
2. Place hand/object near ultrasonic → distance < 20 cm → LED2 toggled.
3. Timer runs every 1s → LED3 blinks independently.
4. Every cycle → DHT22 values (Temp + Humidity) printed.
5. Serial Monitor shows logs from button, ultrasonic, DHT, and timer.

---

## 🧪 Testing

### Test Cases & Expected Results

| Test Action                            | Expected Result                                                           |
| -------------------------------------- | ------------------------------------------------------------------------- |
| Press button                           | LED1 toggles state, log appears on Serial Monitor                         |
| Place hand close to ultrasonic (<20cm) | LED2 toggles, distance logged                                             |
| Move hand away (>20cm)                 | LED2 stays in last state, distance updates                                |
| Wait 1 second                          | LED3 toggles (blinks continuously)                                        |
| Observe Serial Monitor                 | Logs show button events, ultrasonic distance, DHT readings, timer toggles |

---

## 🖥️ Sample Serial Monitor Output

```
Task 4.3D: Starting...
Setup complete.
Timer interrupt: LED3 toggled
Ultrasonic distance: 55 cm
Temperature: 26.00 °C | Humidity: 87.50 %
Button interrupt: LED1 toggled
Ultrasonic condition met: LED2 toggled
Timer interrupt: LED3 toggled
Ultrasonic distance: 12 cm
Temperature: 27.00 °C | Humidity: 86.90 %
```

---

## ✅ Results & Observations

* LED1 successfully toggles on button press (external interrupt).
* LED2 responds to ultrasonic proximity events.
* LED3 blinks automatically every second (timer interrupt).
* DHT22 provides accurate temperature and humidity readings.
* Serial Monitor confirms real-time event handling.

---

## 📌 Conclusion

The task was successfully completed.

* **External interrupts** (button & sensor) worked correctly.
* **Timer interrupt** functioned independently, toggling LED3 every second.
* **Multiple sensor inputs** were integrated and logged properly.

This project demonstrates **asynchronous multitasking** in Arduino — responding instantly to external events (button, ultrasonic), periodic tasks (timer), and sensor logging (DHT22).

