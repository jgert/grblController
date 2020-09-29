; Start of the program
M190 S50.000000
M109 S250.000000
;Sliced at: Sun 03-07-2016 17:55:50
;Basic settings: Layer height: 0.3 Walls: 1.2 Fill: 20
;Print time: 1 hour 9 minutes
;Filament used: 2.584m 20.0g
;Filament cost: 0.37
;M190 S50 ;Uncomment to add your own bed temperature line
;M109 S250 ;Uncomment to add your own temperature line
G21        ;metric values
G90        ;absolute positioning
M82        ;set extruder to absolute mode
G28 X0 Y0  ;move X/Y to min endstops
G0 X100 Y100
Z10
G28 Z0     ;move Z to min endstops
G29
G1 Z15.0 F100 ;move the platform down 15mm
G92 E0                  ;zero the extruded length
G1 F200 E3              ;extrude 3mm of feed stock
G92 E0                  ;zero the extruded length again
G1 F10800
;Put printing message on LCD screen
;?IF_EXT0?M109 T0 S?TEMP0?
M117 Printing...

;Layer count: 19
;LAYER:0
M107
G0 F10800 X48.217 Y22.131 Z0.300
;TYPE:SKIRT
G1 F1800 X48.687 Y21.229 E0.01913
G1 X48.936 Y20.744 E0.02939
G1 X49.723 Y19.693 E0.05409
G1 X50.013 Y19.303 E0.06323
G1 X51.064 Y18.293 E0.09065
G1 X51.455 Y17.957 E0.10034
