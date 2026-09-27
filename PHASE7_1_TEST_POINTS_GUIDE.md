# Phase 7.1: Test Point Implementation Guide

## Executive Summary

This guide provides detailed recommendations for adding comprehensive test points to the PlanBook PCBs for manufacturing testing, debugging, and field service.

## Test Point Strategy

### Test Point Categories

1. **Power Rails** - Voltage measurement points
2. **Critical Signals** - Signal integrity verification
3. **Status Signals** - LED control, power good, reset
4. **Debug Interfaces** - SWD, UART, I2C access
5. **Analog Signals** - Battery current, temperature, audio

### Test Point Specifications

**Standard Test Point:**
- **Pad size:** 1.0mm diameter (0402 pad)
- **Solder mask opening:** 1.2mm diameter
- **Layer:** Top layer (F.Cu) or Bottom layer (B.Cu)
- **Plating:** Non-plated (test point) or plated (if needed for connection)
- **Clearance:** 0.3mm from other copper
- **Labeling:** Silkscreen text (0.8mm height minimum)

**Alternative Test Point Options:**
- **Solder pin:** 0.8mm diameter pin, 2mm height
- **Edge connector:** Gold-plated fingers on board edge
- **Via test point:** Plated via with larger pad (for high-density areas)

---

## Motherboard Test Points

### Power Rail Test Points

| Test Point | Net | Location | Purpose | Priority |
|------------|-----|----------|---------|----------|
| TP_VBAT | Battery voltage | Near battery connector | Battery voltage monitoring | HIGH |
| TP_3V3 | 3.3V main | Near RP2040 | Main 3.3V rail verification | HIGH |
| TP_5V0 | 5V USB | Near USB hub | USB 5V rail verification | HIGH |
| TP_1V8 | 1.8V LDO | Near TLV757 | 1.8V rail verification | MEDIUM |
| TP_CHG_VIN | Charger input | Near charger connector | Charger input voltage | MEDIUM |
| TP_VBUS | USB VBUS | Near USB-C connector | USB VBUS measurement | HIGH |

**Recommended Locations:**
- TP_VBAT: Near battery connector J1, at (X, Y) coordinates
- TP_3V3: Near RP2040 U8, at (74.25, 82)
- TP_5V0: Near USB hub U25, at (173.5, 125)
- TP_1V8: Near LDO U4, at (appropriate location)
- TP_CHG_VIN: Near charger interface connector
- TP_VBUS: Near USB-C connector J3 or J14

### Critical Signal Test Points

| Test Point | Signal | Location | Purpose | Priority |
|------------|--------|----------|---------|----------|
| TP_USB_D_P | USB D+ | Near USB connector | USB signal integrity | MEDIUM |
| TP_USB_D_N | USB D- | Near USB connector | USB signal integrity | MEDIUM |
| TP_I2C_SDA | I2C SDA | Near I2C bus | I2C communication test | MEDIUM |
| TP_I2C_SCL | I2C SCL | Near I2C bus | I2C communication test | MEDIUM |
| TP_UART_TX | UART TX | Near UART connector | Debug UART access | HIGH |
| TP_UART_RX | UART RX | Near UART connector | Debug UART access | HIGH |

### Status Signal Test Points

| Test Point | Signal | Location | Purpose | Priority |
|------------|--------|----------|---------|----------|
| TP_LED_PWR | LED power | Near LED resistors | LED control verification | LOW |
| TP_PG_MAIN | Power good main | Near power management | Power status verification | MEDIUM |
| TP_RESET_N | Reset (active low) | Near RP2040 | Reset state verification | HIGH |
| TP_BOOT0 | Boot select | Near RP2040 | Boot mode verification | MEDIUM |

### Debug Interface Test Points

| Test Point | Signal | Location | Purpose | Priority |
|------------|--------|----------|---------|----------|
| TP_SWDIO | SWDIO | Near RP2040 | Programming/debug access | HIGH |
| TP_SWCLK | SWCLK | Near RP2040 | Programming/debug access | HIGH |
| TP_SWD_GND | GND for SWD | Near RP2040 | SWD ground reference | HIGH |

