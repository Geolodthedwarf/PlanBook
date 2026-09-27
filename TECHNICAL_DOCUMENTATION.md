# PlanBook Technical Documentation

## Executive Summary

This document provides comprehensive technical documentation for the PlanBook project, including system architecture, power distribution, signal interfaces, and design decisions.

---

## Table of Contents

1. [System Overview](#system-overview)
2. [Architecture](#architecture)
3. [Power Distribution](#power-distribution)
4. [Signal Interfaces](#signal-interfaces)
5. [Component Descriptions](#component-descriptions)
6. [Design Rules](#design-rules)
7. [Manufacturing Specifications](#manufacturing-specifications)
8. [Test Procedures](#test-procedures)
9. [Troubleshooting Guide](#troubleshooting-guide)

---

## System Overview

### Project Description

PlanBook is a portable computing device based on the Raspberry Pi RP2040 microcontroller, featuring:
- USB-C power delivery and charging
- Keyboard input with RGB backlight
- WiFi connectivity via M.2 module
- Headphone audio output
- Display interface (DSI)
- Multiple peripheral interfaces

### Key Specifications

| Parameter | Value |
|-----------|-------|
| Main MCU | Raspberry Pi RP2040 (Dual-core Cortex-M0+ @ 133MHz) |
| Power Input | USB-C PD 2.0, 4-21V |
| Battery | 2-4S Li-ion, managed by MAX17320 |
| Display | DSI interface |
| Connectivity | WiFi (M.2), USB 3.0 hub |
| Keyboard | Mechanical with RGB backlight |
| Audio | 3.5mm headphone jack |
| Board Thickness | 1.6mm (standardized) |
| Layers | 2-6 layers depending on PCB |

---

## Architecture

### Block Diagram

```
┌─────────────────────────────────────────────────────────────┐
│                     PlanBook System                       │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│  ┌──────────────┐    ┌──────────────┐    ┌──────────────┐ │
│  │  USB-C Port  │───▶│ USB PD Ctrl │───▶│ Power Switch │ │
│  └──────────────┘    └──────────────┘    └──────────────┘ │
│          │                  │                   │        │
│          ▼                  ▼                   ▼        │
│  ┌──────────────┐    ┌──────────────┐    ┌──────────────┐ │
│  │ Battery Charger│───▶│   Battery    │───▶│   Power Mgmt  │ │
│  └──────────────┘    └──────────────┘    └──────────────┘ │
│                                                              │
│  ┌──────────────────────────────────────────────────────┐  │
│  │              Motherboard                             │  │
│  ├──────────────────────────────────────────────────────┤  │
│  │  ┌──────────┐  ┌──────────┐  ┌──────────┐         │  │
│  │  │  RP2040  │  │ USB Hub  │  │  Display  │         │  │
│  │  └──────────┘  └──────────┘  └──────────┘         │  │
│  │       │            │            │                │  │
│  │       ▼            ▼            ▼                │  │
│  │  ┌──────────┐  ┌──────────┐  ┌──────────┐         │  │
│  │  │ Keyboard │  │  WiFi    │  │ Headphone │         │  │
│  │  └──────────┘  └──────────┘  └──────────┘         │  │
│  └──────────────────────────────────────────────────────┘  │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

### PCB Board Breakdown

| Board | Layers | Purpose | Key Components |
|-------|--------|---------|----------------|
| planbook-motherboard | 6 | Main computing hub | RP2040, USB hub, display driver |
| planbook-charger | 4 | Battery charging & management | MP2650, MAX17320, NX20P5090 |
| planbook-keyboard-kailh-ortho | 4 | Keyboard input | MCU, RGB LEDs, switches |
| planbook-wifi | 4 | WiFi connectivity | M.2 WiFi module, buck converter |
| planbook-headphones | 2 | Audio output | Audio amp, ESD protection |

---

## Power Distribution

### Power Rails

| Rail | Voltage | Source | Current Capacity | Purpose |
|------|---------|--------|-----------------|---------|
| VBAT | 3.7-16.8V | Battery | 5A (charger) | Battery power |
| VIN_CHG | 4-21V | USB-C PD | 5A | Charger input |
| 5V0 | 5V | USB PD switch | 5A | USB hub, peripherals |
| 3V3 | 3.3V | LDOs/buck converters | 3A | Main logic power |
| 1V8 | 1.8V | LDO | 1A | Specific ICs |
| LED_PWR | 3.3V | LDO | 500mA | Keyboard backlight |

### Power Tree

```
USB-C (4-21V)
    │
    ▼
NX20P5090 (USB PD Switch)
    │
    ├─▶ 5V0 (5A max)
    │     ├─▶ USB Hub (TUSB8041)
    │     ├─▶ Peripherals
    │     └─▶ Other 5V loads
    │
    ▼
MP2650 (Battery Charger)
    │
    ├─▶ Battery (2-4S Li-ion)
    │
    └─▶ System Power
          │
          ├─▶ 3V3 (main rail)
          │     ├─▶ RP2040
          │     ├─▶ WiFi module
          │     ├─▶ Display
          │     └─▶ Other 3.3V logic
          │
          ├─▶ 1V8 (LDO)
          │     └─▶ Specific ICs
          │
          └─▶ LED_PWR
                └─▶ Keyboard RGB LEDs
```

### Power Sequencing

1. **Power On Sequence:**
   - USB-C connected → CC detection → PD negotiation
   - NX20P5090 enables VBUS → 5V available
   - MP2650 detects input → Enables charging
   - Battery powers system → 3V3 rail comes up
   - RP2040 boots → Peripherals initialize

2. **Power Off Sequence:**
   - System shutdown requested
   - RP2040 shuts down peripherals
   - 3V3 rail disabled
   - Battery charging continues if USB-C connected

---

## Signal Interfaces

### USB Interfaces

#### USB 3.0 Hub (TUSB8041)
- **Upstream:** USB 3.0 (5Gbps) to host
- **Downstream:** 4× USB 3.0 ports
- **Backward compatible:** USB 2.0 (480Mbps)
- **Power switching:** Per-port or ganged
- **Control:** I2C interface

#### USB-C PD (FUSB302)
- **Standard:** USB Type-C 1.3
- **Power Delivery:** PD 2.0 up to 100W
- **Configuration:** DRP/SRC/SNK
- **Control:** I2C (address 0x22)
- **Dead battery:** Supported

#### USB 2.0 Multiplexers (TS3USB30E - 4 instances)
- **Function:** 1:2 multiplexing
- **Bandwidth:** 1400MHz
- **ESD protection:** Integrated
- **On-resistance:** 6000mΩ

### Display Interface

#### DSI (Display Serial Interface)
- **Standard:** MIPI DSI
- **Lanes:** 4 data lanes + 1 clock lane
- **Speed:** Up to 10Gbps (Gen 2.0)
- **Multiplexer:** TMUXHS4446 (USB-C Alt Mode)
- **Control:** I2C (address 0x54)

### Wireless Interface

#### WiFi (M.2 Module)
- **Standard:** WiFi (specific module dependent)
- **Interface:** PCIe Gen 1/2
- **Speed:** PCIe 2.5Gbps (Gen 1)
- **Power:** 3.3V via buck converter
- **Antenna:** On-module or via connector

### Audio Interface

#### Headphone Output
- **Connector:** 3.5mm jack
- **Amplifier:** Audio amplifier IC
- **Channels:** Stereo (L/R)
- **ESD protection:** SP0503BAHTG (3-channel TVS)
- **Power:** 3.3V

### Debug Interfaces

#### SWD (Serial Wire Debug)
- **Target:** RP2040
- **Signals:** SWDIO, SWCLK, GND
- **Voltage:** 3.3V
- **Purpose:** Programming and debugging

#### UART
- **Baud rate:** Up to 3Mbps
- **Signals:** TX, RX, 3.3V, GND
- **Purpose:** Console/debug output
- **USB bridge:** CY7C65215

#### I2C
- **Speed:** Up to 400kHz
- **Signals:** SDA, SCL, 3.3V, GND
- **Address space:** Multiple devices
- **Purpose:** Sensor and control communication

---

## Component Descriptions

### Main Microcontroller (RP2040)

**Part:** Raspberry Pi RP2040
**Package:** QFN-56 (7×7mm)
**Specs:**
- Dual-core Cortex-M0+ @ 133MHz
- 264KB on-chip SRAM
- 30 GPIO pins
- USB 1.1 device controller
- 8 PIO state machines
- On-chip bootloader (USB DFU)

**Key Features:**
- Flexible GPIO with multiplexing
- High-performance PIO for custom protocols
- Low power consumption
- Excellent documentation and tooling

### Battery Charger (MP2650)

**Part:** MPS MP2650GV-0000-Z
**Package:** QFN-30 (4×5mm)
**Specs:**
- 2-4S Li-ion charging
- 4-21V input range
- 5A charge current
- NVDC power path management
- USB OTG 5V/3A output
- I2C control interface

**Key Features:**
- Simultaneous charging and system power
- Battery fuel gauge integration
- Input voltage regulation
- Thermal protection

### Battery Fuel Gauge (MAX17320)

**Part:** Maxim MAX17320G20+
**Package:** QFN-24 (4×4mm) with thermal vias
**Specs:**
- 2-4S Li-ion support
- ModelGauge m5 algorithm
- 38µA quiescent current
- SHA-256 authentication
- Cell balancing
- Integrated protection

**Key Features:**
- Accurate SOC estimation
- Low power consumption
- Security features
- Protection functions

### USB Hub (TUSB8041)

**Part:** Texas Instruments TUSB8041IRGCR
**Package:** QFN-64 (9×9mm) with thermal pad
**Specs:**
- 4-port USB 3.0 hub
- 5Gbps upstream and downstream
- USB 2.0 backward compatibility
- I2C configuration interface
- Per-port power switching

**Key Features:**
- High-speed USB support
- Flexible power management
- Configurable via I2C

### USB-C PD Controller (FUSB302)

**Part:** onsemi FUSB302BMPX
**Package:** WQFN-14 (2.5×2.5mm)
**Specs:**
- USB Type-C 1.3 compliant
- USB PD 2.0 support
- I2C interface (address 0x22)
- CC pin detection and control
- Dead battery support

**Key Features:**
- PD negotiation
- Type-C configuration
- Low power consumption

---

## Design Rules

### Board Specifications

| Parameter | Value |
|-----------|-------|
| Standard Board Thickness | 1.6mm |
| Copper Thickness | 0.035mm (1oz) |
| Dielectric Material | FR4 (εr=4.5) |
| Copper Finish | ENIG |
| Solder Mask | Black |
| Silkscreen | White |

### Trace Width Rules

| Type | Minimum | Default | Power |
|------|---------|---------|-------|
| Signal | 0.15mm | 0.2mm | 0.3mm |
| High-current | 0.25mm | 0.4mm | 0.6mm |
| High-speed | 0.15mm | 0.15mm | N/A |

### Clearance Rules

| Type | Default | Power | High-speed |
|------|---------|-------|------------|
| Default | 0.15mm | 0.2mm | 0.18mm |
| Minimum | 0.1mm | 0.1mm | 0.1mm |

### Via Rules

| Type | Minimum | Default | Power |
|------|---------|---------|-------|
| Standard | 0.4mm/0.2mm | 0.6mm/0.3mm | 0.8mm/0.4mm |
| Micro | 0.2mm/0.1mm | 0.3mm/0.15mm | N/A |

---

## Manufacturing Specifications

### Panelization

**Standard Panel Size:** 100mm × 100mm
**Tooling Holes:** 1.6mm diameter at panel corners
**Fiducials:** 1mm copper with 0.5mm opening (3 per panel)
**Spacing:** 5mm between boards

### Assembly

**Solder Paste:** Type 4 or 5, no-clean
**Reflow Profile:** Lead-free (Sn-Ag-Cu)
**Inspection:** AOI recommended
**Electrical Test:** Flying probe or bed-of-nails

### Quality Control

**DRC:** Design rule check before manufacturing
**ERC:** Electrical rule check before manufacturing
**First Article Inspection:** Required for first production run
**Statistical Process Control:** Recommended for volume production

---

## Test Procedures

### Incoming Inspection

1. **Visual Inspection**
   - Check for physical damage
   - Verify silkscreen alignment
   - Check solder mask quality

2. **Dimensional Check**
   - Verify board dimensions
   - Check hole sizes
   - Verify layer stackup

### In-Circuit Test (ICT)

1. **Power Rail Verification**
   - Measure all power rails
   - Check voltage levels
   - Verify current capability

2. **Component Verification**
   - Check resistor values
   - Check capacitor values
   - Verify IC presence

### Functional Test

1. **Power Up Test**
   - Apply power
   - Verify power sequence
   - Check current draw

2. **Interface Test**
   - Test USB ports
   - Test display interface
   - Test audio output

3. **Communication Test**
   - Test I2C communication
   - Test UART console
   - Test WiFi connectivity

---

## Troubleshooting Guide

### Power Issues

#### Problem: Device won't power on

**Possible Causes:**
1. Battery not charged
2. USB-C not providing power
3. Power switch failure
4. Short circuit on power rail

**Troubleshooting Steps:**
1. Measure battery voltage (should be 3.7-4.2V per cell)
2. Check USB-C VBUS voltage (should be 5V or negotiated PD voltage)
3. Check 3V3 rail (should be 3.3V ±5%)
4. Check for short circuits with ohmmeter

#### Problem: Excessive current draw

**Possible Causes:**
1. Short circuit
2. Component failure
3. Incorrect configuration

**Troubleshooting Steps:**
1. Measure current on each power rail
2. Check thermal imaging for hot components
3. Disable peripherals one by one
4. Check firmware for incorrect configuration

### USB Issues

#### Problem: USB not recognized

**Possible Causes:**
1. USB hub not powered
2. USB data lines not connected
3. Firmware issue
4. ESD damage

**Troubleshooting Steps:**
1. Check 5V rail on USB hub
2. Verify USB data lines with oscilloscope
3. Try different USB cable
4. Check ESD protection devices

### Display Issues

#### Problem: No display output

**Possible Causes:**
1. Display not powered
2. DSI connection issue
3. Multiplexer not configured
4. Display firmware issue

**Troubleshooting Steps:**
1. Check display power supply
2. Verify DSI clock with oscilloscope
3. Check I2C communication with multiplexer
4. Try known-good display

### Audio Issues

#### Problem: No audio output

**Possible Causes:**
1. Audio amp not powered
2. No input signal
3. Headphone jack issue
4. Muted in software

**Troubleshooting Steps:**
1. Check audio amp power supply
2. Verify audio input signal with oscilloscope
3. Try different headphones
4. Check software mixer settings

---

## Revision History

| Revision | Date | Changes | Author |
|----------|------|---------|--------|
| 1.0 | 2024-01 | Initial documentation | Devin |
| 1.1 | 2024-01 | Added component analysis | Devin |
| 1.2 | 2024-01 | Added USB interface details | Devin |

---

## References

- RP2040 Datasheet (Raspberry Pi)
- MP2650 Datasheet (MPS)
- MAX17320 Datasheet (Maxim)
- TUSB8041 Datasheet (Texas Instruments)
- FUSB302 Datasheet (onsemi)
- USB Type-C Specification
- USB Power Delivery Specification
- KiCad Documentation

---

## Appendices

### Appendix A: Component Cross-Reference

See PHASE4_1_COMPONENT_SUMMARY.md for detailed component recommendations.

### Appendix B: Design Rule Files

See planbook-design-rules.kicad_dru for detailed design rules.

### Appendix C: Implementation Guides

See PHASE2_* and PHASE3_* guides for specific implementation details.