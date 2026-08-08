```markdown
# 🎛️ ESP32 Potentiometer Project - Version 5

## 📌 Overview

Version 5 transforms the potentiometer project into a complete **menu-driven control system** using an ESP32, OLED display, potentiometer, push button, standard LED, and RGB LED module.

Instead of performing only one function, the system now contains multiple operating modes that can be accessed through an OLED menu.

The potentiometer is used to navigate through the menu, while a push button is used to select an option or return to the main menu.

The available modes are:

- LED Dimmer
- RGB Control
- ADC Monitor
- About

This version combines concepts from all previous versions of the potentiometer project while introducing **menu navigation, system states, switch-case logic, and multi-mode embedded system design**.

---

## 🎯 Objectives

- Use a potentiometer to navigate an OLED menu.
- Use a push button to select menu options.
- Implement multiple operating modes within a single program.
- Control LED brightness using ADC and PWM.
- Control an RGB LED using smooth PWM color transitions.
- Monitor raw ADC readings in real time.
- Learn how system states can control program behavior.
- Use `switch-case` statements to organize different operating modes.
- Combine multiple previously learned concepts into one integrated system.

---

## 🛠️ Components Used

- ESP32 Development Board
- 10kΩ Potentiometer
- Push Button
- External LED
- 220Ω Resistor
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

### Push Button

| Button Connection | ESP32 |
|-------------------|--------|
| One Side | GPIO 19 |
| Other Side | GND |

The button uses the ESP32's internal pull-up resistor through `INPUT_PULLUP`.

### Standard LED

| LED Connection | ESP32 |
|----------------|-------|
| Anode (+) through 220Ω resistor | GPIO 23 |
| Cathode (-) | GND |

### RGB LED Module

| RGB LED Pin | ESP32 |
|-------------|-------|
| Red | GPIO 4 |
| Green | GPIO 5 |
| Blue | GPIO 18 |
| Common / GND | GND |

### OLED Display

| OLED Pin | ESP32 |
|----------|-------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

## 🖥️ Menu System

The OLED displays four available options:

- LED DIMMER
- RGB CONTROL
- ADC MONITOR
- ABOUT

A `>` symbol indicates the currently highlighted option.

Example:

    MENU
    -------------

    > LED DIMMER
      RGB CONTROL
      ADC MONITOR
      ABOUT

Rotating the potentiometer changes the highlighted menu option.

Pressing the button opens the selected mode.

Pressing the button again while inside any mode returns the system to the main menu.

---

## 🎚️ Potentiometer Menu Navigation

The potentiometer normally produces ADC readings between approximately **0 and 4095**.

For menu navigation, a shortened mapping range of **0 to 1024** is used. This allows the menu to cycle through its options with less physical rotation of the potentiometer.

Values produced beyond the mapped menu range are limited using `constrain()` so that the menu option remains between **0 and 3**.

This makes the menu respond more quickly to potentiometer movement.

---

## 💡 LED Dimmer Mode

LED Dimmer Mode uses the potentiometer to control the brightness of a standard LED.

The ESP32 reads the potentiometer using its ADC and maps:

**ADC: 0–4095 → PWM: 0–255**

The PWM value is then sent to the LED connected to GPIO 23.

The OLED displays:

- Brightness percentage
- Graphical progress bar

Rotating the potentiometer therefore simultaneously changes the physical LED brightness and the value displayed on the OLED.

---

## 🌈 RGB Control Mode

RGB Control Mode uses the potentiometer to generate smooth color transitions on the RGB LED.

The ADC range is divided into four transition regions:

| ADC Range | Transition |
|-----------|------------|
| 0–1023 | Red → Yellow |
| 1024–2047 | Yellow → Green |
| 2048–3071 | Green → Cyan |
| 3072–4095 | Cyan → Blue |

Each RGB channel is independently controlled using **8-bit PWM values from 0 to 255**.

The complete transition sequence is:

**Red → Yellow → Green → Cyan → Blue**

Unlike simple HIGH/LOW RGB control, PWM allows intermediate brightness levels to produce smooth color blending.

The OLED displays the current potentiometer position as a percentage along with a graphical progress bar.

---

## 📊 ADC Monitor Mode

ADC Monitor Mode displays the raw ADC reading from the potentiometer.

The ESP32's 12-bit ADC provides values ranging approximately from:

**0 to 4095**

The OLED continuously updates the displayed value as the potentiometer is rotated.

This mode provides direct access to the original analog data before any percentage or PWM conversion is performed.

---

## ℹ️ About Mode

The About page displays basic information about the project:

    Pot Controller
    Version 5
    ESP32

This demonstrates how informational screens can be incorporated into an embedded user interface.

---

## 🔄 System States

Version 5 introduces different operating states.

The system uses the following states:

| State | Mode |
|-------|------|
| 0 | Menu |
| 1 | LED Dimmer |
| 2 | RGB Control |
| 3 | ADC Monitor |
| 4 | About |

The `currentMode` variable stores the current state of the system.

The main program then uses a `switch-case` statement to determine which functionality should run.

This allows one ESP32 program to perform several different tasks without requiring separate programs for each feature.

---

## 🔘 Button Control

The push button performs two functions depending on the current system state.

### While in the Menu

The button selects the currently highlighted option.

### While Inside a Mode

The button returns the system to the main menu.

Button state changes are detected using current and previous button states.

A short debounce delay is also used to prevent a single physical press from being detected multiple times.

---

## ⚡ PWM Configuration

PWM is used for both the standard LED and RGB LED.

The PWM configuration uses:

- **Frequency:** 5000 Hz
- **Resolution:** 8-bit
- **PWM Range:** 0–255

The standard LED uses one PWM output, while the RGB LED uses three independent PWM outputs.

This allows the ESP32 to simultaneously support brightness control and RGB color mixing within the same program.

---

## 📚 Concepts Learned

- Analog-to-Digital Conversion (ADC)
- Potentiometer Input
- ADC Range Mapping
- Pulse Width Modulation (PWM)
- LED Brightness Control
- Multi-Channel PWM
- RGB Color Mixing
- Smooth RGB Color Transitions
- OLED User Interfaces
- Menu Navigation
- Push Button Input
- `INPUT_PULLUP`
- Button Edge Detection
- Button Debouncing
- Ternary Operator
- `switch-case` Statements
- System States
- Multi-Mode Program Design
- Function-Based Code Organization
- Combining Multiple Inputs and Outputs

---

## 💡 Challenges Faced

- Designing a menu that could be controlled using an analog potentiometer.
- Adjusting the potentiometer mapping range to make menu navigation faster.
- Using the same potentiometer differently depending on the current operating mode.
- Understanding the difference between highlighting a menu option and selecting a mode.
- Managing multiple system states using a single `currentMode` variable.
- Using a single button for both selecting options and returning to the menu.
- Controlling multiple PWM outputs within the same program.
- Creating smooth RGB transitions instead of abrupt digital color changes.
- Ensuring unused outputs are switched off when changing between modes.

---

## 🚀 Future Improvements

- Add menu navigation hysteresis to reduce movement between options near ADC boundaries.
- Display RGB channel values on the OLED.
- Add additional operating modes.
- Add animated menu transitions.
- Store user settings in non-volatile memory.
- Add icons or improved OLED graphics.
- Replace the potentiometer with a rotary encoder for more advanced menu navigation.
- Integrate the menu system into larger embedded projects.

---

## 📷 Project Images

### Circuit Setup

![Circuit Setup](images/Circuit.jpeg)

### Main Menu

![Main Menu](images/menu_about.mp4)

### LED Dimmer Mode

![LED Dimmer](images/led_dimmer.mp4)

### RGB Control Mode

![RGB Control](images/rgb_control.mp4)

### ADC Monitor Mode

![ADC Monitor](images/adc_monitor.mp4)

---

## ✅ Conclusion

Version 5 completes the ESP32 Potentiometer Project by transforming the potentiometer from a simple analog input into a **user-interface control device**.

The system combines ADC readings, PWM control, RGB color mixing, OLED graphics, button input, and multiple operating modes within a single program. The potentiometer is used both as a continuous controller inside individual modes and as a navigation device within the main menu.

The introduction of the `currentMode` system and `switch-case` logic also represents an important step toward designing larger embedded applications where a microcontroller must manage multiple behaviors and interfaces.

With Version 5 complete, the Potentiometer Project progresses from basic ADC measurement to a fully interactive, multi-mode embedded control system.
```
