# AVR128DB48 - AK9723AJ CO₂ Medical Monitoring System

**Real-time CO₂ detection with bidirectional TWI communication, SPI display with 400ms stabilization delay, USART115200 interrupt-driven terminal with FSM command parsing, and DAC analog waveform output for patient breathing monitoring**

---

<div align="center">
[![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![AVR](https://img.shields.io/badge/AVR-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.microchip.com/en-us/products/microcontrollers-and-microprocessors/8-bit-mcus/avr-mcus)
[![I2C](https://img.shields.io/badge/I2C-0078D4?style=for-the-badge&logo=serial&logoColor=white)](https://en.wikipedia.org/wiki/I%C2%B2C)
[![SPI0](https://img.shields.io/badge/SPI0-FF6B6B?style=for-the-badge&logo=serial&logoColor=white)](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface)
[![UART](https://img.shields.io/badge/UART-115200%20baud-00A86B?style=for-the-badge)](https://en.wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter)
[![DAC](https://img.shields.io/badge/DAC-analog%20output-8A2BE2?style=for-the-badge)](https://en.wikipedia.org/wiki/Digital-to-analog_converter)
[![Capnography](https://img.shields.io/badge/Capnography-CO₂%20waveform-red?style=for-the-badge)](https://en.wikipedia.org/wiki/Capnography)
---

**Version 1.0 | Last Updated: May 2026 | Author: Jin Yuan Chen**

</div>

---

## 1. Executive Summary

**System Definition:** An AVR128DB48-based real-time CO₂ monitoring system interfaced with the AK9723AJ NDIR CO₂ sensor via bidirectional TWI (I²C) communication protocol.

**Medical Application Context:** Designed for patient breathing monitoring applications, including capnography-style respiratory assessment and end-tidal CO₂ (EtCO₂) waveform analysis.

**Core Outputs:**
- **CO₂ ppm display** – Real-time concentration shown as floating-point values on 20×4 SerLCD
- **Analog waveform (DAC)** – Mimics medical CO₂ display waveform for patient breathing visualization
- **Terminal control (USART FSM)** – ASCII command interface at 115200 baud with interrupt-driven Finite State Machine parsing

**Key Interfaces Summary:**

| Interface | Peripheral | Role |
|-----------|------------|------|
| **TWI (I²C)** | Bidirectional | AK9723AJ sensor communication, command register access, calibration |
| **SPI0** | Master | SerLCD display control with 400ms stabilization delay |
| **USART** | 115200 baud | Terminal command interface, interrupt-driven ASCII reception |
| **DAC** | Analog output | CO₂ waveform visualization for medical monitoring |

<insert executive_summary_diagram_here>

*Figure 1: Executive summary – complete system block diagram showing AVR128DB48, AK9723AJ sensor, SerLCD display, DAC waveform output, and USART terminal interface*

---
