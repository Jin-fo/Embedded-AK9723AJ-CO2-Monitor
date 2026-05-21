# AVR128DB48 - AK9723AJ CO₂ Medical Monitoring System

**Real-time CO₂ detection with bidirectional TWI communication, SPI display with 400ms stabilization delay, USART115200 interrupt-driven terminal with FSM command parsing, and DAC analog waveform output for patient breathing monitoring**

<div align="center">
  
[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C++_(programming_language))
[![AVR](https://img.shields.io/badge/AVR-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.microchip.com/en-us/products/microcontrollers-and-microprocessors/8-bit-mcus/avr-mcus)
[![I2C](https://img.shields.io/badge/I2C-0078D4?style=for-the-badge&logo=serial&logoColor=white)](https://en.wikipedia.org/wiki/I%C2%B2C)
[![SPI](https://img.shields.io/badge/SPI-FF6B6B?style=for-the-badge&logo=serial&logoColor=white)](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface)
[![UART](https://img.shields.io/badge/UART-115200%20baud-00A86B?style=for-the-badge)](https://en.wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter)
[![DAC](https://img.shields.io/badge/DAC-analog%20output-8A2BE2?style=for-the-badge)](https://en.wikipedia.org/wiki/Digital-to-analog_converter)
[![Capnography](https://img.shields.io/badge/Capnography-CO₂%20waveform-red?style=for-the-badge)](https://en.wikipedia.org/wiki/Capnography)
---

**Version 1.0 | Last Updated: May 2026 | Author: Jin Yuan Chen**

</div>

---

## Table of Contents

- [Executive Summary](#executive-summary)
- [System Overview](#system-overview)
- [Hardware Architecture](#hardware-architecture)
- [Communication Interfaces](#communication-interfaces-twi--spi--usart--dac)
- [AK9723AJ CO₂ Sensor Operation](#ak9723aj-co₂-sensor-operation)
- [Real-Time Data Acquisition & Processing](#real-time-data-acquisition--processing)
- [USART Terminal Control (FSM)](#fsm-based-usart-terminal-control)
- [DAC Waveform Output](#medical-co₂-waveform-output-dac)
- [SerLCD Display System](#display-system-serlcd-spi0)
- [System Optimization](#system-optimization--stability-behavior)
- [Error Handling](#error-handling--status-indication)

---

## Executive Summary

**System Definition:** An AVR128DB48-based real-time CO₂ monitoring system interfaced with the AK9723AJ NDIR CO₂ sensor via bidirectional TWI (I²C) communication protocol.

**Medical Application Context:** Real-time patient breathing monitoring system supporting capnography-style respiratory assessment through CO₂ waveform visualization.

## Core Outputs

- **CO₂ measurement display** – Real-time sensor output derived from digitized voltage levels, converted to CO₂ ppm and shown as floating-point values on 20×4 SerLCD  
- **Analog waveform (DAC)** – DAC-based analog reconstruction of sensor voltage for respiratory waveform visualization  
- **Terminal control (USART FSM)** – Interrupt-driven USART (115200 baud) interface using ASCII commands with FSM-based parsing for AK9723AJ configuration and calibration register control  
- **Multi-page SerLCD output (SPI0)** – Multi-page display system with ~400 ms update delay  
- **Display optimization** – Optional SerLCD disable mode to improve DAC waveform stability and reduce signal jitter  
- **Status indication** – Single GPIO LED used for boot indication and runtime error signaling via `get_AK9723_stats()`  

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
