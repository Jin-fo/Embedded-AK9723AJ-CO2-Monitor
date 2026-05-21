# AVR128DB48 - AK9723AJ CO₂ Medical Monitoring System

**Real-time CO₂ detection with TWI communication, SPI display, USART terminal control, and DAC analog visualization**

---

<div align="center">

[![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![AVR](https://img.shields.io/badge/AVR-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.microchip.com/en-us/products/microcontrollers-and-microprocessors/8-bit-mcus/avr-mcus)
[![I2C](https://img.shields.io/badge/I2C-0078D4?style=for-the-badge&logo=serial&logoColor=white)](https://en.wikipedia.org/wiki/I%C2%B2C)
[![SPI](https://img.shields.io/badge/SPI-FF6B6B?style=for-the-badge&logo=serial&logoColor=white)](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface)

**Version 1.0 | Last Updated: May 2026 | Author: Jin Yuan Chen**

</div>

---

## Overview

This project implements a **real-time CO₂ monitoring system** for medical applications (patient breathing monitoring) using the **AVR128DB48** microcontroller and **AK9723AJ** NDIR CO₂ sensor. The system features bidirectional TWI (I²C) communication with the sensor, SPI interface to a 20×4 SerLCD display, USART terminal control at 115200 baud, and DAC analog output for waveform visualization.

<insert system_block_diagram_here>

*Figure 1: Complete system architecture showing AVR128DB48 connections to AK9723AJ sensor, SerLCD display, DAC output, and USART terminal*

---

## System Architecture

<insert architecture_flow_diagram_here>

*Figure 2: Data flow from sensor acquisition to display and analog output*

### Core Components

| Component | Function | Interface |
|-----------|----------|-----------|
| **AVR128DB48** | Main microcontroller (8-bit, 24MHz) | - |
| **AK9723AJ** | NDIR CO₂ sensor with onboard ADC | TWI (I²C) |
| **SerLCD 20×4** | Character display for CO₂ values | SPI0 |
| **DAC Output** | Analog voltage representing CO₂ level | DAC0 |
| **USART Terminal** | Command/control interface (115200 baud) | USART2, USART3 |
| **Status LED** | Boot indicator & error notification | PORTA PIN7 |

---

## Hardware Requirements

### Required Components

- **AVR128DB48** microcontroller (48-pin package)
- **AK9723AJ** NDIR CO₂ sensor module
- **20×4 SerLCD** display (SparkFun or compatible)
- **LED** with current-limiting resistor (330Ω)
- **DAC output** connection (oscilloscope or analog meter)
- **USB-to-UART** converter (for terminal communication)
- **Power supply**: 5V DC (or 3.3V with level shifting)

### Pin Connections

<insert pinout_diagram_here>

*Figure 3: Detailed pin mapping between AVR128DB48 and peripherals*

| AVR128DB48 Pin | Peripheral | Function |
|----------------|------------|----------|
| **PORTA PIN7** | Status LED | Boot indicator / Error notification |
| **PORTA PIN4** | AK9723AJ | Sensor interrupt input |
| **TWI0 (PC0/PC1)** | AK9723AJ | I²C data (SDA) and clock (SCL) |
| **SPI0 (MOSI/SCK)** | SerLCD | Display data and clock (400ms stability delay) |
| **DAC0** | Analog output | CO₂ level visualization |
| **USART2** | Terminal | Command RX/TX at 115200 baud |
| **USART3** | Debug | Optional debug output |

---

## Software Features

### Core Capabilities

- ✅ **Real-time CO₂ acquisition** from AK9723AJ via bidirectional TWI
- ✅ **SPI display driver** with 400ms stabilization delay
- ✅ **USART terminal interface** at 115200 baud
- ✅ **Interrupt-driven FSM command parser** for ASCII characters
- ✅ **Sensor configuration** via command register writes
- ✅ **DAC analog output** for CO₂ level visualization (medical waveform simulation)
- ✅ **Dual display modes** (enable/disable toggle via terminal)
- ✅ **Multiple display pages** (0, 1, 2) on SerLCD
- ✅ **Error detection** with LED notification via get_AK9723_stats()
- ✅ **Boot self-test** with LED indicator

### Terminal Command System

The terminal accepts **ASCII characters** via USART interrupt. The AVR implements a **Finite State Machine (FSM)** to parse incoming commands.

| Command | Function | ASCII |
|---------|----------|-------|
| **Page 0** | Display main system status | '0' |
| **Page 1** | Display CO₂ measurements (real-time) | '1' |
| **Page 2** | Display sensor configuration | '2' |
| **Toggle Display** | Enable/disable LCD updates | 'T' |
| **Configure Sensor** | Write to AK9723AJ command register | Multi-byte |
| **Calibration** | Trigger sensor calibration | 'C' |

<insert terminal_command_fsm_here>

*Figure 4: Finite state machine (FSM) for terminal command parsing*

### Command Processing Flow
