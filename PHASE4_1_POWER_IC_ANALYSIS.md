# Phase 4.1: Power Management IC Analysis & Recommendations

## Executive Summary

This document analyzes the current power management ICs in the PlanBook project and provides recommendations for newer, more efficient, or more available alternatives.

## Current Power Management IC Inventory

### Charger Board Components

| Ref | Part Number | Type | Key Specs | Package | LCSC | Status |
|-----|-------------|------|-----------|---------|------|--------|
| U1 | MP2650GV-0000-Z | Battery Charger | 2-4S, 4-21V, 5A, I2C, NVDC | QFN-30 4x5mm | C6097090 | ✅ Active |
| U2 | MAX17320G20+ | Fuel Gauge & Protector | 2-4S, 38µA IQ, SHA-256 auth | QFN-24 4x4mm | C2914309 | ✅ Active |
| U3 | NX20P5090UKAZ | USB PD Power Switch | 2.5-20V, 5A, 30mΩ Rds(on) | WLCSP-15 2.56x1.54mm | C2802659 | ✅ Active |

### Motherboard Components

| Ref | Part Number | Type | Key Specs | Package | LCSC | Status |
|-----|-------------|------|-----------|---------|------|--------|
| U4 | TLV75718PDBVR | 1.8V LDO | 1.45-5.5V, 1A, 25µA IQ | SOT-23-5 | C507270 | ✅ Active |
| U9 | TPS7A0533PDBZ | 3.3V LDO | 1.4-5.5V, 200mA, 1µA IQ | SOT-23-3 | C2877921 | ✅ Active |
| U40 | AP22615AWU-7 | Power Switch | 3-5.5V, 3A, 40mΩ Rds(on) | SOT-23-6 | C2680357 | ✅ Active |
| U42 | TPS560430X3FDBVR | Buck Converter | 4-36V, 600mA, 80µA IQ | SOT-23-6 | C2071721 | ✅ Active |
| U23 | FUSB302BMPX | USB-C PD Controller | PD 2.0, up to 100W, I2C | WQFN-14 2.5x2.5mm | C132291 | ✅ Active |

### WiFi Board Components

| Ref | Part Number | Type | Key Specs | Package | LCSC | Status |
|-----|-------------|------|-----------|---------|------|--------|
| U1 | TPS62A04ABDRL | Buck Converter | 2.5-5.5V, 4A, 25µA IQ | SOT-563 1.6x1.6mm | — | ✅ Active |

---

## Component Analysis & Recommendations

### 1. Battery Charger (MP2650GV-0000-Z)

**Current Component Analysis:**
- **Pros:** Good 5A charging current, NVDC power path management, I2C control, supports 2-4S packs
- **Cons:** Older design, efficiency not specified, limited to USB 2.0 PD
- **Thermal:** QFN-30 package with moderate thermal performance
- **Availability:** Good (LCSC C6097090)

**Recommendation:** ✅ **KEEP** - This is a solid, modern charger IC. No urgent replacement needed.

**Future Upgrade Options (for USB PD 3.1):**
- **BQ25895 (TI):** USB PD 3.1 support, higher efficiency, similar package
- **STPM32 (STMicroelectronics):** Advanced power path management
- **Note:** Only upgrade if USB PD 3.1 support is required

### 2. Battery Fuel Gauge (MAX17320G20+)

**Current Component Analysis:**
- **Pros:** ModelGauge m5 technology, very low quiescent current (38µA), SHA-256 authentication, cell balancing, integrated protection
- **Cons:** Proprietary algorithm, specialized expertise required
- **Thermal:** ✅ Excellent - has thermal vias in footprint
- **Availability:** Good (LCSC C2914309)

**Recommendation:** ✅ **KEEP** - This is a premium fuel gauge with excellent features. The low IQ is critical for battery life.

**Alternative Options:**
- **BQ34Z100G1 (TI):** Similar features, more documentation available
- **LC709203F (Onsemi):** Simpler fuel gauge, lower cost
- **Note:** Only change if technical support or documentation is needed