**Recommended SWD Header:**
- Create 3-pin header (SWDIO, SWCLK, GND)
- Placement: Near RP2040 U8
- Pin pitch: 1.27mm (standard 0.05")
- Header type: Pogo pin or through-hole

### Analog Signal Test Points

| Test Point | Signal | Location | Purpose | Priority |
|------------|--------|----------|---------|----------|
| TP_BAT_I_SENSE | Battery current sense | Near MAX17320 | Battery current monitoring | MEDIUM |
| TP_TEMP | Temperature sensor | Near temperature sensor | Thermal monitoring | LOW |
| TP_AUDIO_L | Audio left | Near audio jack | Audio signal verification | LOW |
| TP_AUDIO_R | Audio right | Near audio jack | Audio signal verification | LOW |

---

## Charger Board Test Points

### Power Rail Test Points

| Test Point | Net | Location | Purpose | Priority |
|------------|-----|----------|---------|----------|
| TP_CHG_VIN | Charger input | Near connector | Input voltage verification | HIGH |
| TP_CHG_VBAT | Battery voltage | Near battery connector | Battery voltage monitoring | HIGH |
| TP_5V0 | 5V output | Near NX20P5090 | USB PD output verification | HIGH |
| TP_CC1 | CC1 | Near USB-C | CC line monitoring | MEDIUM |
| TP_CC2 | CC2 | Near USB-C | CC line monitoring | MEDIUM |

### Control Signal Test Points

| Test Point | Signal | Location | Purpose | Priority |
|------------|--------|----------|---------|----------|
| TP_I2C_SDA | I2C SDA | Near MP2650 | Charger I2C access | MEDIUM |
| TP_I2C_SCL | I2C SCL | Near MP2650 | Charger I2C access | MEDIUM |
| TP_EN_CHG | Charger enable | Near MP2650 | Charger control verification | MEDIUM |

---

## Keyboard Board Test Points

### Power Rail Test Points

| Test Point | Net | Location | Purpose | Priority |
|------------|-----|----------|---------|----------|
| TP_3V3_KBD | 3.3V keyboard | Near MCU | Keyboard 3.3V verification | HIGH |
| TP_LED_PWR | LED power | Near LED connector | Keyboard LED power | MEDIUM |

### Signal Test Points

| Test Point | Signal | Location | Purpose | Priority |
|------------|--------|----------|---------|----------|
| TP_UART_TX | UART TX | Near UART connector J2 | Debug UART access | HIGH |
| TP_UART_RX | UART RX | Near UART connector J2 | Debug UART access | HIGH |
| TP_I2C_SDA | I2C SDA | Near MCU | Keyboard I2C access | MEDIUM |
| TP_I2C_SCL | I2C SCL | Near MCU | Keyboard I2C access | MEDIUM |

---

## WiFi Board Test Points

### Power Rail Test Points

| Test Point | Net | Location | Purpose | Priority |
|------------|-----|----------|---------|----------|
| TP_3V3_WIFI | 3.3V WiFi | Near M.2 connector | WiFi 3.3V verification | HIGH |
| TP_PCIE_VDD | PCIe power | Near M.2 connector | PCIe power verification | MEDIUM |

### Signal Test Points

| Test Point | Signal | Location | Purpose | Priority |
|------------|--------|----------|---------|----------|
| TP_PCIE_TX_P | PCIe TX+ | Near M.2 connector | PCIe signal verification | MEDIUM |
| TP_PCIE_TX_N | PCIe TX- | Near M.2 connector | PCIe signal verification | MEDIUM |
| TP_PCIE_RX_P | PCIe RX+ | Near M.2 connector | PCIe signal verification | MEDIUM |
| TP_PCIE_RX_N | PCIe RX- | Near M.2 connector | PCIe signal verification | MEDIUM |

---

## Headphones Board Test Points

### Power Rail Test Points

| Test Point | Net | Location | Purpose | Priority |
|------------|-----|----------|---------|----------|
| TP_3V3_HP | 3.3V headphones | Near audio IC | Headphones 3.3V verification | HIGH |

### Signal Test Points

| Test Point | Signal | Location | Purpose | Priority |
|------------|--------|----------|---------|----------|
| TP_AUDIO_L | Audio left | Near audio jack | Audio signal verification | MEDIUM |
| TP_AUDIO_R | Audio right | Near audio jack | Audio signal verification | MEDIUM |

---

## Test Point Footprint Library

### Standard Test Point Footprint

**Footprint Name:** TestPoint_1mm_Diameter

**Footprint Definition:**
```
(module TestPoint_1mm_Diameter
  (layer "F.Cu")
  (attr board_only exclude_from_pos_files exclude_from_bom)
  (pad "1" thru_circle
    (at 0 0)
    (size 1 1)
    (drill 0.5)
    (layers "*.Cu")
    (remove_unused_layers no)
  )
  (fp_text reference "TP*" (at 0 1.5) (layer "F.SilkS")
    (effects (font (size 0.8 0.8) (thickness 0.15)))
  )
)
```

**Alternative - Non-plated test point:**
```
(module TestPoint_1mm_NonPlated
  (layer "F.Cu")
  (attr board_only exclude_from_pos_files exclude_from_bom)
  (pad "1" circle
    (at 0 0)
    (size 1 1)
    (layers "F.Cu")
  )
  (fp_text reference "TP*" (at 0 1.5) (layer "F.SilkS")
    (effects (font (size 0.8 0.8) (thickness 0.15)))
  )
)
```

### SWD Header Footprint

**Footprint Name:** PinHeader_1x27_P1.27mm

**Footprint Definition:**
```
(module PinHeader_1x27_P1.27mm_Vertical
  (layer "F.Cu")
  (description "3-pin 1.27mm pitch header for SWD")
  (pad "1" thru_rect
    (at 0 0)
    (size 1.27 1.27)
    (drill 0.8)
    (layers "*.Cu")
  )
  (pad "2" thru_rect
    (at 1.27 0)
    (size 1.27 1.27)
    (drill 0.8)
    (layers "*.Cu")
  )
  (pad "3" thru_rect
    (at 2.54 0)
    (size 1.27 1.27)
    (drill 0.8)
    (layers "*.Cu")
  )
  (fp_text reference "J_SWD" (at 0 2) (layer "F.SilkS")
    (effects (font (size 1 1) (thickness 0.15)))
  )
)
```

---

## Implementation Steps in KiCad

### Step 1: Create Test Point Footprints

1. **Open Footprint Editor**
   - File → New Footprint
   - Set library name: planbook-testpoints

2. **Create Standard Test Point**
   - Add pad: Type "SMD" or "Through-hole"
   - Set size: 1.0mm diameter
   - Set position: (0, 0)
   - Add reference text
   - Save as "TestPoint_1mm"

3. **Create SWD Header**
   - Add 3 through-hole pads
   - Set pitch: 1.27mm
   - Pin 1: SWDIO
   - Pin 2: SWCLK
   - Pin 3: GND
   - Save as "PinHeader_SWD_3pin"

### Step 2: Add Test Points to Schematic

1. **Open Schematic**
   - Open planbook-motherboard.kicad_sch
   - Add test point symbols
   - Connect to appropriate nets
   - Annotate test points (TP1, TP2, etc.)

2. **Add SWD Header**
   - Add 3-pin header symbol
   - Connect to SWDIO, SWCLK, GND
   - Label as "J_SWD"

### Step 3: Update PCB

1. **Open PCB Editor**
   - Open planbook-motherboard.kicad_pcb
   - Use "Update PCB from Schematic"
   - Place test points at recommended locations
   - Ensure adequate clearance
   - Add silkscreen labels

2. **Verify Placement**
   - Check clearance from components
   - Verify accessibility for probes
   - Ensure no signal interference
   - Run DRC check

### Step 4: Repeat for Other PCBs

Repeat steps 1-3 for:
- planbook-charger
- planbook-keyboard-kailh-ortho
- planbook-wifi
- planbook-headphones

---

## Test Point Labeling

### Silkscreen Label Format

**Standard Format:**
```
TP_3V3
```

**Descriptive Format:**
```
TP_VBAT (3.7V-4.2V)
```

**Color Coding (if possible):**
- Power rails: Red text
- Ground: Black text
- Signals: Blue text
- Debug: Green text

### Label Placement

- Place 0.5mm from test point pad
- Use 0.8mm text height minimum
- Ensure text doesn't overlap with pads
- Orient text for readability

---

## Manufacturing Test Considerations

### Bed-of-Nails Testing

**Test Point Requirements:**
- Minimum 1.0mm pad size for probe access
- 2.54mm center-to-center spacing preferred
- No tall components within 5mm of test points
- Test points on one side of board preferred

### Flying Probe Testing

**Test Point Requirements:**
- Minimum 0.5mm pad size
- 1.27mm center-to-center spacing acceptable
- Can test both sides of board
- Tighter spacing possible

### AOI/ICT Testing

**Test Point Requirements:**
- May use vias as test points
- Smaller pads acceptable
- Bed-of-nails fixture may be used

---

## Verification Steps

After implementing test points:

1. **Visual Inspection**
   - Verify all test points are present
   - Check labeling is correct
   - Ensure proper clearance

2. **Electrical Verification**
   - Use multimeter to verify connections
   - Measure voltages at power test points
   - Check for shorts to ground

3. **Accessibility Verification**
   - Ensure probes can access all test points
   - Check for component interference
   - Verify sufficient spacing

4. **DRC Check**
   - Run design rules check
   - Verify no clearance violations
   - Check for short circuits

---

## Test Point Documentation

### Create Test Point Location Document

**Document Contents:**
- Board name and revision
- Test point reference designator
- Net name
- Coordinates (X, Y)
- Expected voltage/value
- Test procedure

**Example Table:**

| Ref | Net | Location (X, Y) | Expected Value | Test Procedure |
|-----|-----|---------------|----------------|----------------|
| TP1 | 3V3 | (74.25, 82) | 3.3V ±5% | Measure with multimeter |
| TP2 | VBAT | (near J1) | 3.7-4.2V | Measure with multimeter |
| J1 | SWD | (near U8) | - | Connect SWD debugger |

---

## Expected Benefits

### Manufacturing Benefits
- Faster electrical testing
- Reduced test time
- Improved fault isolation
- Lower test costs

### Debugging Benefits
- Easier firmware debugging
- Faster fault diagnosis
- Better field service capability
- Reduced development time

### Quality Benefits
- Improved product reliability
- Better quality control
- Easier validation testing
- Enhanced traceability

---

## Notes

- **Test point priority:** Focus on power rails and critical signals first
- **Accessibility:** Ensure test points are accessible with standard probes
- **Clearance:** Maintain minimum 0.3mm clearance from other copper
- **Labeling:** Clear, readable labels are essential for efficient testing
- **Ground reference:** Include ground test points for differential measurements
- **High-frequency signals:** Use 50Ω terminated test points for RF signals

---

## References

- IPC-2221 Generic Standard on Printed Board Design
- IPC-9251 Requirements for Testability
- KiCad PCB Editor Documentation
- Manufacturer test specifications