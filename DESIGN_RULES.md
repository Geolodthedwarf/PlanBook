# PlanBook PCB Design Rules

## Standard Design Rules for PlanBook Project

### Board Specifications
- **Standard Board Thickness**: 1.6mm (for mechanical strength)
- **Copper Thickness**: 0.035mm (1oz)
- **Dielectric Material**: FR4 with εr=4.5, loss_tangent=0.02
- **Copper Finish**: ENIG (Electroless Nickel Immersion Gold)
- **Solder Mask**: Black
- **Silkscreen**: White

### Layer Stackup (Standard 4-Layer)
```
F.SilkS (Top Silkscreen)
F.Paste (Top Solder Paste)
F.Mask (Top Solder Mask) - 0.01mm
F.Cu (Top Copper) - 0.035mm
Dielectric 1 - 0.1mm FR4
In1.Cu (Inner Layer 1) - 0.035mm
Dielectric 2 - 0.64mm FR4
In2.Cu (Inner Layer 2) - 0.035mm
Dielectric 3 - 0.64mm FR4
B.Cu (Bottom Copper) - 0.035mm
Dielectric 4 - 0.1mm FR4
B.Mask (Bottom Solder Mask) - 0.01mm
B.Paste (Bottom Solder Paste)
B.SilkS (Bottom Silkscreen)
```

### Trace Width Rules
- **Minimum Signal Trace**: 0.15mm
- **Default Signal Trace**: 0.2mm
- **Power Trace**: 0.3mm
- **High-Current Trace**: 0.6mm
- **High-Speed Signal**: 0.15mm (impedance controlled)

### Clearance Rules
- **Default Clearance**: 0.15mm
- **Power Clearance**: 0.2mm
- **High-Speed Clearance**: 0.18mm
- **Minimum Clearance**: 0.1mm
- **Pad to Mask Clearance**: 0.05mm

### Via Rules
- **Default Via**: 0.6mm diameter / 0.3mm drill
- **Power Via**: 0.8mm diameter / 0.4mm drill
- **Minimum Via**: 0.4mm diameter / 0.2mm drill
- **Micro Via**: 0.3mm diameter / 0.15mm drill
- **Minimum Micro Via**: 0.2mm diameter / 0.1mm drill

### Drill Rules
- **Minimum Drill Size**: 0.3mm
- **Standard Drill Sizes**: 0.3mm, 0.4mm, 0.6mm, 0.8mm, 1.0mm, 1.1mm, 1.6mm, 2.2mm

### Zone Rules
- **Default Zone Clearance**: 0.2mm
- **Thermal Relief Gap**: 0.15mm
- **Thermal Relief Spoke Width**: 0.25mm
- **Thermal Relief Spoke Angle**: 45°

### Silk Screen Rules
- **Silk Screen Clearance**: 0.15mm
- **Minimum Text Height**: 0.8mm
- **Minimum Text Width**: 0.15mm

### Solder Mask Rules
- **Solder Mask Clearance**: 0.05mm
- **Minimum Solder Mask Width**: 0.1mm

### Special Rules by Board Type

#### Motherboard (6-Layer)
- Additional power planes on In1.Cu and In4.Cu
- Standard 4-layer rules apply to signal layers
- Extra ground stitching vias around board edges

#### Charger Board (4-Layer)
- Follow standard 4-layer rules
- Power traces use 0.6mm minimum width
- Additional thermal vias under power components

#### Keyboard Board (4-Layer)
- Follow standard 4-layer rules
- Key switch holes: 1.27mm, 1.7018mm, 3.429mm (for stabilizers)
- ESD protection on keyboard matrix lines

#### WiFi Board (4-Layer)
- Follow standard 4-layer rules
- Impedance-controlled routing for PCIe signals
- Ground stitching vias around high-speed sections

#### Headphones Board (2-Layer)
- Simplified layer stackup
- Standard trace widths and clearances
- Ground pour on bottom layer

### Manufacturing Notes
- **Tenting**: Front and back solder mask tenting
- **Panelization**: Standard 100mm x 100mm panels with 5mm spacing
- **Tooling Holes**: 1.6mm diameter at panel corners
- **Fiducials**: 1mm copper with 0.5mm opening, 3 per panel

### Design Constraints
- **Minimum Annular Ring**: 0.15mm
- **Minimum Hole to Hole Spacing**: 0.3mm
- **Minimum Edge Clearance**: 0.2mm
- **Minimum Solder Paste Spacing**: 0.15mm

### High-Speed Design Rules
- **USB 2.0**: 90Ω differential, length matching ±5mil
- **HDMI**: 100Ω differential, length matching ±10mil
- **PCIe**: 90Ω differential, length matching ±5mil
- **I2C**: No special requirements
- **SPI**: No special requirements

### Testing Requirements
- **Electrical Test**: 100% net list verification
- **Flying Probe**: Recommended for prototype validation
- **AOI**: Automated Optical Inspection for component placement
- **X-Ray**: For BGA and QFN components

### File Naming Convention
- **Gerber Files**: [board_name]_[layer].gbr
- **Drill Files**: [board_name]-NPTH.drl, [board_name]-PTH.drl
- **BOM**: [board_name]_bom.csv
- **Pick and Place**: [board_name]_pos.csv

### Revision Control
- **Version**: Major.Minor.Patch format
- **Revision Letter**: A, B, C, etc. for production revisions
- **Date**: YYYY-MM-DD format
- **Change Log**: Document all significant changes