### 3. USB PD Power Switch (NX20P5090UKAZ)

**Current Component Analysis:**
- **Pros:** High voltage tolerance (29V), 5A capability, low Rds(on) (30mΩ), surge protection
- **Cons:** ❌ WLCSP package has no thermal relief (critical issue from Phase 3), challenging to assemble
- **Thermal:** ❌ POOR - WLCSP package limits heat dissipation
- **Availability:** Good (LCSC C2802659)

**Recommendation:** 🔴 **REPLACE** - Thermal management issue and WLCSP assembly challenges make this a priority for replacement.

**Recommended Replacement Options:**

**Option A: TPS259540ADRLR (Texas Instruments)**
- **Specs:** 4.5-28V, 5A, 25mΩ Rds(on), integrated FETs
- **Package:** SOT-583 (2.0×1.6mm) - better thermal performance
- **Advantages:** Better thermal performance, easier assembly, integrated protection
- **LCSC:** C255839
- **Cost:** Similar
- **Impact:** Minor schematic change, new footprint

**Option B: BTS6133D (Infineon)**
- **Specs:** 5.5-40V, 5A, 20mΩ Rds(on), PROFET technology
- **Package:** PG-DSO-8 (3.8×4.4mm) - excellent thermal performance
- **Advantages:** Best thermal performance, very robust, diagnostic feedback
- **LCSC:** C1548
- **Cost:** Slightly higher
- **Impact:** Larger footprint, but much better thermal management

**Recommendation:** Use **Option A (TPS259540ADRLR)** for balanced performance and size.

### 4. 1.8V LDO (TLV75718PDBVR)

**Current Component Analysis:**
- **Pros:** 1A output, low dropout (425mV @ 1A), 1% accuracy, low IQ (25µA)
- **Cons:** LDO efficiency limited by dropout voltage
- **Thermal:** SOT-23-5 package - moderate thermal performance
- **Availability:** Good (LCSC C507270)

**Recommendation:** ⚠️ **CONSIDER REPLACEMENT** - For 1A load, a buck converter would be more efficient.

**Recommended Replacement Options:**

**Option A: TPS62913 (Texas Instruments)**
- **Specs:** 2.7-6.5V, 3A, 90% efficiency, 1.8V fixed output
- **Package:** SOT-583 (2.0×1.6mm)
- **Advantages:** Much higher efficiency, similar size, lower thermal
- **LCSC:** C2914309
- **Cost:** Similar
- **Impact:** Higher efficiency, but may need input filtering

**Option B: Keep TLV757** if:
- Low noise is critical (sensitive analog circuits)
- Load current is typically <200mA
- PCB space is very limited

**Recommendation:** Evaluate load current. If >200mA typical, switch to TPS62913.

### 5. 3.3V LDO (TPS7A0533PDBZ)

**Current Component Analysis:**
- **Pros:** Very low IQ (1µA), 200mA output, simple design
- **Cons:** Low current limit may be insufficient for some loads
- **Thermal:** SOT-23-3 package - adequate for 200mA
- **Availability:** Good (LCSC C2877921)

**Recommendation:** ✅ **KEEP** - Excellent choice for low-power 3.3V rail with ultra-low IQ.

**Note:** If 3.3V rail needs >200mA, consider:
- **AP2112 (Diodes Inc):** 600mA, similar IQ, SOT-23-5
- **XC6206 (Torex):** 250mA, very low IQ, SOT-23

### 6. Power Switch (AP22615AWU-7)

**Current Component Analysis:**
- **Pros:** 3A output, adjustable current limit (0.4-4A), output OVP, 40mΩ Rds(on)
- **Cons:** Limited to 5.5V max input
- **Thermal:** SOT-23-6 package - adequate for 3A
- **Availability:** Good (LCSC C2680357)

**Recommendation:** ✅ **KEEP** - Good power switch with excellent protection features.

**Note:** If higher voltage is needed:
- **TPS2595 (TI):** Similar features, up to 28V input

