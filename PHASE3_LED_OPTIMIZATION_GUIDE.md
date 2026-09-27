# Phase 3: LED Current Limiting Resistor Optimization Guide

## Executive Summary

The PlanBook project has severely under-driven LEDs that will result in poor visibility. Status LEDs are operating at only 2-4% of their rated current, making them barely visible. This guide provides specific resistor value changes to achieve proper LED brightness.

## Current LED Status

### 🔴 CRITICAL: Motherboard LEDs Severely Under-Driven

**LEDs:**
- D1 (LED_NVME) - ROHM SMLEN3WBC8W1 white LED
- D23 (LED_NVME) - ROHM SMLEN3WBC8W1 white LED  
- D8 (status LED) - ROHM SMLEN3WBC8W1 white LED
- D9 (status LED) - ROHM SMLEN3WBC8W1 white LED

**Current Limiting Resistors:**
- R1 = 1kΩ (for D1)
- R110 = 1kΩ (for D23)
- Additional 1kΩ resistors for D8 and D9

**Problem:**
- Calculated current: only 0.4mA (typical)
- LED rating: 10mA max continuous
- Visibility: **Very dim or barely visible**
- Operating at only **4% of rated current**

### 🟡 MODERATE: WiFi LEDs Under-Driven

**LEDs:**
- D1 - Kingbright APT1608SURCK red LED
- D2 - Kingbright APT1608SURCK red LED

**Current Limiting Resistors:**
- R3 = 2kΩ (for D1)
- R4 = 2kΩ (for D2)

**Problem:**
- Calculated current: only 0.675mA (typical)
- LED rating: 30mA max continuous
- Visibility: **Very dim**
- Operating at only **2.25% of rated current**

### 🟢 GOOD: Keyboard RGB LEDs

**LEDs:**
- 48× SK6805-EC15 addressable RGB LEDs

**Status:**
- Internal constant current drivers
- No traditional current limiting resistors needed
- Properly designed with PWM control capability

## LED Specifications

### ROHM SMLEN3WBC8W1 (White LEDs on Motherboard)
- **Forward Voltage (Vf):** 2.5V (min), 2.9V (typ), 3.3V (max) at 5mA
- **Forward Current (If):** 10mA (max continuous), 50mA (peak)
- **Luminous Intensity:** 56-220 mcd at 5mA
- **Package:** 0603

### Kingbright APT1608SURCK (Red LEDs on WiFi)
- **Forward Voltage (Vf):** 1.95V (typ), 2.5V (max) at 20mA
- **Forward Current (If):** 30mA (max continuous), 185mA (peak)
- **Luminous Intensity:** 40-80 mcd at 20mA
- **Package:** 0603

## Resistor Value Calculations

### Motherboard White LEDs (Target: 5mA for good visibility)

**Formula:** R = (V_supply - Vf) / I_target

**Calculation:**
- V_supply = 3.3V
- Vf = 2.9V (typical)
- I_target = 5mA
- R = (3.3V - 2.9V) / 0.005A = 80Ω

**Standard Value:** 82Ω (E24 series)

**Verification:**
- I_actual = (3.3V - 2.9V) / 82Ω = 4.9mA
- Power = I² × R = (0.0049)² × 82 = 1.97mW
- Safe for 0603 resistor (100mW rating)

### WiFi Red LEDs (Target: 5mA for good visibility)

**Calculation:**
- V_supply = 3.3V
- Vf = 1.95V (typical)
- I_target = 5mA
- R = (3.3V - 1.95V) / 0.005A = 270Ω

**Standard Value:** 270Ω (E24 series)

**Verification:**
- I_actual = (3.3V - 1.95V) / 270Ω = 5mA
- Power = I² × R = (0.005)² × 270 = 6.75mW
- Safe for 0603 resistor (100mW rating)

## Required Resistor Changes

### planbook-motherboard

| Reference | Current Value | Recommended Value | Target Current | Location |
|-----------|---------------|-------------------|----------------|----------|
| R1 | 1kΩ | **82Ω** | 4.9mA | Line 1620 |
| R110 | 1kΩ | **82Ω** | 4.9mA | Line 983 |
| (R for D8) | 1kΩ | **82Ω** | 4.9mA | PCB location 201.05,68.4 |
| (R for D9) | 1kΩ | **82Ω** | 4.9mA | PCB location 201.05,70.15 |

**Implementation Steps:**
1. Identify the resistor reference for D8 and D9 in schematic
2. Change all four resistors from 1kΩ to 82Ω
3. Update schematic and PCB files
4. Verify LED brightness with prototype

### planbook-wifi (nref-wifi-m2)

| Reference | Current Value | Recommended Value | Target Current | Location |
|-----------|---------------|-------------------|----------------|----------|
| R3 | 2kΩ | **270Ω** | 5mA | Line 7620 |
| R4 | 2kΩ | **270Ω** | 5mA | Line 9599 |

**Implementation Steps:**
1. Change R3 and R4 from 2kΩ to 270Ω
2. Update schematic and PCB files
3. Verify LED brightness with prototype

## Recommended Resistor Part Numbers

### 82Ω 0603 Resistors
- **Yageo:** RC0603FR-0782RL
- **Samsung:** RC0603FR-0782RL
- **Panasonic:** ERJ-3GEYJ820V
- **LCSC:** C1548 (check availability)

