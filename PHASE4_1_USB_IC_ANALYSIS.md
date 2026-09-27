# Phase 4.1: USB Interface IC Analysis & Recommendations

## Executive Summary

This document analyzes the current USB interface ICs in the PlanBook project and provides recommendations for newer, more capable, or more efficient alternatives.

## Current USB Interface IC Inventory

### Motherboard Components

| Ref | Part Number | Type | Key Specs | Package | LCSC | Status |
|-----|-------------|------|-----------|---------|------|--------|
| U25 | TUSB8041IRGCR | USB 3.0 Hub | 4-port, 5Gbps, I2C | QFN-64 9x9mm | C544686 | ✅ Active |
| U37/U41/U42/U31 | TS3USB30EDGSR | USB 2.0 Mux | 480Mbps, 1:2, ESD | VSSOP-10 3x3mm | — | ✅ Active |
| U23 | FUSB302BMPX | USB-C PD Controller | PD 2.0, Type-C 1.3 | WQFN-14 2.5x2.5mm | C132291 | ✅ Active |
| U35 | TMUXHS4446RETR | USB-C Mux | 10Gbps, 6x4 | QFN 3x6mm | — | ✅ Active |
| U38 | CY7C65215-32LTXI | USB-Serial Bridge | Dual-channel, 12Mbps | QFN-32 5x5mm | C22451897 | ✅ Active |
| U40/U34/U22/U28/U21 | AP22615AWU-7 | USB Power Switch | 3A, adjustable limit | SOT-23-6 | C2680357 | ✅ Active |
| Multiple | TPD4E02B04DQAR-TP | USB ESD Protection | 4-ch, 0.25pF, ±12kV | USON-10 2.5x1mm | — | ✅ Active |
| TP14 | ESDS314DBVR | ESD Protection | Low capacitance | SOT-23-6 | — | ✅ Active |

---

## Component Analysis & Recommendations

### 1. USB Hub Controller (TUSB8041IRGCR)

**Current Component Analysis:**
- **Pros:** 4-port USB 3.0 hub, I2C configurable, over-current protection
- **Cons:** USB 3.0 only (not 3.1/3.2), no USB Billboard support
- **Thermal:** QFN-64 with thermal pad - good thermal performance
- **Availability:** Good (LCSC C544686)

**Recommendation:** ⚠️ **CONSIDER UPGRADE** - For future-proofing with USB 3.2 and alternate mode support.

**Recommended Replacement Options:**

**Option A: TUSB8044A (Texas Instruments)**
- **Specs:** USB 3.2 x1 Gen1 (5 Gbps), USB Billboard 1.21 support
- **Package:** QFN-64 9x9mm (same footprint)
- **Advantages:** 
  - USB Billboard support for alternate mode negotiation
  - Industrial temperature option available
  - Same package (drop-in replacement)
  - Future-proof for DisplayPort Alt Mode
- **LCSC:** Check availability
- **Cost:** Similar to TUSB8041
- **Impact:** Drop-in replacement, software changes for Billboard support

**Option B: TUSB8041A (Texas Instruments)**
- **Specs:** USB 3.1 Gen1 (5 Gbps)
- **Package:** QFN-64 9x9mm (same footprint)
- **Advantages:** 
  - Improved USB 3.1 specification
  - Same package (drop-in replacement)
  - Minimal changes required
- **LCSC:** Check availability
- **Cost:** Similar
- **Impact:** Drop-in replacement, minor spec improvement

**Option C: Keep TUSB8041**
- **Advantages:** Proven design, working implementation
- **Disadvantages:** Limited to USB 3.0, no Billboard support

**Recommendation:** Use **Option A (TUSB8044A)** if DisplayPort Alt Mode or future USB features are needed. Otherwise, keep current.

### 2. USB 2.0 Multiplexer (TS3USB30EDGSR) - 4 Instances

**Current Component Analysis:**
- **Pros:** 480Mbps support, integrated ESD, 1:2 multiplexing
- **Cons:** High on-resistance (6000mΩ), high capacitance (7.5pF)
- **Thermal:** VSSOP-10 package - adequate
- **Availability:** Good

**Recommendation:** ✅ **RECOMMEND REPLACEMENT** - Better performance drop-in replacement available.

**Recommended Replacement Options:**

**Option A: TS3USB221E (Texas Instruments)**
- **Specs:** USB 2.0, 1:2, 1000MHz bandwidth
- **Package:** VSSOP-10 3x3mm (same footprint) or UQFN 2x1.5mm
- **Advantages:**
  - Lower on-resistance: 3000mΩ (vs 6000mΩ)
  - Lower capacitance: 3.5pF (vs 7.5pF)
  - Better ESD: 12kV HBM
  - Drop-in replacement (VSSOP-10 option)