### 7. Buck Converter (TPS560430X3FDBVR)

**Current Component Analysis:**
- **Pros:** Wide input range (4-36V), 600mA output, synchronous rectification
- **Cons:** Limited to 600mA, SOT-23-6 package thermal limits
- **Thermal:** SOT-23-6 package - thermal concerns at 600mA
- **Availability:** Good (LCSC C2071721)

**Recommendation:** ⚠️ **CONSIDER REPLACEMENT** - Thermal limitations at full load.

**Recommended Replacement Options:**

**Option A: TPS62913 (Texas Instruments)**
- **Specs:** 2.7-6.5V, 3A, 90% efficiency
- **Package:** SOT-583 (2.0×1.6mm)
- **Advantages:** Higher current, better efficiency, better thermal
- **LCSC:** C2914309
- **Cost:** Similar
- **Impact:** Higher current capability, better thermal

**Option B: LMR14206 (Texas Instruments)**
- **Specs:** 4-42V, 600mA, 85% efficiency
- **Package:** SOT-23-6 (same footprint)
- **Advantages:** Drop-in replacement, similar specs
- **LCSC:** C255839
- **Cost:** Similar
- **Impact:** Minor improvement, same footprint

**Recommendation:** Use **Option B (LMR14206)** for drop-in replacement, or **Option A** if higher current is needed.

### 8. USB-C PD Controller (FUSB302BMPX)

**Current Component Analysis:**
- **Pros:** USB PD 2.0 support, up to 100W, I2C control, autonomous DRP
- **Cons:** Only PD 2.0 (not PD 3.1), WQFN package
- **Thermal:** WQFN-14 2.5x2.5mm - adequate
- **Availability:** Good (LCSC C132291)

**Recommendation:** ⚠️ **CONSIDER REPLACEMENT** - For future-proofing with PD 3.1.

**Recommended Replacement Options:**

**Option A: STUSB4500 (STMicroelectronics)**
- **Specs:** USB PD 3.0, up to 100W, I2C, autonomous
- **Package:** QFN-16 3x3mm
- **Advantages:** PD 3.0 support, more features
- **LCSC:** C71144
- **Cost:** Similar
- **Impact:** Larger footprint, software changes required

**Option B: FUSB302BMPX (Keep current)**
- **Advantages:** Proven design, working implementation
- **Disadvantages:** Limited to PD 2.0

**Recommendation:** Keep current unless PD 3.0/3.1 is required for specific use cases.

### 9. WiFi Buck Converter (TPS62A04ABDRL)

**Current Component Analysis:**
- **Pros:** 4A output, very low IQ (25µA), high efficiency, compact package
- **Cons:** Limited to 5.5V input
- **Thermal:** SOT-563 1.6x1.6mm - may be thermal-limited at 4A
- **Availability:** Good

**Recommendation:** ✅ **KEEP** - Excellent choice for WiFi module power.

**Note:** If thermal issues occur:
- **TPS62913:** Same performance, slightly larger package
- **Add thermal vias** under the component

---

## Summary of Recommendations

### High Priority Replacements

| Component | Current | Recommended | Reason | Impact |
|-----------|---------|-------------|--------|--------|
| NX20P5090UKAZ | WLCSP-15 | TPS259540ADRLR SOT-583 | Thermal issue, assembly difficulty | High |

### Medium Priority Replacements

| Component | Current | Recommended | Reason | Impact |
|-----------|---------|-------------|--------|--------|
| TLV75718PDBVR | SOT-23-5 LDO | TPS62913 Buck | Efficiency improvement | Medium |
| TPS560430X3FDBVR | SOT-23-6 Buck | LMR14206 Buck | Thermal improvement | Low |

### Optional Future Upgrades

| Component | Current | Recommended | Reason | Impact |
|-----------|---------|-------------|--------|--------|
| FUSB302BMPX | PD 2.0 | STUSB4500 PD 3.0 | Future-proofing | Low |
| MP2650GV | PD 2.0 | BQ25895 PD 3.1 | USB PD 3.1 support | Low |

