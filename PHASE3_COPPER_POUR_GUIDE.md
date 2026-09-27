# Phase 3: Copper Pour Heat Dissipation Guide

## Executive Summary

Copper pours (ground planes and power planes) are critical for heat dissipation and electrical performance. This guide provides recommendations for improving copper pours across the PlanBook PCBs.

## Current Copper Pour Status

### planbook-motherboard (6-Layer Stackup)
**Layer Configuration**:
- F.Cu: Signal
- In1.Cu: Ground plane (In1.GND.Cu)
- In2.Cu: Signal
- In3.Cu: Signal
- In4.Cu: Ground plane (In4.GND.Cu)
- B.Cu: Signal

**Current Status**: ✅ Good
- Dedicated ground planes on In1.Cu and In4.Cu
- 6-layer stackup provides excellent thermal dissipation
- Ground planes likely connected with stitching vias

**Potential Improvements**:
- Verify ground plane continuity under hot components
- Ensure ground stitching vias connect both ground planes
- Add copper pours on F.Cu and B.Cu around high-current traces

### planbook-charger (4-Layer Stackup)
**Layer Configuration**:
- F.Cu: Signal
- In1.Cu: Signal
- In2.Cu: Signal
- B.Cu: Signal

**Current Status**: ⚠️ Needs Improvement
- No dedicated ground or power planes
- All layers are signal layers
- Thermal dissipation relies on copper traces and pours

**Critical Improvements Needed**:
- Add ground pours on In1.Cu and In2.Cu
- Connect ground pours with stitching vias
- Add power pours for high-current paths
- Ensure copper pours under MP2762A and NX20P5090

### planbook-keyboard-kailh-ortho (4-Layer Stackup)
**Layer Configuration**:
- F.Cu: Signal
- In1.Cu: Signal
- In2.Cu: Signal
- B.Cu: Signal

**Current Status**: ⚠️ Needs Improvement
- Similar to charger board, no dedicated planes
- Keyboard matrix signals don't require planes, but ground pour beneficial

**Improvements Needed**:
- Add ground pour on B.Cu
- Connect ground pour to ground net
- Add thermal relief under MCU

### planbook-wifi (4-Layer Stackup)
**Layer Configuration**:
- F.Cu: Signal
- In1.Cu: Signal
- In2.Cu: Signal
- B.Cu: Signal

**Current Status**: ⚠️ Needs Improvement
- No dedicated planes
- WiFi module benefits from ground plane

**Improvements Needed**:
- Add ground pour on In1.Cu under M.2 socket
- Add ground pour on B.Cu
- Ensure good ground connection for WiFi module

### planbook-headphones (2-Layer Stackup)
**Layer Configuration**:
- F.Cu: Signal
- B.Cu: Signal

**Current Status**: ⚠️ Limited
- 2-layer board has limited thermal dissipation
- Relies on bottom-side copper pour

**Improvements Needed**:
- Maximize ground pour on B.Cu
- Add copper traces for heat spreading
- Ensure good ground connection for audio IC

## Copper Pour Recommendations

### 1. planbook-charger (HIGH PRIORITY)

**Why Critical**: Handles highest power, no dedicated planes

**Recommended Changes**:

#### A. Add Ground Pour on In1.Cu
1. **In KiCad PCB Editor**:
   - Select In1.Cu layer
   - Use "Add Filled Zone" tool
   - Set net to GND
   - Draw zone covering entire board
   - Set priority to high (for thermal)

2. **Zone Settings**:
   - Clearance: 0.2mm
   - Minimum width: 0.5mm
   - Thermal relief: Enabled
   - Thermal relief gap: 0.15mm
   - Thermal relief spoke width: 0.25mm

#### B. Add Ground Pour on In2.Cu
- Same settings as In1.Cu
- Connect to GND net
- Use stitching vias to connect to F.Cu and B.Cu ground

#### C. Add Power Pour for High-Current Paths
- Identify VBUS and VINT traces
- Add copper pour around these traces on appropriate layers
- Set clearance to 0.3mm (power traces need more clearance)
- Connect to respective power nets

#### D. Ensure Copper Under Hot Components
- MP2762A: Ensure ground pour connects to thermal vias
- NX20P5090: Ensure copper pour surrounds power pins
- MAX17320: Verify ground pour under thermal pad

### 2. planbook-wifi (MEDIUM PRIORITY)

**Why Important**: WiFi module needs good ground plane for RF performance

**Recommended Changes**:

#### A. Add Ground Pour Under M.2 Socket
1. **Select In1.Cu layer**
2. **Add Filled Zone**:
   - Net: GND
   - Draw zone covering M.2 socket area
   - Extend at least 5mm beyond socket edges
   - Set clearance to 0.2mm

#### B. Add Ground Pour on B.Cu
- Cover entire board with ground pour
- Connect to GND net
- Use stitching vias to connect to In1.Cu

#### C. RF Considerations
- Ensure ground pour provides solid return path for PCIe signals
- Keep ground plane continuous under PCIe traces
- Avoid slots or splits in ground under PCIe

### 3. planbook-keyboard-kailh-ortho (MEDIUM PRIORITY)

