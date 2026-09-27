# Phase 2: ESD Protection Implementation Guide

## Executive Summary

The PlanBook project has partial ESD protection but several critical interfaces remain unprotected. This guide provides specific component recommendations and implementation guidance for adding ESD protection to vulnerable interfaces.

## Current ESD Protection Status

### ✅ Already Protected:
- **USB D+/D- lines**: Protected through TS3USB30E multiplexers with built-in ESD protection
- **Headphones daughterboard**: Protected with SP0503BAHTG (3-channel TVS array)
- **Partial USB protection**: D2 (ESDS314) protects 4 high-speed data lines

### ❌ Unprotected Interfaces (High Priority):
1. **USB-C CC and SBU lines** (2 connectors × 4 lines each)
2. **Micro SD Card** (6 data lines exposed during card changes)
3. **Keyboard matrix lines** (user interaction point)
4. **Audio jack on motherboard** (if separate from daughterboard)
5. **UART debug connector** (external interface)
6. **DSI display interface** (internal but high-speed)
7. **PCIe M.2 interface** (internal high-speed)

## Priority Implementation Order

### 1. HIGH PRIORITY (Implement First)

#### 1.1 USB-C CC/SBU Lines
**Risk Level**: HIGH - User-facing, frequent plugging, hot-plug events

**Component**: TPD4E02B04-Q1 (Texas Instruments)
- 4-channel ultra-low capacitance TVS array
- 0.25pF capacitance per channel
- ±3.6V working voltage
- IEC 61000-4-2 Level 4 (±15kV)
- Package: DFN2510 (2.5×1.0mm)
- LCSC Part: Check availability

**Implementation**:
- **Quantity**: 2 devices (one per USB-C connector J3 and J14)
- **Location**: Motherboard at positions near USB-C connectors
- **Protected Lines**: CC1, CC2, SBU1, SBU2 on each connector
- **Placement**: Directly at connector pins, minimize trace length

**Alternative**: ESDS304 (TI) - already used in design, add more instances

#### 1.2 Micro SD Card Interface
**Risk Level**: HIGH - Frequent card insertion/removal, exposed contacts

**Component Option A**: PESD3V3X4UHM (Nexperia)
- 4-channel ESD protection array for SD cards
- Very low clamping voltage: 3.7V @ 11A
- 25kV ESD protection
- Package: DFN1308-6 (1.3×0.8mm)
- Protects 4 of the 6 SD card lines

**Component Option B**: EMI9106 (STMicroelectronics)
- Combined EMI filter + ESD protection + termination
- Protects all 6 SD card lines + VCC
- Integrated 40Ω termination resistors
- Package: UDFN-16 (3.3×1.35×0.5mm)
- Higher cost but saves board space

**Implementation**:
- **Quantity**: 1 device (Option A) or 1 device (Option B)
- **Location**: Motherboard near SD card connector J2
- **Protected Lines**: DAT0-3, CLK, CMD (all 6 SD card lines)
- **Placement**: As close as possible to connector J2

**Recommendation**: Use Option B (EMI9106) for comprehensive protection and EMI filtering

### 2. MEDIUM PRIORITY (Implement After High Priority)

#### 2.1 Keyboard Matrix Lines
**Risk Level**: MEDIUM - User interaction point, indirect discharge path

**Component**: TPD8E003 (Texas Instruments)
- 8-channel ESD protection diode array
- Designed specifically for keypads and GPIO
- ±12kV contact, ±15kV air-gap ESD
- 9pF capacitance (acceptable for keyboard scan rates)
- Package: WSON (space-saving)

**Implementation**:
- **Quantity**: Determine based on matrix size (typically 1-2 devices)
- **Location**: Keyboard PCB near MCU or connector to motherboard
- **Protected Lines**: Row and column scan lines
- **Placement**: Near the edge connector or MCU, minimize trace length

**Alternative**: Use individual TVS diodes like ESD5V3L1U if space permits

#### 2.2 Audio Jack (Motherboard)
**Risk Level**: MEDIUM - User-facing, but daughterboard has protection

**Component**: ESD5V3L1B (Infineon)
- Bidirectional TVS diode for audio
- ±5.3V working voltage
- ±20kV ESD protection
- Low dynamic resistance (0.22Ω)
- Package: TSLP-2 (1.0×0.6×0.3mm)

**Implementation**:
- **Quantity**: 3 devices (for L, R, and Mic lines)
- **Location**: Motherboard near audio jack J4
- **Note**: Only needed if J4 is separate from headphones daughterboard

**Recommendation**: Verify if J4 connects to headphones daughterboard. If yes, skip this.

#### 2.3 UART Debug Connector
**Risk Level**: MEDIUM - Development interface, not user-facing

