# 🎛️ ESP32 Potentiometer Project - Version 1

## 📌 Overview

This project introduces the concept of **Analog-to-Digital Conversion (ADC)** using a **10kΩ potentiometer** with the ESP32. Unlike digital sensors that provide only HIGH or LOW signals, the potentiometer generates a continuously varying voltage that the ESP32 converts into a digital value.

The real-time ADC value is displayed on a **0.96" SSD1306 OLED display**, providing a visual representation of the potentiometer's position without relying on the Serial Monitor.

---

## 🎯 Objectives

- Learn the fundamentals of Analog-to-Digital Conversion (ADC).
- Read analog input from a potentiometer using the ESP32.
- Display live ADC readings on an OLED display.
- Understand how analog voltages are represented as digital values.

---

## 🛠️ Components Used

- ESP32 Development Board
- 10kΩ Potentiometer
- 0.96" SSD1306 OLED Display (I²C)
- Breadboard
- Jumper Wires

---

## 🔌 Circuit Connections

### Potentiometer

| Potentiometer Pin | ESP32 |
|-------------------|--------|
| Left Pin | 3.3V |
| Middle Pin (Wiper) | GPIO 34 |
| Right Pin | GND |

### OLED Display

| OLED Pin | ESP32 |
|----------|--------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

## ⚙️ How It Works

- The potentiometer acts as a variable voltage divider.
- Rotating the knob changes the voltage at its middle (wiper) pin.
- The ESP32's built-in **12-bit ADC** converts this voltage into a digital value ranging from **0 to 4095**.
- The OLED continuously updates to display the current ADC reading in real time.

---

## 📚 Concepts Learned

- Analog vs Digital Signals
- Analog-to-Digital Conversion (ADC)
- ESP32 ADC Resolution (12-bit)
- Reading Analog Inputs using `analogRead()`
- OLED Display Updates using I²C
- Function-based Code Organization

---

## 💡 Challenges Faced

- Understanding the difference between analog voltage and digital values.
- Learning how the ESP32 converts a continuous voltage into discrete numerical values.
- Positioning text neatly on the OLED for different ADC readings.

---

## 🚀 Future Improvements

- Convert ADC readings into percentages.
- Display a graphical progress bar.
- Use the potentiometer to control LED brightness via PWM.
- Integrate the potentiometer with an RGB LED for color control.
- Use the potentiometer as a menu navigation input for future projects.

---

## 📷 Project Images

### Circuit Setup

![Circuit Setup](images/Circuit.jpeg)

### Project Demonstration

![Project Demo](images/Demo.gif)

---

## ✅ Conclusion

This project marks the introduction to **analog input processing** on the ESP32. By reading and displaying live ADC values from a potentiometer, it establishes the foundation for working with analog sensors and user-controlled inputs. The concepts learned here will be applied in future projects involving LED brightness control, RGB LEDs, menu navigation, and more advanced sensor-based applications.