
**BLE Firmware – EFR32BG**

**📌 Project Overview**

This project demonstrates a Bluetooth Low Energy (BLE) client–server system developed on the EFR32BG13 (Blue Gecko) platform. The firmware enables secure wireless communication between two devices, implementing custom GATT services and optimizing for low-power operation.

**Key highlights:**

GATT Server: Interfaces with a TSL2561 light sensor via I²C and a GPIO-driven buzzer.

GATT Client: Performs service discovery, enables indications, and displays lux & buzzer data on the onboard LCD.

Implements secure numeric comparison pairing to protect transmitted data.

Optimized using LETIMER0-driven sampling, EM2 sleep mode, and peripheral power gating for ultra-low energy consumption.

**⚙️ Features**

**Custom GATT Services**

Real-time lux value monitoring from TSL2561 sensor.

Remote buzzer control with status feedback.

**Secure BLE Communication**

Numeric comparison pairing ensures no unencrypted data transfer.

**Low Power Design**

EM2 sleep mode + LETIMER0 periodic sampling.

Microamp-level idle current draw.

**User Feedback**

Onboard LCD updates with lux and buzzer values in real time.

**🖥️ Hardware Used**

EFR32BG13 (Blue Gecko) Development Boards (Client & Server)

TSL2561 Luminosity Sensor (I²C interface)

GPIO-driven Buzzer

Onboard LCD for displaying data

**🛠️ Tools & Development**

IDE: Simplicity Studio (Silicon Labs)

Language: C (bare-metal firmware)

Protocols: BLE (GATT), I²C, GPIO

Debugging: Energy Profiler, Oscilloscope, Logic Analyzer

**🚀 Getting Started
Prerequisites**

Install Simplicity Studio

Flash firmware to EFR32BG13 boards (Server & Client)

Connect TSL2561 sensor (I²C) and buzzer (GPIO) to the Server board

**Usage**

Power on both Client & Server boards

Pair using secure numeric comparison

Server transmits lux sensor values and buzzer status

Client receives and displays updates on its onboard LCD

**📚 Learnings & Outcomes**

Developed skills in BLE stack, GATT services, and pairing mechanisms.

Gained hands-on experience with low-power design in embedded systems.

Strengthened debugging and verification using Energy Profiler & hardware tools.