**Component**: TPD1E10B06 (Texas Instruments)
- Single-channel ESD protection
- ±30kV contact/air-gap ESD
- 12pF capacitance
- Package: 0402 or SOD-523

**Implementation**:
- **Quantity**: 2 devices (for TX and RX lines)
- **Location**: Keyboard PCB near UART connector J2
- **Protected Lines**: UART_TX, UART_RX
- **Placement**: Directly at connector pins

### 3. LOW PRIORITY (Optional for Production)

#### 3.1 DSI Display Interface
**Risk Level**: LOW - Internal connector, less frequent access

**Component**: TPD2E009 (Texas Instruments)
- 2-channel ESD protection for high-speed differential interfaces
- 0.7pF capacitance (typical)
- Supports data rates up to 6Gbps
- ±8kV ESD protection
- Package: SOT-23-3 or DRT (1mm²)

**Implementation**:
- **Quantity**: 5 devices (one per differential pair)
- **Location**: Motherboard near display connector
- **Protected Lines**: DSI_D0-3_P/N, DSI_CLK_P/N
- **Placement**: Near display connector, maintain differential impedance

**Alternative**: TPD1E05U06 series (single channel, 0.4pF)

#### 3.2 PCIe M.2 Interface
**Risk Level**: LOW - Internal connector, high-speed

**Component**: TPD2E009 (Texas Instruments) - same as DSI
- 2-channel for differential pairs
- 0.7pF capacitance
- Suitable for PCIe Gen 1/2 speeds

**Implementation**:
- **Quantity**: 3 devices (TX, RX, and CLK pairs)
- **Location**: WiFi PCB near M.2 connector J2
- **Protected Lines**: PCIE3_TX_P/N, PCIE3_RX_P/N, PCIE3_CLK_P/N
- **Placement**: Near M.2 connector, maintain differential impedance

## Implementation Steps in KiCad

### General Procedure:

1. **Open the appropriate PCB file in KiCad**
2. **Add the TVS diode footprints**:
   - Use "Add footprint" tool
   - Search for appropriate package (DFN2510, DFN1308, etc.)
   - Place at recommended coordinates near connectors
3. **Connect to schematic**:
   - Update schematic to add TVS diode symbols
   - Connect to appropriate nets (signal lines to ground)
   - Annotate new components
4. **Run DRC check**:
   - Verify no clearance violations
   - Check trace lengths are minimal
5. **Test**:
   - Verify proper connection with multimeter
   - Test ESD susceptibility if possible

### Footprint Libraries:

Use existing footprint libraries in the project:
- Check if DFN, SOT-23, and other packages are available
- Create new footprints if needed using footprint editor
- Use KiCad's standard libraries as fallback

### Net Assignment:

TVS diodes should be connected:
- **Anode**: To the signal line being protected
- **Cathode**: To ground (GND)
- **Placement**: Between connector and protected IC

## Cost Estimate

| Component | Quantity | Est. Cost per unit | Total Cost |
|-----------|----------|-------------------|------------|
| TPD4E02B04-Q1 (USB-C) | 2 | $0.50 | $1.00 |
| EMI9106 (SD Card) | 1 | $0.80 | $0.80 |
| TPD8E003 (Keyboard) | 2 | $0.40 | $0.80 |
| TPD1E10B06 (UART) | 2 | $0.15 | $0.30 |
| **HIGH PRIORITY TOTAL** | | | **$2.90** |
| TPD2E009 (DSI) | 5 | $0.35 | $1.75 |
| TPD2E009 (PCIe) | 3 | $0.35 | $1.05 |
| **ALL FEATURES TOTAL** | | | **$5.70** |

## Verification Steps

After implementation:

1. **Visual Inspection**:
   - Verify TVS diodes are placed correctly
   - Check orientation (anode/cathode)
   - Ensure no short circuits

2. **Electrical Testing**:
   - Use multimeter to verify proper connection
   - Test signal integrity with oscilloscope
   - Verify no signal degradation

3. **ESD Testing** (if possible):
   - Use ESD gun to test protection
   - Verify device survives specified ESD levels
   - Test with device powered on and off

4. **Signal Integrity**:
   - Measure signal quality on protected lines
   - Verify no excessive capacitance added
   - Check differential pair impedance (for high-speed lines)

## Notes

- **Capacitance is critical** for high-speed lines (USB, DSI, PCIe)
- **Placement is critical** - TVS must be as close as possible to connector
- **Ground connection is critical** - use solid ground plane with minimal inductance
- **Differential pairs** need matched length after TVS placement
- **Existing protection** on USB D+/D- through multiplexers is sufficient for those lines
- **Headphones daughterboard** already has excellent protection

## References

- IEC 61000-4-2 ESD immunity standard
- Texas Instruments ESD protection application notes
- Raspberry Pi hardware design guidelines
- USB-C specification requirements