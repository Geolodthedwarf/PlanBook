# Phase 3: Thermal Management Implementation Guide

## Executive Summary

The PlanBook project has mixed thermal management. Some components (RP2040, MAX17320, TUSB8041) already have adequate thermal vias, but critical power components on the charger board are missing thermal management entirely.

## Current Thermal Management Status

### ✅ Already Adequate (No Changes Needed)

**1. RP2040 (planbook-motherboard)**
- Location: U8 at (74.25, 80)
- Package: QFN-56 with 3.2mm × 3.2mm thermal pad
- Current: 9 thermal vias (0.35mm drill, 0.6mm pad) in 3×3 grid
- Status: ✅ Meets industry standards

**2. MAX17320 Battery Fuel Gauge (planbook-charger)**
- Location: U2 at (98.5, 104.75)
- Package: QFN-24-1EP 4×4mm with 2.65×2.65mm thermal pad
- Current: 9 thermal vias (0.3mm drill, 0.6mm pad) in 3×3 grid
- Status: ✅ Adequate for low-power device

**3. TUSB8041 USB Hub (planbook-motherboard)**
- Location: U25 at (173.5, 121.3)
- Package: QFN-64-1EP 9×9mm with 6×6mm thermal pad
- Current: 16 thermal vias (0.3mm drill, 0.6mm pad) in 4×4 grid
- Status: ✅ Adequate for USB hub

### ❌ Critical Issues (Immediate Action Required)

**1. MP2762A Battery Charger (planbook-charger)**
- Location: at (105.7, 89.25)
- Package: QFN-30 (4×5mm)
- Power: 6A charge current, 4-21V input, buck/boost operation
- Thermal limit: 120°C die temperature
- Current: ❌ NO thermal vias - only exposed pad on F.Cu and B.Cu
- Heat generation: 🔴 HIGH - handles up to 6A with integrated MOSFETs
- Priority: 🔴 CRITICAL

**2. NX20P5090 USB PD Power Switch (planbook-charger)**
- Location: at (103.2, 78.7) - 90° rotation
- Package: WLP-15 (3.2×3.2mm ball grid array)
- Power: 5A max current, 2.5-20V operation
- Thermal: Rθ(j-a) = 67.2 K/W, max junction temp 125°C
- Current: ❌ NO thermal vias - no exposed pad or thermal relief
- Heat generation: 🔴 HIGH - 5A power switch with up to 1.45W dissipation
- Priority: 🔴 CRITICAL

### 🟡 Moderate Issues (Recommended Improvements)

**3. LDO Regulators (planbook-motherboard)**
- AP22615AWU-7: 1.5A LDO (SOT-23-6)
- TLV75718PDBV: 1A LDO (SOT-23)
- TPS7A0533PDBZ: 200mA LDO (SOT-23)
- LMR16006YQ3: 600mA buck regulator (SOT-23-6)
- Status: ❌ SOT-23 packages rely on PCB copper pour
- Priority: 🟡 MODERATE

## Critical Thermal Via Implementation

### 1. MP2762A Charger IC (CRITICAL)

**Current Footprint**: `planbook-charger:MP2762A` - custom footprint with no thermal vias

**Required Changes**:

#### Step 1: Modify Footprint
In KiCad Footprint Editor:
1. Open the MP2762A footprint
2. Navigate to the thermal pad (exposed pad on the bottom)
3. Add thermal vias in a 4×4 grid pattern

#### Via Specifications:
- **Drill size**: 0.3mm
- **Pad size**: 0.6mm
- **Pattern**: 4×4 grid (16 vias total)
- **Spacing**: 1mm center-to-center
- **Layers**: Connect to all copper layers (F.Cu, In1.Cu, In2.Cu, B.Cu)
- **Tenting**: Tent vias on bottom side to prevent solder wicking

#### Via Grid Pattern (relative to thermal pad center):
```
Coordinates (mm from center):
  (-0.75, -0.75)  (-0.75, 0)    (-0.75, 0.75)  (-0.75, 1.5)
  (0, -0.75)      (0, 0)        (0, 0.75)      (0, 1.5)
  (0.75, -0.75)   (0.75, 0)     (0.75, 0.75)   (0.75, 1.5)
  (1.5, -0.75)    (1.5, 0)      (1.5, 0.75)    (1.5, 1.5)
```

#### Step 2: Update PCB
1. Update the footprint in the PCB editor
2. Ensure the thermal pad connects to ground plane
3. Verify DRC passes

#### Expected Benefits:
- Reduced junction temperature by 20-30°C
- Improved reliability at high charge currents
- Better heat spreading to board edges

### 2. NX20P5090 Power Switch (CRITICAL)

**Current Footprint**: `planbook-charger:NXP_NX20P5090` - WLP package with no thermal features

**Challenge**: WLP packages have no exposed thermal pad, so thermal management must be through pin connections.

#### Required Changes:

#### Step 1: Add Thermal Vias Near Power Pins
In KiCad PCB Editor:
1. Zoom to NX20P5090 location at (103.2, 78.7)
2. Add thermal vias near VINT and VBUS pins
3. Connect these vias to internal ground/power planes

#### Via Specifications:
- **Drill size**: 0.3mm
- **Pad size**: 0.6mm
- **Quantity**: 4-6 vias
- **Placement**: Within 1mm of power pins
- **Layers**: Connect to all copper layers