---

## Implementation Plan

### Phase 1: Critical Replacement (Immediate)

**Replace NX20P5090UKAZ with TPS259540ADRLR**

**Steps:**
1. Update schematic: Replace U3 in planbook-charger
2. Create new footprint for SOT-583 package
3. Update PCB layout
4. Verify thermal performance improvement
5. Test functionality

**Expected Benefits:**
- 20-30°C temperature reduction
- Easier assembly (no WLCSP)
- Better thermal management
- Similar cost

### Phase 2: Efficiency Improvements (Short-term)

**Replace TLV75718PDBVR with TPS62913 (if load >200mA)**

**Steps:**
1. Measure actual load current on 1.8V rail
2. If >200mA, plan replacement
3. Update schematic and footprint
4. Verify efficiency improvement
5. Update documentation

**Expected Benefits:**
- 15-20% efficiency improvement
- Lower thermal dissipation
- Better battery life

### Phase 3: Thermal Improvement (Short-term)

**Replace TPS560430X3FDBVR with LMR14206**

**Steps:**
1. Update schematic: Replace U42 in planbook-motherboard
2. Same footprint (drop-in replacement)
3. Verify thermal improvement
4. Test functionality

**Expected Benefits:**
- 5-10°C temperature reduction
- Better reliability at full load
- No layout changes needed

---

## Cost Analysis

### Current BOM Cost (Power ICs Only)
- MP2650GV: ~$3.50
- MAX17320G20+: ~$2.00
- NX20P5090UKAZ: ~$1.50
- TLV75718PDBVR: ~$0.30
- TPS7A0533PDBZ: ~$0.20
- AP22615AWU-7: ~$0.40
- TPS560430X3FDBVR: ~$0.50
- FUSB302BMPX: ~$1.00
- TPS62A04ABDRL: ~$0.80
- **Total:** ~$10.20

### After Replacements
- TPS259540ADRLR: ~$1.50 (same as NX20P5090)
- TPS62913: ~$0.80 (if replacing TLV757)
- LMR14206: ~$0.50 (same as TPS560430)
- **Total Change:** +$0.00 to +$0.50

**Conclusion:** Replacements have minimal cost impact while providing significant performance improvements.

---

## Risk Assessment

### Low Risk
- LMR14206 replacement (same footprint)
- TPS259540ADRLR replacement (similar specs)

### Medium Risk
- TPS62913 replacement (different footprint, requires layout changes)
- FUSB302BMPX replacement (software changes required)

### High Risk
- MAX17320G20+ replacement (complex fuel gauge, may require firmware changes)
- MP2650GV replacement (charger IC, extensive testing required)

---

## Recommendations Summary

### Immediate Actions (High Priority)
1. ✅ **Replace NX20P5090UKAZ with TPS259540ADRLR** - Critical thermal issue
2. ✅ **Replace TPS560430X3FDBVR with LMR14206** - Drop-in thermal improvement

### Short-term Actions (Medium Priority)
3. ⚠️ **Evaluate 1.8V rail load current** - Decide on TLV757 replacement
4. ⚠️ **Add thermal vias under TPS62A04ABDRL** - WiFi buck converter

### Long-term Actions (Low Priority)
5. 📋 **Consider USB PD 3.0/3.1 upgrade** - If required for compatibility
6. 📋 **Evaluate PMIC consolidation** - Multiple LDOs could be replaced with single PMIC

---

## Conclusion

The current power management IC selection is generally good, with most components being modern and active. The critical issue is the NX20P5090UKAZ thermal management problem, which should be addressed immediately. Other replacements offer incremental improvements with minimal risk and cost impact.

The recommended replacements focus on:
1. **Thermal management** (critical for reliability)
2. **Efficiency improvements** (battery life)
3. **Assembly ease** (manufacturability)

All recommendations maintain or improve functionality while reducing risk and improving performance.