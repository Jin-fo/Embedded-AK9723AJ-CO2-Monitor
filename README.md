# AK9723 Medical CO₂ Breathing Monitor

**AVR128DB48 | NDIR CO₂ Sensor | Real-Time Capnography | Multi-Protocol Interface**
[![Platform](https://img.shields.io/badge/platform-AVR128DB48-blue)]()
[![TWI](https://img.shields.io/badge/TWI-I2C-orange)]()
[![SPI](https://img.shields.io/badge/SPI-display%20interface-blue)]()
[![USART](https://img.shields.io/badge/USART-115200%20baud-green)]()
[![DAC](https://img.shields.io/badge/DAC-analog%20output-purple)]()
[![Application](https://img.shields.io/badge/application-Medical%20CO₂-red)]()
---

## 📋 Table of Contents

- [Executive Summary](#executive-summary)
- [Key Features](#key-features)
- [System Architecture](#system-architecture)
- [AK9723 CO₂ Sensor Integration](#ak9723-co₂-sensor-integration)
- [Medical Breathing Monitor Features](#medical-breathing-monitor-features)
- [Terminal Command System](#terminal-command-system)
- [Multi-Page Display System](#multi-page-display-system)
- [Performance & Optimization](#performance--optimization)
- [Hardware Connections](#hardware-connections)
- [Build & Flash Instructions](#build--flash-instructions)
- [Terminal Command Reference](#terminal-command-reference)
- [Troubleshooting](#troubleshooting)
- [Version History](#version-history)

---

## Executive Summary

The **AK9723 Medical CO₂ Breathing Monitor** is a professional-grade embedded platform designed for **patient respiratory monitoring (capnography)**. Built around the **AVR128DB48 microcontroller** and **Asahi Kasei Microdevices AK9723 NDIR CO₂ sensor**, this system delivers real-time carbon dioxide concentration measurement with:

- DAC-based analog CO₂ waveform output derived from sensor ADC voltage for respiratory visualization  
- Interrupt-driven USART (115200 baud) terminal interface using ASCII commands  
- FSM command parser for AK9723AJ sensor configuration and calibration register control  
- Multi-page SerLCD (SPI0) interface with ~400 ms update delay
- Optional display disable for improved analog stability  
- Single GPIO LED used for boot indication and runtime error signaling via `get_AK9723_stats()`  

**Target Applications:** ICU bedside monitoring, ventilator integration, anesthesia gas analysis, and emergency respiratory monitoring.
