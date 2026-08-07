```markdown
# 🌈 ESP32 Potentiometer Project - Version 4

## 📌 Overview

Version 4 expands the potentiometer project by using a **10kΩ potentiometer to control an RGB LED**.

Instead of simply switching between fixed colors, the ESP32 uses **PWM (Pulse Width Modulation)** to gradually adjust the intensity of the red, green, and blue channels. This creates smooth transitions between multiple colors as the potentiometer is rotated.

The potentiometer position is also displayed as a percentage on the **0.96" SSD1306 OLED display**, along with a graphical progress bar.

This version combines **ADC input, PWM output, RGB color mixing, and OLED visualization** into a single project.

---

## 🎯 Objectives

- Read analog input from a 10kΩ potentiometer.
- Use the potentiometer position to control an RGB LED.
- Generate smooth color transitions using PWM.
- Understand how different RGB intensity values produce different colors.
- Map ADC ranges to individual RGB PWM values.
- Display the potentiometer position on the OLED.
- Combine analog input, multiple PWM outputs, and graphical feedback.

---

## 🛠️ Components Used

- ESP32 Development Board
- 10kΩ Potentiometer
- RGB LED Module
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

### RGB LED Module

| RGB LED Pin | ESP32 |
|-------------|-------|
| Red | GPIO 4 |
| Green | GPIO 5 |
| Blue | GPIO 18 |
| Common / GND | GND |

> **Note:** These connections assume a common-cathode RGB LED module. If a common-anode module is used, the PWM logic must be inverted.

### OLED Display

| OLED Pin | ESP32 |
|----------|-------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

## ⚙️ How It Works

- The potentiometer acts as a variable voltage divider.
- Rotating the potentiometer changes the voltage supplied to GPIO 34.
- The ESP32's built-in 12-bit ADC converts this voltage into a value between approximately **0 and 4095**.
- The ADC range is divided into multiple transition regions.
- Within each region, the `map()` function calculates the PWM intensity of one RGB channel.
- PWM values between **0 and 255** allow each RGB channel to have different brightness levels.
- Gradually increasing or decreasing these PWM values creates smooth transitions between colors.
- The potentiometer position is also converted into a percentage and displayed on the OLED.

---

## 🌈 Color Transition Sequence

The potentiometer controls the RGB LED through the following sequence:

| Potentiometer Position | Color Transition |
|------------------------|------------------|
| 0 – 1023 | Red → Yellow |
| 1024 – 2047 | Yellow → Green |
| 2048 – 3071 | Green → Cyan |
| 3072 – 4095 | Cyan → Blue |

The complete transition is:

**Red → Yellow → Green → Cyan → Blue**

Unlike fixed digital color switching, the colors gradually blend into one another as the potentiometer is rotated.

---

## 🎨 RGB Color Mixing

An RGB LED contains three individual color channels:

- Red
- Green
- Blue

Each channel is controlled independently using an 8-bit PWM value between **0 and 255**.

| Color | Red | Green | Blue |
|-------|----:|------:|-----:|
| Red | 255 | 0 | 0 |
| Yellow | 255 | 255 | 0 |
| Green | 0 | 255 | 0 |
| Cyan | 0 | 255 | 255 |
| Blue | 0 | 0 | 255 |

Intermediate PWM values create additional colors between these main colors.

For example, during the transition from red to yellow, the red channel remains at maximum intensity while the green channel gradually increases.

---

## ⚡ PWM Configuration

All three RGB channels are controlled using PWM.

The PWM output is configured with:

- **Frequency:** 5000 Hz
- **Resolution:** 8-bit
- **PWM Range:** 0–255

Each RGB channel is attached to PWM independently using `ledcAttach()`.

The brightness of each channel is then controlled using `ledcWrite()`.

This allows the ESP32 to generate many more colors than simple HIGH and LOW digital outputs.

---

## 🔄 ADC to RGB Control

The potentiometer provides:

**ADC Range: 0–4095**

This range is divided into four sections.

Within each section, one RGB channel gradually increases or decreases.

For example:

### Red to Yellow

- Red remains at 255.
- Green increases from 0 to 255.
- Blue remains at 0.

### Yellow to Green

- Red decreases from 255 to 0.
- Green remains at 255.
- Blue remains at 0.

### Green to Cyan

- Red remains at 0.
- Green remains at 255.
- Blue increases from 0 to 255.

### Cyan to Blue

- Red remains at 0.
- Green decreases from 255 to 0.
- Blue remains at 255.

This produces smooth transitions instead of immediately switching from one color to another.

---

## 📚 Concepts Learned

- Analog-to-Digital Conversion (ADC)
- Reading Analog Inputs using `analogRead()`
- ADC Range Mapping
- Pulse Width Modulation (PWM)
- Multiple PWM Outputs
- RGB LED Control
- RGB Color Mixing
- Smooth Color Transitions
- Mapping ADC Values to PWM Values
- Using `ledcAttach()`
- Using `ledcWrite()`
- Using One Analog Input to Control Multiple Outputs
- OLED Percentage Visualization
- Graphical Progress Bar Display

---

## 💡 Challenges Faced

- Initially controlling the RGB channels using only HIGH and LOW values, which resulted in abrupt color changes.
- Understanding why digital RGB control could not produce smooth transitions.
- Using PWM to independently control the intensity of each RGB channel.
- Mapping different sections of the ADC range to different PWM ranges.
- Maintaining continuity between adjacent color transitions.
- Understanding how combinations of red, green, and blue intensities produce different colors.

---

## 🚀 Future Improvements

- Add more colors to the transition sequence.
- Create a complete RGB color spectrum using more advanced color mapping.
- Display RGB intensity values on the OLED.
- Display the currently generated color name.
- Smooth fluctuating ADC readings using averaging.
- Add multiple RGB control modes.
- Use the potentiometer as an OLED menu navigation input.

---

## 📷 Project Images

### Circuit Setup

![Circuit Setup](images/Circuit.jpeg)

### Project Demonstration

![Project Demo](images/Demo.gif)

---

## ✅ Conclusion

Version 4 significantly expands the potentiometer project by combining **analog input with multi-channel PWM control**.

Instead of simply selecting predefined colors, the potentiometer continuously controls the intensity of the RGB LED's individual color channels. This allows smooth transitions from **red through yellow, green, and cyan to blue**.

This version demonstrates how analog input values can be processed and mapped to multiple outputs simultaneously. It also reinforces PWM concepts while introducing RGB color mixing and smooth interpolation between output states.

The project provides a strong foundation for more advanced RGB lighting systems, analog controllers, user interfaces, and other embedded systems where a continuous physical input is used to control multiple outputs.
```