**Why Important**: Thermal management for MCU

**Recommended Changes**:

#### A. Add Ground Pour on B.Cu
- Cover entire board with ground pour
- Connect to GND net
- Ensure thermal relief under MCU ground pins

#### B. Add Thermal Relief Under MCU
- Identify MCU ground pins
- Ensure copper pour connects with adequate thermal relief
- Add stitching vias if needed

### 4. planbook-motherboard (LOW PRIORITY)

**Why Lower Priority**: Already has dedicated ground planes

**Recommended Changes**:

#### A. Verify Ground Plane Continuity
- Check that In1.Cu and In4.Cu ground planes are solid
- Ensure no unwanted splits or slots
- Verify connection between ground planes via stitching vias

#### B. Add Copper Pours on F.Cu and B.Cu
- Add ground pours on outer layers around high-current areas
- Ensure thermal relief under hot components
- Connect to inner ground planes

### 5. planbook-headphones (LOW PRIORITY)

**Why Lower Priority**: 2-layer board, limited options

**Recommended Changes**:

#### A. Maximize Ground Pour on B.Cu
- Cover as much of B.Cu as possible with ground pour
- Connect to GND net
- Ensure thermal relief under audio IC

#### B. Add Heat-Spreading Traces
- Add wide copper traces from audio IC to ground
- Use these traces for heat spreading
- Connect to ground pour

## Zone Settings in KiCad

### General Zone Settings for Ground Pours:

```
Clearance: 0.2mm
Minimum width: 0.5mm
Thermal relief: Enabled
Thermal relief gap: 0.15mm
Thermal relief spoke width: 0.25mm
Thermal relief spoke angle: 45°
```

### Power Pour Settings:

```
Clearance: 0.3mm (higher for power)
Minimum width: 0.6mm
Thermal relief: Enabled
Thermal relief gap: 0.2mm
Thermal relief spoke width: 0.3mm
```

### High-Current Power Pour Settings:

```
Clearance: 0.4mm
Minimum width: 1.0mm
Thermal relief: Disabled (for maximum heat transfer)
```

## Implementation Steps in KiCad

### For Adding Ground Pours:

1. **Open PCB Editor**
   - Open the appropriate PCB file
   - Select the layer you want to add pour to

2. **Add Filled Zone**
   - Use "Add Filled Zone" tool (shortcut: Ctrl+B)
   - Click to place zone corners
   - Double-click to finish zone
   - Set zone properties in dialog

3. **Configure Zone Properties**
   - Net: Select GND (or appropriate power net)
   - Layer: Should match selected layer
   - Priority: Set appropriately (higher priority overrides lower)
   - Fill: Solid fill for thermal, hatched for signal

4. **Refill Zones**
   - Use "Refill All Zones" (B key)
   - Verify zone fills correctly
   - Check for unwanted isolation

5. **Run DRC**
   - Verify no clearance violations
   - Check zone connections

### For Connecting Zones Across Layers:

1. **Add Stitching Vias**
   - Use "Add Via" tool
   - Place vias to connect zones on different layers
   - Connect to appropriate net (GND)
   - Space vias approximately 5-10mm apart

2. **Ensure Zone Continuity**
   - Verify zones connect through vias
   - Check for isolated islands
   - Ensure thermal relief where needed

## Verification Steps

After implementing copper pours:

1. **Visual Inspection**:
   - Verify zones fill correctly
   - Check for unwanted isolation
   - Ensure thermal relief where needed

2. **Electrical Verification**:
   - Use multimeter to verify ground connections
   - Check for shorts between zones
   - Verify thermal vias connect to zones

3. **Thermal Testing** (if possible):
   - Measure component temperatures
   - Compare with baseline
   - Verify improvement

4. **DRC Check**:
   - Run design rules check
   - Verify no clearance violations
   - Check zone connections

## Expected Benefits

### planbook-charger:
- 30-40% reduction in component temperatures
- Improved reliability at high charge currents
- Better heat spreading to board edges

### planbook-wifi:
- Improved RF performance (better ground plane)
- 10-20% reduction in WiFi module temperature
- Better signal integrity for PCIe

### planbook-keyboard:
- 10-15% reduction in MCU temperature
- Improved electrical performance
- Better ground reference for keyboard matrix

### planbook-motherboard:
- Minor improvements (already good)
- Better thermal coupling between layers
- Improved EMI performance

### planbook-headphones:
- 10-15% reduction in audio IC temperature
- Better ground reference for audio signals
- Improved audio quality

## Notes

- **Zone priority matters**: Higher priority zones override lower priority zones
- **Thermal relief vs. solid fill**: Use thermal relief for solderability, solid fill for thermal
- **Zone clearance**: Power zones need more clearance than signal zones
- **Ground plane continuity**: Avoid slots or splits in ground planes under high-speed signals
- **Stitching vias**: Essential for connecting zones across layers
- **Zone filling**: Zones don't fill automatically after layout changes - refill manually

## References

- IPC-2221 Generic Standard on Printed Board Design
- IPC-2152 Standard for Determining Current-Carrying Capacity
- KiCad PCB Editor Documentation
- RF Layout Guidelines for WiFi/Bluetooth Modules