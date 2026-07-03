

<div align="center">

<img src="assets/aolyf_dynamics_logo.png" width="180"/>

# CYD ESP32 PT1000 Temperature Dashboard

### Professional Embedded HMI System using CYD ESP32-2432S028

Real-time PT1000 temperature monitoring dashboard with animated TFT interface, custom splash screen, and I2C communication architecture.

<br>

![ESP32](https://img.shields.io/badge/ESP32-Embedded-red?style=for-the-badge)
![PlatformIO](https://img.shields.io/badge/PlatformIO-IDE-orange?style=for-the-badge)
![Arduino](https://img.shields.io/badge/Framework-Arduino-blue?style=for-the-badge)
![Display](https://img.shields.io/badge/Display-ILI9341_2_DRIVER-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-success?style=for-the-badge)

<br>

Embedded UI • Real-Time Monitoring • ESP32 • TFT Graphics • I2C Communication

</div>

---

# Overview

This project implements a professional embedded Human Machine Interface (HMI) dashboard using the **CYD ESP32-2432S028** TFT display module.

The system receives PT1000 temperature sensor values from a dedicated ESP32 master controller over the I2C bus and renders them on a modern graphical dashboard optimized for embedded performance.

The interface includes:

* Custom startup splash screen
* Animated loading bar with percentage indicator
* RGB565 branded logo rendering
* Real-time temperature visualization
* Four-channel temperature display
* Optimized TFT rendering pipeline
* Lightweight embedded UI architecture

---

# Live Demonstration

## Startup Splash Screen

* Custom logo animation
* Embedded boot sequence
* Loading progress visualization

## Dashboard Interface

* Four live temperature cards
* Real-time sensor updates
* Professional HMI layout
* Optimized refresh performance

---

# System Architecture

```text id="9z2jlwm"
┌──────────────────────┐
│   PT1000 Sensors     │
└──────────┬───────────┘
           │
           ▼
┌──────────────────────┐
│    ESP32 MASTER      │
│  Sensor Acquisition  │
│   I2C Transmission   │
└──────────┬───────────┘
           │
           ▼
┌──────────────────────┐
│   CYD ESP32 DISPLAY  │
│     I2C SLAVE UI     │
│   TFT Dashboard HMI  │
└──────────────────────┘
```

---

# Key Features

| Category      | Features                                                               |
| ------------- | ---------------------------------------------------------------------- |
| Embedded UI   | Animated splash screen, gradient background, rounded temperature cards |
| Communication | I2C slave communication, real-time updates                             |
| Graphics      | RGB565 image rendering, TFT_eSPI optimization                          |
| Architecture  | Modular codebase, PlatformIO structure                                 |
| Performance   | Lightweight rendering, optimized memory usage                          |

---

# Hardware Requirements

| Component          | Description           |
| ------------------ | --------------------- |
| CYD ESP32-2432S028 | TFT display module    |
| ESP32 Dev Board    | Master controller     |
| PT1000 Sensors     | Temperature sensing   |
| I2C Wiring         | Communication bus     |
| USB Cable          | Programming and power |

---

# Display Specifications

| Parameter        | Value            |
| ---------------- | ---------------- |
| Resolution       | 320 × 240        |
| Driver           | ILI9341_2_DRIVER |
| Interface        | SPI TFT          |
| Orientation      | Landscape        |
| Graphics Library | TFT_eSPI         |

---

# I2C Configuration

## CYD ESP32 Slave Pins

| Signal | GPIO    |
| ------ | ------- |
| SDA    | GPIO 27 |
| SCL    | GPIO 22 |

## I2C Slave Address

```cpp id="4hcrgb"
0x08
```

---

# Repository Structure

```text id="u1c0j6"
CYD_320_240_PT1000_DISPLAY/
│
├── assets/
│   ├── demo.mp4
│   └── logo_preview.png
│
├── include/
│   ├── User_Setup.h
│   └── aowlyf_logo.h
│
├── src/
│   └── main.cpp
│
├── platformio.ini
├── README.md
└── .gitignore
```

---

# TFT_eSPI Configuration

Display configuration is located in:

```text id="dwm39t"
include/User_Setup.h
```

Using the CYD-compatible driver:

```cpp id="ik4x8f"
#define ILI9341_2_DRIVER
```

---

# Quick Start

## Clone Repository

```bash id="81fk54"
git clone https://github.com/Olawalekaybee/CYD_320_240_PT1000_DISPLAY.git
```

## Open in VS Code

Install:

* VS Code
* PlatformIO IDE Extension

---

# Build Firmware

```bash id="ud6f6l"
pio run
```

# Upload Firmware

```bash id="86l58t"
pio run --target upload
```

# Open Serial Monitor

```bash id="12em18"
pio device monitor -b 115200
```

---

# Performance Optimizations

The rendering pipeline is optimized specifically for CYD ESP32 hardware limitations.

Optimizations include:

* Lightweight graphics rendering
* Reduced memory allocation
* Optimized TFT redraw logic
* Stable frame updates
* Efficient embedded UI design
* No heavy sprite rotation operations

---

# Technologies Used

* ESP32
* PlatformIO
* Arduino Framework
* TFT_eSPI
* Embedded C++
* SPI TFT Graphics
* I2C Communication

---

# Future Roadmap

* WiFi telemetry integration
* MQTT cloud dashboard
* SD card logging
* Historical graph visualization
* Touchscreen support
* LVGL migration
* OTA firmware updates
* Alarm and notification system

---

# Author

## Olawale Kaybee

Embedded Systems Engineer
IoT & Smart Device Developer

GitHub:
https://github.com/Olawalekaybee

---

# License

This project is licensed under the MIT License.

---

<div align="center">

### CYD ESP32 Professional Embedded Dashboard

Built using ESP32 + PlatformIO + TFT_eSPI

</div>
