# 🎛️ ESP32 Potentiometer Project - Version 2

## 📌 Overview

This version enhances the potentiometer project by converting the raw ADC readings into a user-friendly percentage value. Instead of displaying values between **0 and 4095**, the ESP32 maps the readings to a **0%–100%** scale and displays them on a **0.96" SSD1306 OLED display**.

A graphical progress bar has also been added, making it easier to visualize the potentiometer's position in real time. The project operates entirely through the OLED display without requiring the Serial Monitor.

---

## 🎯 Objectives

- Read analog input from a 10kΩ potentiometer.
- Convert raw ADC readings into percentage values.
- Display the percentage on an OLED display.
- Create a graphical progress bar representing the potentiometer position.
- Learn how to map values from one range to another.

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

> **Note:** If rotating the potentiometer clockwise decreases the displayed percentage, simply swap the 3.3V and GND connections on the outer pins.

---

## ⚙️ How It Works

- The potentiometer acts as a variable voltage divider.
- Rotating the knob changes the output voltage at the wiper (middle pin).
- The ESP32 reads this voltage using its built-in **12-bit ADC**, producing a value between **0 and 4095**.
- The `map()` function converts the ADC reading into a percentage between **0% and 100%**.
- The OLED displays the percentage along with a graphical progress bar that updates continuously as the potentiometer is rotated.

---

## 📊 ADC to Percentage Conversion

| ADC Value | Percentage |
|-----------|------------|
| 0 | 0% |
| 1024 | 25% |
| 2048 | 50% |
| 3072 | 75% |
| 4095 | 100% |

The conversion is performed using Arduino's `map()` function, while `constrain()` ensures the displayed value always remains within the valid range.

---

## 📚 Concepts Learned

- Analog-to-Digital Conversion (ADC)
- ESP32 12-bit ADC Resolution
- Reading Analog Inputs using `analogRead()`
- Mapping Values using `map()`
- Limiting Values using `constrain()`
- Drawing Shapes on the OLED
- Creating Graphical Progress Bars
- Function-Based Program Organization

---

## 💡 Challenges Faced

- Understanding how ADC values relate to percentages.
- Mapping one numerical range into another.
- Calculating the correct width of the progress bar.
- Aligning percentage values of different lengths on the OLED.
- Creating a smooth and responsive graphical interface.

---

## 🚀 Future Improvements

- Control LED brightness using the potentiometer.
- Display both the ADC value and percentage simultaneously.
- Display the measured voltage in volts.
- Smooth ADC readings using averaging.
- Use the potentiometer to control an RGB LED.
- Implement menu navigation using the potentiometer.

---

## 📷 Project Images

### Circuit Setup

![Circuit Setup](images/Circuit.jpeg)

### Project Demonstration

![Project Demo](images/Demo.gif)

---

## ✅ Conclusion

Version 2 builds upon the basic ADC reading project by presenting the potentiometer's position as an intuitive percentage along with a graphical progress bar. This introduces the important concepts of value mapping and graphical visualization, which are widely used in embedded systems. The knowledge gained in this version serves as the foundation for the next project version, where the potentiometer will be used to control LED brightness through PWM.
```