- **LCSC:** Check availability
- **Cost:** Similar
- **Impact:** Drop-in replacement, better signal integrity

**Option B: Toshiba TDS4A212MX/TDS4B212MX**
- **Specs:** USB4/PCIe 5.0 support, 26-27.5GHz bandwidth
- **Package:** XQFN16 2.4x1.6mm
- **Advantages:**
  - Future-proof for USB4/Thunderbolt
  - Very low power: 150μA
  - Much higher bandwidth
- **LCSC:** Check availability
- **Cost:** Higher
- **Impact:** New footprint, major redesign

**Recommendation:** Use **Option A (TS3USB221E)** for immediate improvement with minimal impact.

### 3. USB-C PD Controller (FUSB302BMPX)

**Current Component Analysis:**
- **Pros:** USB PD 2.0 support, I2C control, dead battery support
- **Cons:** Only PD 2.0 (not 3.0/3.1), Type-C 1.3 (not 2.1)
- **Thermal:** WQFN-14 2.5x2.5mm - adequate
- **Availability:** Good (LCSC C132291)

**Recommendation:** ⚠️ **CONSIDER UPGRADE** - For PD 3.1 and Type-C 2.1 compliance.

**Recommended Replacement Options:**

**Option A: FUSB15200 (onsemi)**
- **Specs:** USB PD 3.1 & Type-C 2.1, dual-port
- **Package:** QFN-40 5x5mm
- **Advantages:**
  - PD 3.1 support (up to 240W EPR)
  - Type-C 2.1 compliance
  - Dual-port support
  - Integrated Arm Cortex-M0+ MCU
  - 132KB flash, 6KB SRAM
  - Open-source firmware
  - Integrated VCONN switch
- **LCSC:** Check availability
- **Cost:** Higher than FUSB302
- **Impact:** Larger footprint, software changes required

**Option B: HUSB239 (Hynetek)**
- **Specs:** USB PD 3.1 & Type-C 2.1, autonomous
- **Package:** QFN-16 3x3mm
- **Advantages:**
  - Autonomous DRP controller (no firmware needed)
  - Up to 48V/5A EPR support
  - Integrated VBUS switch driver
  - Very low power: <75μA
  - Compact package
- **LCSC:** Check availability
- **Cost:** Similar to FUSB302
- **Impact:** Similar footprint size, software changes for PD 3.1

**Option C: UM3506 (Unicmicro)**
- **Specs:** USB PD 3.0/3.1 & Type-C 1.4
- **Package:** QFN-24 or QFN-32
- **Advantages:**
  - 32-bit RISC-V core at 33MHz
  - Internal TCPM+TCPC architecture
  - Complete software library
  - Programmable
- **LCSC:** Check availability
- **Cost:** Similar
- **Impact:** New footprint, software changes

**Recommendation:** Use **Option B (HUSB239)** for autonomous PD 3.1 with minimal software complexity.

### 4. USB-C Multiplexer (TMUXHS4446RETR)

**Current Component Analysis:**
- **Pros:** 10Gbps support, DisplayPort 2.1, passive switch
- **Cons:** Limited to USB 3.2 Gen 2 (not USB4)
- **Thermal:** QFN 3x6mm - adequate
- **Availability:** Good

**Recommendation:** ⚠️ **CONSIDER UPGRADE** - For USB4/Thunderbolt 4 future-proofing.

**Recommended Replacement Options:**

**Option A: TMUXHS4512 (Texas Instruments)**
- **Specs:** USB4 up to 20Gbps, DisplayPort UHBR20
- **Package:** QFN 3x6mm (same footprint)
- **Advantages:**
  - USB4 support up to 20Gbps
  - DisplayPort 1.4/2.1 up to UHBR20
  - Same package (drop-in replacement)
  - Future-proof for Thunderbolt 4
- **LCSC:** Check availability
- **Cost:** Similar
- **Impact:** Drop-in replacement, no layout changes

**Option B: TMUXHS4446-Q1 (Texas Instruments)**
- **Specs:** Same as TMUXHS4446
- **Package:** QFN 3x6mm (same footprint)
- **Advantages:**
  - Automotive qualified
  - AEC-Q101 qualified
  - Automotive temperature range: -40°C to 125°C
- **LCSC:** Check availability
- **Cost:** Similar
- **Impact:** Drop-in replacement, automotive certification

