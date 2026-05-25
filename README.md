# Embedded AK9723AJ CO₂ Monitor

**Embedded real-time CO₂ monitoring system for respiratory waveform analysis using AVR128DB48 MCU and AK9723AJ NDIR sensor.**

<div align="center">

[![AVR](https://img.shields.io/badge/AVR-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.microchip.com/)
[![I2C](https://img.shields.io/badge/I2C-0078D4?style=for-the-badge)](https://en.wikipedia.org/wiki/I%C2%B2C)
[![SPI](https://img.shields.io/badge/SPI-FF6B6B?style=for-the-badge)](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface)
[![UART](https://img.shields.io/badge/UART-115200%20baud-00A86B?style=for-the-badge)](https://en.wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter)
[![DAC](https://img.shields.io/badge/DAC-Analog_Output-8A2BE2?style=for-the-badge)](https://en.wikipedia.org/wiki/Digital-to-analog_converter)
[![Capnography](https://img.shields.io/badge/CO₂-Capnography-red?style=for-the-badge)](https://en.wikipedia.org/wiki/Capnography)

**May 2026 | Jin Yuan Chen**

</div>

---
<p align="center">
  <img src="docs/images/system_block_diagram.png" alt="System Block Diagram" style="max-width:100%; height:auto;"/>
</p>
<p align="center">
  <em>Figure 1: System block diagram of the AVR128DB48–AK9723AJ embedded CO₂ monitoring pipeline, illustrating sensor acquisition, real-time processing, and dual-mode output (DAC waveform + SerLCD/UART visualization).</em>
</p>

## System Overview

Embedded real-time CO₂ monitoring system for respiratory waveform (capnography-style) generation. The system uses an AK9723AJ NDIR CO₂ sensor with AVR128DB48 firmware to implement a deterministic acquisition and processing pipeline. Sensor data is read via I²C (TWI), converted to digitalized CO₂ voltage measurement, and distributed to multiple outputs.

The system provides DAC-based analog waveform output, SerLCD visualization via SPI, and USART (115200 baud) terminal control using an interrupt-driven FSM for configuration and calibration. It supports runtime system management and displays CO₂ values in both digital (LCD/UART) and analog (waveform) forms.

---

## Architecture

**AK9723AJ NDIR CO₂ Sensor Layer**
- I²C (TWI) communication interface with AVR128DB48  
- Register-level configuration and calibration control  
- Continuous NDIR CO₂ data acquisition (voltage-based output)  

**AVR128DB48 Processing Core**
- Deterministic real-time firmware execution  
- CO₂ signal processing and ppm conversion pipeline  
- Interrupt-driven USART interface with FSM-based command parsing  
- System state control and fault handling logic  

**DAC + SerLCD Output Layer**
- DAC-based analog reconstruction of respiratory CO₂ waveform  
- SPI-driven SerLCD multi-page visualization system  
- USART telemetry output for runtime diagnostics and system feedback  

---

## Key Features
- Real-time CO₂ concentration computation from NDIR sensor input
- Dual-domain output: digital display + analog waveform generation

<p align="center">
  <img src="docs/images/Command_Parse_FSM.png" alt="Command_Parse_FSM" style="max-width:100%; height:auto;"/>
</p>
<p align="center">
<p align="center">
  <em>Figure 2: Command Parse FSM diagram, logic flow of terminal command characters to AVR microcontroller via USART.</em>
</p>

  
- FSM-based UART terminal interface (115200 baud, interrupt-driven)
- Multi-protocol embedded integration (I²C, SPI, UART, DAC)
- Runtime calibration and sensor configuration via terminal commands
- GPIO-based status indication (boot state and fault signaling)
  
## Communication Interfaces

| Interface | Role |
|---|---|
| **I²C (TWI)** | Sensor acquisition + calibration control |
| **SPI0** | SerLCD display updates |
| **USART (115200)** | Command-line interface |
| **DAC** | Analog CO₂ waveform output |

---

## Application Domain

- Respiratory monitoring (capnography-style waveform analysis)
- ICU / anesthesia / ventilator feedback systems
- Embedded mixed-signal medical sensing platforms

---

## System Characteristics

- Real-time embedded processing pipeline
- Mixed-signal architecture (digital + analog outputs)
- Interrupt-driven firmware design
- Multi-protocol peripheral integration (I²C, SPI, UART, DAC)

<p align="center">
  <img src="docs/images/ak9723aj_to_SerLCD.png" alt="ak9723aj_to_SerLCD" style="max-width:100%; height:auto;"/>
</p>
<p align="center">
<p align="center">
  <em>Figure 3: Voltage measurement and hexdecimal represent of CO₂ concentration read from the AK9723AJ displayed on the SerLCD</em>
</p>