#### Via Placement (relative to component center):
```
  (-1.0, -0.5)  - Near VINT pin
  (1.0, -0.5)   - Near VBUS pin
  (-1.0, 0.5)   - Additional heat spreading
  (1.0, 0.5)    - Additional heat spreading
```

#### Step 2: Expand Copper Pour
1. Increase copper area around VINT and VBUS pins
2. Ensure wide traces (minimum 0.6mm for 5A current)
3. Connect to ground planes for heat spreading

#### NXP Datasheet Recommendation:
> "To minimize effective Rθ(j-a), all pins must have solid connection to larger Cu layer areas. In multi-layer PCB applications, the second layer should be used to create a large heat spreader area right below the device."

#### Expected Benefits:
- Reduced thermal resistance from 67.2 K/W to ~50 K/W
- Improved reliability at 5A current
- Better heat dissipation through ground planes

## Moderate Thermal Improvements

### 3. LDO Regulators (MODERATE)

#### For AP22615AWU-7 (1.5A LDO):
- Package: SOT-23-6
- Recommendations:
  1. Ensure wide copper traces on input/output pins (minimum 0.5mm)
  2. Add polygon pour connected to GND pin
  3. Add 2-3 thermal vias near GND pin

#### For TLV75718PDBV (1A LDO):
- Package: SOT-23
- Recommendations:
  1. Ensure copper traces are adequate for 1A current
  2. Add ground pour around component
  3. No thermal vias needed (lower power)

#### For TPS7A0533PDBZ (200mA LDO):
- Package: SOT-23
- Recommendations:
  1. Standard copper traces sufficient
  2. No additional thermal management needed

#### For LMR16006YQ3 (600mA Buck Regulator):
- Package: SOT-23-6
- Recommendations:
  1. Add 3-4 thermal vias near GND pin (pin 2)
  2. Ensure large copper area on VIN and VOUT pins
  3. Connect to internal ground planes

## Standard Thermal Via Pattern Reference

### For QFN Packages with Thermal Pads:

**Small Pad (<3mm)**:
- Pattern: 3×3 grid (9 vias)
- Spacing: 0.8mm center-to-center
- Example: RP2040 (already done)

**Medium Pad (3-5mm)**:
- Pattern: 4×4 grid (16 vias)
- Spacing: 1.0mm center-to-center
- Example: MP2762A (needs implementation)

**Large Pad (>5mm)**:
- Pattern: 5×5 grid (25 vias)
- Spacing: 1.27mm center-to-center
- Example: TUSB8041 (already done with 4×4)

### Via Specifications:
- **Drill size**: 0.3mm (min) to 0.35mm (max)
- **Pad size**: 0.6mm
- **Placement**: Centered under thermal pad
- **Clearance**: Minimum 0.5mm from pad edge
- **Layer connection**: All copper layers (especially ground planes)
- **Tenting**: Consider tenting vias on bottom side

## Implementation Steps in KiCad

### For Footprint Modifications (MP2762A):

1. **Open Footprint Editor**
   - File → Open Footprint Editor
   - Load `planbook-charger:MP2762A`

2. **Add Thermal Vias**
   - Select the thermal pad
   - Use "Add Pad" tool to create vias
   - Set pad type to "Through-hole"
   - Set drill size to 0.3mm
   - Set pad size to 0.6mm
   - Place in 4×4 grid pattern
   - Connect to appropriate net (usually GND)

3. **Save Footprint**
   - Save the modified footprint
   - Update PCB to use new footprint

4. **Update PCB**
   - Open planbook-charger.kicad_pcb
   - Use "Update Footprint" tool
   - Verify DRC passes

### For PCB-Level Modifications (NX20P5090, LDOs):

1. **Open PCB Editor**
   - Open the appropriate PCB file
   - Zoom to component location

2. **Add Thermal Vias**
   - Use "Add Via" tool
   - Set drill size to 0.3mm
   - Set pad size to 0.6mm
   - Place at recommended coordinates
   - Connect to ground plane

3. **Run DRC**
   - Verify no clearance violations
   - Check via connections

4. **Save**
   - Save the PCB file

## Verification Steps

After implementation:

1. **Visual Inspection**:
   - Verify thermal vias are correctly placed
   - Check via connections to ground planes
   - Ensure no short circuits

2. **Thermal Testing** (if possible):
   - Measure component temperature under load
   - Compare with datasheet limits
   - Verify temperature reduction vs. baseline

3. **DRC Check**:
   - Run design rules check
   - Verify no violations
   - Check thermal pad connections

## Expected Thermal Improvements

| Component | Current Rθ(j-a) | Expected Rθ(j-a) | Temp Reduction at Max Power |
|-----------|----------------|------------------|----------------------------|
| MP2762A | ~80 K/W | ~50 K/W | 20-30°C reduction |
| NX20P5090 | 67.2 K/W | ~50 K/W | 10-15°C reduction |
| LDOs | Varies | ~10% improvement | 5-10°C reduction |

## Notes

- The charger board (planbook-charger) has the most critical thermal needs
- The 6-layer motherboard stackup provides excellent thermal dissipation
- All thermal vias should be connected to ground planes for maximum heat spreading
- For reflow soldering, consider tenting vias on the bottom side
- Thermal vias should not be placed too close to pad edges (minimum 0.5mm clearance)
- Solder mask should not cover thermal vias that need to connect to ground planes

## References

- MP2762A datasheet (MPS)
- NX20P5090 datasheet (NXP)
- IPC-7092 Design and Assembly Process Implementation for BGAs
- IPC-2221 Generic Standard on Printed Board Design