**Recommendation:** Use **Option A (TMUXHS4512)** if USB4/Thunderbolt 4 is planned. Otherwise, keep current.

### 5. USB-Serial Bridge (CY7C65215-32LTXI)

**Current Component Analysis:**
- **Pros:** Dual-channel (UART/I2C/SPI), 12Mbps, CAPSENSE support
- **Cons:** 32-pin package (larger than needed for single channel)
- **Thermal:** QFN-32 5x5mm - adequate
- **Availability:** Good (LCSC C22451897)

**Recommendation:** ✅ **KEEP** - Excellent component, dual-channel flexibility is valuable.

**Alternative Options (if single channel is sufficient):**

**Option A: CY7C65211-24LTXI**
- **Specs:** Single-channel, 12Mbps
- **Package:** QFN-24 5x5mm (smaller)
- **Advantages:** Smaller package, lower cost
- **LCSC:** Check availability
- **Impact:** Smaller footprint, but loses dual-channel flexibility

**Recommendation:** Keep current CY7C65215 unless space is very constrained.

### 6. USB Power Switch (AP22615AWU-7) - 5 Instances

**Current Component Analysis:**
- **Pros:** 3A output, adjustable current limit, OVP, PD3.0 FRS
- **Cons:** Limited to 5.5V input
- **Thermal:** SOT-23-6 package - adequate for 3A
- **Availability:** Good (LCSC C2680357)

**Recommendation:** ✅ **KEEP** - Excellent power switch with good protection features.

**Alternative Options (if higher current needed):**

**Option A: TPS25940 (Texas Instruments)**
- **Specs:** Up to 5A, programmable current limit
- **Package:** SOT-583 or similar
- **Advantages:** Higher current, better thermal, precision current sense
- **LCSC:** Check availability
- **Cost:** Similar
- **Impact:** New footprint, only if 5A needed

**Recommendation:** Keep current AP22615 unless higher current is required.

### 7. USB ESD Protection (TPD4E02B04DQAR-TP) - 6 Instances

**Current Component Analysis:**
- **Pros:** 4-channel, 0.25pF capacitance, ±12kV ESD, 10Gbps support
- **Cons:** No 48V short-to-VBUS protection
- **Thermal:** USON-10 2.5x1mm - excellent
- **Availability:** Good

**Recommendation:** ⚠️ **CONSIDER ADDING** TPD4S480 for USB-C specific protection.

**Recommended Addition:**

**Option A: TPD4S480 (Texas Instruments)**
- **Specs:** 48V short-to-VBUS protection, USB-C specific
- **Package:** USON-10 or similar
- **Advantages:**
  - 48V overvoltage protection
  - Designed for USB-C PD-EPR
  - IEC ESD protection for CC1, CC2, SBU1, SBU2
  - Eliminates need for external high-voltage TVS
- **LCSC:** Check availability
- **Cost:** Moderate
- **Impact:** Add 1-2 components for USB-C ports

**Recommendation:** Add TPD4S480 to USB-C ports for PD-EPR support (48V protection).

---

## Summary of Recommendations

### High Priority Replacements

| Component | Current | Recommended | Reason | Impact |
|-----------|---------|-------------|--------|--------|
| TS3USB30EDGSR (4x) | VSSOP-10 | TS3USB221E VSSOP-10 | Better performance, drop-in | Medium |
| FUSB302BMPX | WQFN-14 | HUSB239 QFN-16 | PD 3.1, autonomous | High |

### Medium Priority Replacements

| Component | Current | Recommended | Reason | Impact |
|-----------|---------|-------------|--------|--------|
| TUSB8041IRGCR | QFN-64 | TUSB8044A QFN-64 | USB 3.2, Billboard | Medium |
| TMUXHS4446RETR | QFN 3x6 | TMUXHS4512 QFN 3x6 | USB4 support | Medium |

### Low Priority / Optional

| Component | Current | Recommended | Reason | Impact |
|-----------|---------|-------------|--------|--------|
| CY7C65215-32LTXI | QFN-32 | Keep current | Dual-channel valuable | None |
| AP22615AWU-7 (5x) | SOT-23-6 | Keep current | Excellent specs | None |
| TPD4E02B04 (6x) | USON-10 | Add TPD4S480 | 48V protection | Low |

---

## Implementation Plan

### Phase 1: Performance Improvement (Immediate)

**Replace TS3USB30EDGSR with TS3USB221E (4 instances)**

