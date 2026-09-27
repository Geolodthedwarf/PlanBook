# Phase 2: Decoupling Capacitor Implementation Guide

## RP2040 Decoupling Capacitor Additions

### Current Status
- **RP2040 Location:** U8 at (74.25, 80) with 90° rotation
- **Current Decoupling:** 3×0.1µF for 9 power pins (inadequate)
- **Target:** 100nF per power pin per Raspberry Pi guidelines

### Critical Additions Required

#### 1. STANDBY_3V3 Rail Decoupling (High Priority)

**Power Pins Needing Decoupling:**
- Pin 1 (IOVDD_1) - Position: ~73.0, 76.0
- Pin 10 (IOVDD_10) - Position: ~73.0, 81.0  
- Pin 22 (IOVDD_22) - Position: ~74.25, 83.5
- Pin 33 (IOVDD_33) - Position: ~75.5, 81.0
- Pin 42 (IOVDD_42) - Position: ~76.0, 77.0
- Pin 48/49 (USB_VDD/IOVDD) - Position: ~74.25, 76.0

**Add 6× 0.1µF capacitors:**
- Value: 0.1µF (100nF)
- Package: 0402
- Voltage: 6.3V
- Dielectric: X5R
- LCSC Part: C307331 (CL05B104KB54PNC) - same as existing C25, C27, C31
- Net: STANDAS_3V3

#### 2. VREG_IN (Pin 44) Critical Addition

**Add 1× 1µF capacitor:**
- Value: 1µF
- Package: 0402
- Voltage: 6.3V
- Dielectric: X5R
- LCSC Part: C52923 (CL05A105KA5NQNC) - same as existing C26
- Net: STANDBY_3V3
- Position: ~72.5, 76.5 (near Pin 44)
- **Critical for LDO stability**

#### 3. High-Frequency Decoupling (Optional but Recommended)

**Add 2× 0.01µF capacitors:**
- Value: 0.01µF (10nF)
- Package: 0201 (smallest available)
- Voltage: 6.3V
- Dielectric: X5R
- LCSC Part: C1548 or similar
- Net: STANDBY_3V3
- Positions: ~74.0, 78.0 and ~74.5, 82.0

### Implementation Steps in KiCad

1. **Open planbook-motherboard.kicad_pcb in KiCad**
2. **Zoom to the RP2040 (U8) area**
3. **Add capacitors one by one:**
   - Use "Add footprint" tool
   - Search for 0402 capacitor footprint
   - Place at recommended coordinates
   - Assign to STANDBY_3V3 net
   - Set value to 0.1µF or 1µF as specified
4. **Run Design Rule Check (DRC)** to verify no conflicts
5. **Update schematic** to add corresponding capacitor symbols
6. **Annotate capacitors as "decoupling" in schematic**

### Component Footprint Recommendations

Use existing 0402 capacitor footprints from the project:
- The project already uses C307331 (0.1µF) in multiple locations
- Use the same footprint library for consistency
- Ensure footprint matches the package size (0402 = 1.0mm × 0.5mm)

### Net Assignment

All new capacitors should be connected to:
- **STANDS_3V3** net (check exact net name in schematic)
- **Ground plane** (use via-in-pad or nearby via for GND connection)

### Expected Benefits

- **Reduced power supply noise** on RP2040
- **Improved stability** at high clock speeds
- **Better EMC performance**
- **Reduced risk of brownout** during current spikes
- **Compliance with Raspberry Pi hardware design guidelines**

### Verification Steps

After implementation:
1. Run electrical rules check (ERC) in schematic
2. Run design rules check (DRC) in PCB editor
3. Verify capacitor placements don't interfere with routing
4. Check thermal considerations (capacitors near RP2040 may affect thermal performance)
5. Consider adding thermal relief for soldering

### Additional ICs to Consider

After RP2040 decoupling, also consider:
- **MAX17320 (battery management IC)** - needs decoupling near power pins
- **MP2650 (charger IC)** - needs input/output decoupling
- **Display driver ICs** - need power rail decoupling
- **Other power management ICs** - review each for decoupling needs

### Timeline Recommendations

1. **Immediate:** Add RP2040 decoupling (critical for performance)
2. **Short-term:** Add decoupling to other power ICs
3. **Medium-term:** Review entire power distribution network
4. **Long-term:** Add thermal vias and improve ground planes