### 270Ω 0603 Resistors
- **Yageo:** RC0603FR-07270RL
- **Samsung:** RC0603FR-07270RL
- **Panasonic:** ERJ-3GEYJ271V
- **LCSC:** C23169 (check availability)

## Power Consumption Analysis

### Current State (Before Optimization)
- Motherboard LEDs: 4 × 0.4mA = 1.6mA
- WiFi LEDs: 2 × 0.675mA = 1.35mA
- **Total LED current:** 2.95mA
- **Total LED power:** ~10mW at 3.3V

### After Optimization (Recommended Values)
- Motherboard LEDs: 4 × 4.9mA = 19.6mA
- WiFi LEDs: 2 × 5mA = 10mA
- **Total LED current:** 29.6mA
- **Total LED power:** ~97mW at 3.3V

### Power Increase: ~87mW

This is a reasonable increase for significantly improved visibility. For a device that likely draws 500mA-1A during normal operation, an additional 87mW is negligible (<10% increase).

## Power Saving Opportunities

### 1. PWM Control (Recommended)
Implement hardware or software PWM control for all status LEDs:
- **Normal operation:** 25% brightness (reduces power by 75%)
- **Notification events:** 100% brightness (full visibility)
- **Boot/bootloader:** 100% brightness (diagnostic visibility)
- **Idle timeout:** Turn off after X minutes

**Estimated savings:** ~72mW during normal operation

### 2. Auto-Dimming (Optional)
Add ambient light sensor (if not already present):
- Bright environment: 50% brightness
- Dark environment: 25% brightness
- **Estimated savings:** ~24mW average

### 3. LED Enable/Disable Control
Add GPIO control to completely disable LEDs when not needed:
- User can disable all LEDs via software
- **Estimated savings:** Up to 97mW when disabled

## Implementation Steps in KiCad

### For Motherboard LEDs:

1. **Open Schematic**
   - Open planbook-motherboard.kicad_sch
   - Find R1, R110, and resistors for D8, D9

2. **Change Resistor Values**
   - Change value from "1k" to "82"
   - Update part number if needed
   - Add comment about LED optimization

3. **Update PCB**
   - Use "Update PCB from Schematic" tool
   - Verify footprint matches 0603 package
   - Check DRC passes

4. **Test**
   - Measure LED current with multimeter
   - Verify brightness is adequate
   - Check power consumption

### For WiFi LEDs:

1. **Open Schematic**
   - Open planbook-wifi/nref-wifi-m2.kicad_sch
   - Find R3 and R4

2. **Change Resistor Values**
   - Change value from "2k" to "270"
   - Update part number if needed
   - Add comment about LED optimization

3. **Update PCB**
   - Use "Update PCB from Schematic" tool
   - Verify footprint matches 0603 package
   - Check DRC passes

4. **Test**
   - Measure LED current with multimeter
   - Verify brightness is adequate
   - Check power consumption

## Verification Steps

After implementation:

1. **Electrical Testing**
   - Measure LED current with multimeter
   - Verify current matches calculated values (±10% tolerance)
   - Check power consumption

2. **Visual Testing**
   - Verify LEDs are clearly visible
   - Check brightness is appropriate (not too bright)
   - Test in various lighting conditions

3. **Thermal Testing**
   - Verify resistors don't overheat
   - Check LED temperatures
   - Ensure no thermal issues

4. **Software Testing** (if PWM implemented)
   - Test PWM control functionality
   - Verify brightness levels work correctly
   - Test auto-dimming if implemented

## Alternative Brightness Levels

If 5mA is too bright or too dim, here are alternative resistor values:

### Motherboard White LEDs

| Target Current | Resistor Value | Standard Value | Brightness |
|----------------|----------------|----------------|------------|
| 2mA (dim) | 200Ω | 200Ω | Low |
| 3mA (medium) | 133Ω | 130Ω | Medium |
| 5mA (recommended) | 80Ω | 82Ω | Good |
| 7mA (bright) | 57Ω | 56Ω | Bright |
| 10mA (max) | 40Ω | 39Ω | Very bright |

### WiFi Red LEDs

| Target Current | Resistor Value | Standard Value | Brightness |
|----------------|----------------|----------------|------------|
| 2mA (dim) | 675Ω | 680Ω | Low |
| 5mA (recommended) | 270Ω | 270Ω | Good |
| 10mA (bright) | 135Ω | 130Ω | Bright |
| 20mA (max) | 67.5Ω | 68Ω | Very bright |

## Notes

- **Resistor tolerance:** 1% or 5% tolerance is acceptable
- **LED forward voltage variance:** Can cause current variation of ±20%
- **Power dissipation:** All recommended values are well within 0603 resistor ratings
- **LED lifetime:** Operating at 5mA (50% of max) provides good balance of brightness and longevity
- **User preference:** Brightness is subjective - adjust based on user feedback
- **Keyboard RGB LEDs:** No changes needed - already properly designed

## References

- ROHM SMLEN3WBC8W1 Datasheet
- Kingbright APT1608SURCK Datasheet
- LED Current Limiting Resistor Calculator Guidelines
- KiCad Schematic Editor Documentation