**Steps:**
1. Update schematic: Replace U37, U41, U42, U31
2. Same footprint (VSSOP-10) - drop-in replacement
3. Verify signal integrity improvement
4. Test functionality

**Expected Benefits:**
- 50% reduction in on-resistance
- 50% reduction in capacitance
- Better signal integrity
- No layout changes

### Phase 2: Future-Proofing (Short-term)

**Replace FUSB302BMPX with HUSB239**

**Steps:**
1. Update schematic: Replace U23
2. Create new footprint for QFN-16
3. Update PCB layout
4. Update firmware for PD 3.1 support
5. Test PD negotiation

**Expected Benefits:**
- PD 3.1 support (up to 240W EPR)
- Type-C 2.1 compliance
- Autonomous operation (simpler firmware)
- Similar footprint size

### Phase 3: Advanced Features (Medium-term)

**Replace TUSB8041 with TUSB8044A (if DisplayPort Alt Mode needed)**

**Steps:**
1. Update schematic: Replace U25
2. Same footprint (QFN-64) - drop-in replacement
3. Update firmware for USB Billboard support
4. Test alternate mode negotiation

**Expected Benefits:**
- USB 3.2 support
- USB Billboard for alternate modes
- Better DisplayPort Alt Mode support
- No layout changes

### Phase 4: Future-Proofing (Optional)

**Replace TMUXHS4446 with TMUXHS4512 (if USB4/Thunderbolt 4 planned)**

**Steps:**
1. Update schematic: Replace U35
2. Same footprint (QFN 3x6) - drop-in replacement
3. Verify signal integrity at 20Gbps
4. Test USB4/Thunderbolt compatibility

**Expected Benefits:**
- USB4 support up to 20Gbps
- Thunderbolt 4 compatibility
- DisplayPort UHBR20 support
- No layout changes

---

## Cost Analysis

### Current BOM Cost (USB ICs Only)
- TUSB8041IRGCR: ~$3.00
- TS3USB30EDGSR (4x): ~$2.00 ($0.50 each)
- FUSB302BMPX: ~$1.00
- TMUXHS4446RETR: ~$1.50
- CY7C65215-32LTXI: ~$2.00
- AP22615AWU-7 (5x): ~$2.00 ($0.40 each)
- TPD4E02B04 (6x): ~$3.00 ($0.50 each)
- ESDS314DBVR: ~$0.30
- **Total:** ~$14.80

### After Replacements (High Priority)
- TS3USB221E (4x): ~$2.00 ($0.50 each)
- HUSB239: ~$1.00
- **Change:** $0.00 (same cost)

### After All Replacements
- TUSB8044A: ~$3.50
- TS3USB221E (4x): ~$2.00
- HUSB239: ~$1.00
- TMUXHS4512: ~$2.00
- TPD4S480 (2x): ~$1.00
- **Total:** ~$16.50
- **Increase:** ~$1.70

**Conclusion:** Minimal cost increase for significant performance and future-proofing improvements.

---

## Risk Assessment

### Low Risk
- TS3USB221E replacement (same footprint, better specs)
- TUSB8044A replacement (same footprint, drop-in)
- TMUXHS4512 replacement (same footprint, drop-in)

### Medium Risk
- HUSB239 replacement (different footprint, firmware changes)
- TPD4S480 addition (new component, validation needed)

### High Risk
- None identified in USB ICs

---

## Recommendations Summary

### Immediate Actions (High Priority)
1. ✅ **Replace TS3USB30EDGSR with TS3USB221E** (4 instances) - Performance improvement
2. ✅ **Add TPD4S480 to USB-C ports** - 48V protection for PD-EPR

### Short-term Actions (Medium Priority)
3. ⚠️ **Replace FUSB302BMPX with HUSB239** - PD 3.1 support
4. ⚠️ **Replace TUSB8041 with TUSB8044A** - USB 3.2/Billboard support

### Long-term Actions (Low Priority)
5. 📋 **Replace TMUXHS4446 with TMUXHS4512** - USB4/Thunderbolt 4 support
6. 📋 **Evaluate USB-Serial bridge** - Consider CY7C65211 if single channel sufficient

---

## Conclusion

The current USB interface IC selection is generally good and modern. The key improvements focus on:
1. **Performance optimization** (lower resistance, better signal integrity)
2. **Future-proofing** (PD 3.1, USB 3.2, USB4)
3. **Enhanced protection** (48V short-to-VBUS protection)

All recommended replacements maintain or improve functionality while reducing risk and improving performance. The most impactful change is the TS3USB221E replacement, which offers immediate signal integrity improvements with minimal risk.