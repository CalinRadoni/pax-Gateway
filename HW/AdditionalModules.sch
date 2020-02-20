EESchema Schematic File Version 4
LIBS:esp32-rfm-gateway-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title "ESP32 RFM69/RFM9x Gateway"
Date "2019-05-18"
Rev "38"
Comp "Calin Radoni"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L calin:AT_CryptoAuth U?
U 1 1 5CCB0E97
P 2200 4250
AR Path="/5CCB0E97" Ref="U?"  Part="1" 
AR Path="/5CCB086C/5CCB0E97" Ref="U40"  Part="1" 
F 0 "U40" H 2200 4500 50  0000 C CNN
F 1 "AT_CryptoAuth" H 2200 4000 50  0000 C CNN
F 2 "CalinGeneric:SOIC-8-HS" H 2200 4250 50  0001 C CNN
F 3 "" H 2200 4250 50  0001 C CNN
F 4 "ATCrypto" H 0   -200 50  0001 C CNN "Variant"
F 5 "ATSHA204A/ATECC508A/ATECC608A-SSHDA" H 0   -200 50  0001 C CNN "part-number"
F 6 "*" H 0   -200 50  0001 C CNN "characteristics"
F 7 "Microchip" H 0   -200 50  0001 C CNN "manufacturer"
F 8 "SOIC-8 3.90mm" H 0   -200 50  0001 C CNN "package"
F 9 "DNP" H 0   0   50  0001 C CNN "Notes"
	1    2200 4250
	1    0    0    -1  
$EndComp
$Comp
L calin:C C?
U 1 1 5CCB0E9E
P 1350 4250
AR Path="/5CCB0E9E" Ref="C?"  Part="1" 
AR Path="/5CCB086C/5CCB0E9E" Ref="C40"  Part="1" 
F 0 "C40" H 1375 4350 50  0000 L CNN
F 1 "100nF" V 1400 3950 50  0000 L CNN
F 2 "CalinGeneric:C0805HS" H 1388 4100 50  0001 C CNN
F 3 "" H 1350 4250 50  0000 C CNN
F 4 "ATCrypto" H 0   -200 50  0001 C CNN "Variant"
F 5 "100 nF / 50V / X7R" H 0   -200 50  0001 C CNN "characteristics"
F 6 "Samsung" H 0   -200 50  0001 C CNN "manufacturer"
F 7 "0805" H 0   -200 50  0001 C CNN "package"
F 8 "CL21B104KBCNNNC" H 0   -200 50  0001 C CNN "part-number"
F 9 "DNP" H 0   0   50  0001 C CNN "Notes"
	1    1350 4250
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5CCB0EA5
P 2600 4000
AR Path="/5CCB0EA5" Ref="#PWR?"  Part="1" 
AR Path="/5CCB086C/5CCB0EA5" Ref="#PWR0159"  Part="1" 
F 0 "#PWR0159" H 2600 3850 50  0001 C CNN
F 1 "+3V3" H 2600 4140 50  0000 C CNN
F 2 "" H 2600 4000 50  0000 C CNN
F 3 "" H 2600 4000 50  0000 C CNN
	1    2600 4000
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5CCB0EAB
P 1350 4000
AR Path="/5CCB0EAB" Ref="#PWR?"  Part="1" 
AR Path="/5CCB086C/5CCB0EAB" Ref="#PWR0160"  Part="1" 
F 0 "#PWR0160" H 1350 3850 50  0001 C CNN
F 1 "+3V3" H 1350 4140 50  0000 C CNN
F 2 "" H 1350 4000 50  0000 C CNN
F 3 "" H 1350 4000 50  0000 C CNN
	1    1350 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CCB0EB1
P 1350 4500
AR Path="/5CCB0EB1" Ref="#PWR?"  Part="1" 
AR Path="/5CCB086C/5CCB0EB1" Ref="#PWR0161"  Part="1" 
F 0 "#PWR0161" H 1350 4250 50  0001 C CNN
F 1 "GND" H 1350 4350 50  0000 C CNN
F 2 "" H 1350 4500 50  0000 C CNN
F 3 "" H 1350 4500 50  0000 C CNN
	1    1350 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 4000 1350 4100
Wire Wire Line
	1350 4400 1350 4500
Wire Wire Line
	2600 4000 2600 4100
Wire Wire Line
	2600 4100 2500 4100
$Comp
L power:GND #PWR?
U 1 1 5CCB0EBB
P 1800 4500
AR Path="/5CCB0EBB" Ref="#PWR?"  Part="1" 
AR Path="/5CCB086C/5CCB0EBB" Ref="#PWR0162"  Part="1" 
F 0 "#PWR0162" H 1800 4250 50  0001 C CNN
F 1 "GND" H 1800 4350 50  0000 C CNN
F 2 "" H 1800 4500 50  0000 C CNN
F 3 "" H 1800 4500 50  0000 C CNN
	1    1800 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 4400 1800 4400
Wire Wire Line
	1800 4400 1800 4500
Wire Wire Line
	2500 4300 2900 4300
Wire Wire Line
	2500 4400 2900 4400
Text Label 2650 4300 0    50   ~ 0
SCL
Text Label 2650 4400 0    50   ~ 0
SDA
Text Label 1750 1200 0    50   ~ 0
SDA
Text Label 1750 1400 0    50   ~ 0
SCL
Wire Wire Line
	1500 1200 2000 1200
Wire Wire Line
	1500 1400 2000 1400
Text Notes 3150 4400 0    50   Italic 0
AT_CryptoAuth is a placeholder compatible with:\n- ATSHA204A\n- ATECC508A\n- ATECC608A
Text HLabel 1500 1200 0    50   UnSpc ~ 0
SDA
Text HLabel 1500 1400 0    50   UnSpc ~ 0
SCL
$Comp
L calin:LED D?
U 1 1 5CBFAF05
P 8250 1300
AR Path="/5CBFAF05" Ref="D?"  Part="1" 
AR Path="/5CCB086C/5CBFAF05" Ref="D10"  Part="1" 
F 0 "D10" H 8250 1400 40  0000 C CNN
F 1 "LED" H 8400 1250 50  0000 C CNN
F 2 "CalinGeneric:LED0805HS" H 8250 1300 50  0001 C CNN
F 3 "" H 8250 1300 50  0001 C CNN
	1    8250 1300
	1    0    0    1   
$EndComp
$Comp
L calin:R R?
U 1 1 5CBFAF0C
P 7850 1300
AR Path="/5CBFAF0C" Ref="R?"  Part="1" 
AR Path="/5CCB086C/5CBFAF0C" Ref="R10"  Part="1" 
F 0 "R10" V 7930 1300 40  0000 C CNN
F 1 "100" V 7850 1300 40  0000 C CNN
F 2 "CalinGeneric:R0805HS" V 7780 1300 30  0001 C CNN
F 3 "" H 7850 1300 30  0000 C CNN
F 4 "100 1%" H -650 100 50  0001 C CNN "characteristics"
F 5 "Panasonic" H -650 100 50  0001 C CNN "manufacturer"
F 6 "0805" H -650 100 50  0001 C CNN "package"
F 7 "ERJ-6ENF1000V" H -650 100 50  0001 C CNN "part-number"
	1    7850 1300
	0    1    1    0   
$EndComp
Wire Wire Line
	8000 1300 8100 1300
$Comp
L power:+3V3 #PWR?
U 1 1 5CBFAF15
P 8500 1300
AR Path="/5CBFAF15" Ref="#PWR?"  Part="1" 
AR Path="/5CCB086C/5CBFAF15" Ref="#PWR0163"  Part="1" 
F 0 "#PWR0163" H 8500 1150 50  0001 C CNN
F 1 "+3V3" V 8500 1500 50  0000 C CNN
F 2 "" H 8500 1300 50  0000 C CNN
F 3 "" H 8500 1300 50  0000 C CNN
	1    8500 1300
	0    1    1    0   
$EndComp
Wire Wire Line
	8400 1300 8500 1300
$Comp
L calin:LED D?
U 1 1 5CBFAF1C
P 8250 1600
AR Path="/5CBFAF1C" Ref="D?"  Part="1" 
AR Path="/5CCB086C/5CBFAF1C" Ref="D11"  Part="1" 
F 0 "D11" H 8250 1700 40  0000 C CNN
F 1 "LED" H 8400 1550 50  0000 C CNN
F 2 "CalinGeneric:LED0805HS" H 8250 1600 50  0001 C CNN
F 3 "" H 8250 1600 50  0001 C CNN
	1    8250 1600
	1    0    0    1   
$EndComp
$Comp
L calin:R R?
U 1 1 5CBFAF23
P 7850 1600
AR Path="/5CBFAF23" Ref="R?"  Part="1" 
AR Path="/5CCB086C/5CBFAF23" Ref="R11"  Part="1" 
F 0 "R11" V 7930 1600 40  0000 C CNN
F 1 "100" V 7850 1600 40  0000 C CNN
F 2 "CalinGeneric:R0805HS" V 7780 1600 30  0001 C CNN
F 3 "" H 7850 1600 30  0000 C CNN
F 4 "100 1%" H -650 100 50  0001 C CNN "characteristics"
F 5 "Panasonic" H -650 100 50  0001 C CNN "manufacturer"
F 6 "0805" H -650 100 50  0001 C CNN "package"
F 7 "ERJ-6ENF1000V" H -650 100 50  0001 C CNN "part-number"
	1    7850 1600
	0    1    1    0   
$EndComp
Wire Wire Line
	8000 1600 8100 1600
$Comp
L power:+3V3 #PWR?
U 1 1 5CBFAF2C
P 8500 1600
AR Path="/5CBFAF2C" Ref="#PWR?"  Part="1" 
AR Path="/5CCB086C/5CBFAF2C" Ref="#PWR0164"  Part="1" 
F 0 "#PWR0164" H 8500 1450 50  0001 C CNN
F 1 "+3V3" V 8500 1800 50  0000 C CNN
F 2 "" H 8500 1600 50  0000 C CNN
F 3 "" H 8500 1600 50  0000 C CNN
	1    8500 1600
	0    1    1    0   
$EndComp
Wire Wire Line
	8400 1600 8500 1600
$Comp
L calin:LED D?
U 1 1 5CBFAF33
P 8250 1900
AR Path="/5CBFAF33" Ref="D?"  Part="1" 
AR Path="/5CCB086C/5CBFAF33" Ref="D12"  Part="1" 
F 0 "D12" H 8250 2000 40  0000 C CNN
F 1 "LED" H 8400 1850 50  0000 C CNN
F 2 "CalinGeneric:LED0805HS" H 8250 1900 50  0001 C CNN
F 3 "" H 8250 1900 50  0001 C CNN
	1    8250 1900
	1    0    0    1   
$EndComp
$Comp
L calin:R R?
U 1 1 5CBFAF3A
P 7850 1900
AR Path="/5CBFAF3A" Ref="R?"  Part="1" 
AR Path="/5CCB086C/5CBFAF3A" Ref="R12"  Part="1" 
F 0 "R12" V 7930 1900 40  0000 C CNN
F 1 "100" V 7850 1900 40  0000 C CNN
F 2 "CalinGeneric:R0805HS" V 7780 1900 30  0001 C CNN
F 3 "" H 7850 1900 30  0000 C CNN
F 4 "100 1%" H -650 100 50  0001 C CNN "characteristics"
F 5 "Panasonic" H -650 100 50  0001 C CNN "manufacturer"
F 6 "0805" H -650 100 50  0001 C CNN "package"
F 7 "ERJ-6ENF1000V" H -650 100 50  0001 C CNN "part-number"
	1    7850 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	8000 1900 8100 1900
$Comp
L power:+3V3 #PWR?
U 1 1 5CBFAF43
P 8500 1900
AR Path="/5CBFAF43" Ref="#PWR?"  Part="1" 
AR Path="/5CCB086C/5CBFAF43" Ref="#PWR0165"  Part="1" 
F 0 "#PWR0165" H 8500 1750 50  0001 C CNN
F 1 "+3V3" V 8500 2100 50  0000 C CNN
F 2 "" H 8500 1900 50  0000 C CNN
F 3 "" H 8500 1900 50  0000 C CNN
	1    8500 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	8400 1900 8500 1900
$Comp
L calin:LED D?
U 1 1 5CBFAF4A
P 8250 2200
AR Path="/5CBFAF4A" Ref="D?"  Part="1" 
AR Path="/5CCB086C/5CBFAF4A" Ref="D13"  Part="1" 
F 0 "D13" H 8250 2300 40  0000 C CNN
F 1 "LED" H 8400 2150 50  0000 C CNN
F 2 "CalinGeneric:LED0805HS" H 8250 2200 50  0001 C CNN
F 3 "" H 8250 2200 50  0001 C CNN
	1    8250 2200
	1    0    0    1   
$EndComp
$Comp
L calin:R R?
U 1 1 5CBFAF51
P 7850 2200
AR Path="/5CBFAF51" Ref="R?"  Part="1" 
AR Path="/5CCB086C/5CBFAF51" Ref="R13"  Part="1" 
F 0 "R13" V 7930 2200 40  0000 C CNN
F 1 "100" V 7850 2200 40  0000 C CNN
F 2 "CalinGeneric:R0805HS" V 7780 2200 30  0001 C CNN
F 3 "" H 7850 2200 30  0000 C CNN
F 4 "100 1%" H -650 100 50  0001 C CNN "characteristics"
F 5 "Panasonic" H -650 100 50  0001 C CNN "manufacturer"
F 6 "0805" H -650 100 50  0001 C CNN "package"
F 7 "ERJ-6ENF1000V" H -650 100 50  0001 C CNN "part-number"
	1    7850 2200
	0    1    1    0   
$EndComp
Wire Wire Line
	8000 2200 8100 2200
$Comp
L power:+3V3 #PWR?
U 1 1 5CBFAF5A
P 8500 2200
AR Path="/5CBFAF5A" Ref="#PWR?"  Part="1" 
AR Path="/5CCB086C/5CBFAF5A" Ref="#PWR0166"  Part="1" 
F 0 "#PWR0166" H 8500 2050 50  0001 C CNN
F 1 "+3V3" V 8500 2400 50  0000 C CNN
F 2 "" H 8500 2200 50  0000 C CNN
F 3 "" H 8500 2200 50  0000 C CNN
	1    8500 2200
	0    1    1    0   
$EndComp
Wire Wire Line
	8400 2200 8500 2200
$Comp
L calin:Symbol_Generic SYM?
U 1 1 5CBFAF61
P 9150 1300
AR Path="/5CBFAF61" Ref="SYM?"  Part="1" 
AR Path="/5CCB086C/5CBFAF61" Ref="SYM10"  Part="1" 
F 0 "SYM10" H 9300 1300 50  0001 C CNN
F 1 "LightPipe" H 9228 1300 50  0000 L CNN
F 2 "CalinGeneric:SLP3-xxx-150-x" H 9150 1300 50  0001 C CNN
F 3 "" V 9150 1300 50  0001 C CNN
F 4 "LightPipe" H -650 100 50  0001 C CNN "characteristics"
F 5 "BIVAR" H -650 100 50  0001 C CNN "manufacturer"
F 6 "SLP3-XXX-XXX-X" H -650 100 50  0001 C CNN "package"
F 7 "SLP3-150-150-F" H -650 100 50  0001 C CNN "part-number"
	1    9150 1300
	1    0    0    -1  
$EndComp
$Comp
L calin:Symbol_Generic SYM?
U 1 1 5CBFAF67
P 9150 1600
AR Path="/5CBFAF67" Ref="SYM?"  Part="1" 
AR Path="/5CCB086C/5CBFAF67" Ref="SYM11"  Part="1" 
F 0 "SYM11" H 9300 1600 50  0001 C CNN
F 1 "LightPipe" H 9228 1600 50  0000 L CNN
F 2 "CalinGeneric:SLP3-xxx-150-x" H 9150 1600 50  0001 C CNN
F 3 "" V 9150 1600 50  0001 C CNN
F 4 "LightPipe" H -650 100 50  0001 C CNN "characteristics"
F 5 "BIVAR" H -650 100 50  0001 C CNN "manufacturer"
F 6 "SLP3-XXX-XXX-X" H -650 100 50  0001 C CNN "package"
F 7 "SLP3-150-150-F" H -650 100 50  0001 C CNN "part-number"
	1    9150 1600
	1    0    0    -1  
$EndComp
$Comp
L calin:Symbol_Generic SYM?
U 1 1 5CBFAF6D
P 9150 1900
AR Path="/5CBFAF6D" Ref="SYM?"  Part="1" 
AR Path="/5CCB086C/5CBFAF6D" Ref="SYM12"  Part="1" 
F 0 "SYM12" H 9300 1900 50  0001 C CNN
F 1 "LightPipe" H 9228 1900 50  0000 L CNN
F 2 "CalinGeneric:SLP3-xxx-150-x" H 9150 1900 50  0001 C CNN
F 3 "" V 9150 1900 50  0001 C CNN
F 4 "LightPipe" H -650 100 50  0001 C CNN "characteristics"
F 5 "BIVAR" H -650 100 50  0001 C CNN "manufacturer"
F 6 "SLP3-XXX-XXX-X" H -650 100 50  0001 C CNN "package"
F 7 "SLP3-150-150-F" H -650 100 50  0001 C CNN "part-number"
	1    9150 1900
	1    0    0    -1  
$EndComp
$Comp
L calin:Symbol_Generic SYM?
U 1 1 5CBFAF73
P 9150 2200
AR Path="/5CBFAF73" Ref="SYM?"  Part="1" 
AR Path="/5CCB086C/5CBFAF73" Ref="SYM13"  Part="1" 
F 0 "SYM13" H 9300 2200 50  0001 C CNN
F 1 "LightPipe" H 9228 2200 50  0000 L CNN
F 2 "CalinGeneric:SLP3-xxx-150-x" H 9150 2200 50  0001 C CNN
F 3 "" V 9150 2200 50  0001 C CNN
F 4 "LightPipe" H -650 100 50  0001 C CNN "characteristics"
F 5 "BIVAR" H -650 100 50  0001 C CNN "manufacturer"
F 6 "SLP3-XXX-XXX-X" H -650 100 50  0001 C CNN "package"
F 7 "SLP3-150-150-F" H -650 100 50  0001 C CNN "part-number"
	1    9150 2200
	1    0    0    -1  
$EndComp
$Comp
L calin:CS_2 J40
U 1 1 5CC0953E
P 1500 6550
F 0 "J40" V 1400 6550 60  0000 C CNN
F 1 "ph_1x2" V 1600 6550 50  0000 C CNN
F 2 "CalinConnectors:Pin_Header_Straight_1x02" H 1500 6600 60  0001 C CNN
F 3 "" H 1500 6600 60  0000 C CNN
	1    1500 6550
	1    0    0    -1  
$EndComp
$Comp
L calin:R R?
U 1 1 5CC095F4
P 2200 6250
AR Path="/5CC095F4" Ref="R?"  Part="1" 
AR Path="/5CCB086C/5CC095F4" Ref="R40"  Part="1" 
F 0 "R40" V 2280 6250 40  0000 C CNN
F 1 "10k" V 2200 6250 40  0000 C CNN
F 2 "CalinGeneric:R0805HS" V 2130 6250 30  0001 C CNN
F 3 "" H 2200 6250 30  0000 C CNN
F 4 "10k" H 0   0   50  0001 C CNN "characteristics"
F 5 "Vishay" H 0   0   50  0001 C CNN "manufacturer"
F 6 "0805" H 0   0   50  0001 C CNN "package"
F 7 "CRCW080510K0FKEA" H 0   0   50  0001 C CNN "part-number"
	1    2200 6250
	0    1    1    0   
$EndComp
$Comp
L calin:R R?
U 1 1 5CC096FF
P 2200 6850
AR Path="/5CC096FF" Ref="R?"  Part="1" 
AR Path="/5CCB086C/5CC096FF" Ref="R41"  Part="1" 
F 0 "R41" V 2280 6850 40  0000 C CNN
F 1 "10k" V 2200 6850 40  0000 C CNN
F 2 "CalinGeneric:R0805HS" V 2130 6850 30  0001 C CNN
F 3 "" H 2200 6850 30  0000 C CNN
F 4 "10k" H 0   0   50  0001 C CNN "characteristics"
F 5 "Vishay" H 0   0   50  0001 C CNN "manufacturer"
F 6 "0805" H 0   0   50  0001 C CNN "package"
F 7 "CRCW080510K0FKEA" H 0   0   50  0001 C CNN "part-number"
	1    2200 6850
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:BC817 Q40
U 1 1 5CC09CBF
P 2650 6250
F 0 "Q40" H 2841 6296 50  0000 L CNN
F 1 "BC817" H 2841 6205 50  0000 L CNN
F 2 "CalinGeneric:SOT-23" H 2850 6175 50  0001 L CIN
F 3 "" H 2650 6250 50  0001 L CNN
F 4 "BC817-40" H 0   0   50  0001 C CNN "characteristics"
F 5 "Diodes" H 0   0   50  0001 C CNN "manufacturer"
F 6 "SOT-23" H 0   0   50  0001 C CNN "package"
F 7 "BC817-40" H 0   0   50  0001 C CNN "part-number"
	1    2650 6250
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC817 Q41
U 1 1 5CC09D1F
P 2650 6850
F 0 "Q41" H 2841 6804 50  0000 L CNN
F 1 "BC817" H 2841 6895 50  0000 L CNN
F 2 "CalinGeneric:SOT-23" H 2850 6775 50  0001 L CIN
F 3 "" H 2650 6850 50  0001 L CNN
F 4 "BC817-40" H 0   0   50  0001 C CNN "characteristics"
F 5 "Diodes" H 0   0   50  0001 C CNN "manufacturer"
F 6 "SOT-23" H 0   0   50  0001 C CNN "package"
F 7 "BC817-40" H 0   0   50  0001 C CNN "part-number"
	1    2650 6850
	1    0    0    1   
$EndComp
Wire Wire Line
	2450 6250 2350 6250
Wire Wire Line
	2450 6850 2350 6850
Wire Wire Line
	2050 6250 1950 6250
Wire Wire Line
	1500 6250 1500 6350
Wire Wire Line
	2050 6850 1950 6850
Wire Wire Line
	1500 6850 1500 6750
Wire Wire Line
	2750 6650 2750 6600
Wire Wire Line
	2750 6600 2200 6600
Wire Wire Line
	2200 6600 1950 6350
Wire Wire Line
	1950 6350 1950 6250
Connection ~ 1950 6250
Wire Wire Line
	1950 6250 1500 6250
Wire Wire Line
	2750 6450 2750 6500
Wire Wire Line
	2750 6500 2200 6500
Wire Wire Line
	2200 6500 1950 6750
Wire Wire Line
	1950 6750 1950 6850
Connection ~ 1950 6850
Wire Wire Line
	1950 6850 1500 6850
Text Label 1650 6250 0    50   ~ 0
DTR
Text Label 1650 6850 0    50   ~ 0
RTS
Text Notes 3250 6850 0    50   ~ 0
DTR RTS    EN Boot\n  1   1  |  x   x\n  0   0  |  x   x\n  1   0  |  0   x\n  0   1  |  x   0\n\n x = pin not driven
Text HLabel 3500 6000 2    50   UnSpc ~ 0
ESP-EN
Text HLabel 3500 7100 2    50   UnSpc ~ 0
ESP-Boot
Wire Wire Line
	3500 6000 2750 6000
Wire Wire Line
	2750 6000 2750 6050
Wire Wire Line
	3500 7100 2750 7100
Wire Wire Line
	2750 7100 2750 7050
$Comp
L power:GND #PWR?
U 1 1 5CBEDDD9
P 7800 5750
AR Path="/5CBEDDD9" Ref="#PWR?"  Part="1" 
AR Path="/5CCB086C/5CBEDDD9" Ref="#PWR0171"  Part="1" 
F 0 "#PWR0171" H 7800 5500 50  0001 C CNN
F 1 "GND" H 7800 5600 50  0000 C CNN
F 2 "" H 7800 5750 50  0000 C CNN
F 3 "" H 7800 5750 50  0000 C CNN
	1    7800 5750
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5CBEDE2C
P 8700 5150
AR Path="/5CBEDE2C" Ref="#PWR?"  Part="1" 
AR Path="/5CCB086C/5CBEDE2C" Ref="#PWR0172"  Part="1" 
F 0 "#PWR0172" H 8700 5000 50  0001 C CNN
F 1 "+3V3" H 8700 5290 50  0000 C CNN
F 2 "" H 8700 5150 50  0000 C CNN
F 3 "" H 8700 5150 50  0000 C CNN
	1    8700 5150
	1    0    0    -1  
$EndComp
$Comp
L calin:C C?
U 1 1 5CBF000C
P 7050 5500
AR Path="/5CBF000C" Ref="C?"  Part="1" 
AR Path="/5CCB086C/5CBF000C" Ref="C41"  Part="1" 
F 0 "C41" H 7075 5600 50  0000 L CNN
F 1 "100nF" V 7100 5200 50  0000 L CNN
F 2 "CalinGeneric:C0805HS" H 7088 5350 50  0001 C CNN
F 3 "" H 7050 5500 50  0000 C CNN
F 4 "Sensor" H 550 0   50  0001 C CNN "Variant"
F 5 "100 nF / 50V / X7R" H 550 0   50  0001 C CNN "characteristics"
F 6 "Samsung" H 550 0   50  0001 C CNN "manufacturer"
F 7 "0805" H 550 0   50  0001 C CNN "package"
F 8 "CL21B104KBCNNNC" H 550 0   50  0001 C CNN "part-number"
	1    7050 5500
	1    0    0    -1  
$EndComp
Text Label 7500 5400 0    50   ~ 0
SDA
Text Label 7500 5250 0    50   ~ 0
SCL
$Comp
L power:GND #PWR?
U 1 1 5CBF25F5
P 7050 5750
AR Path="/5CBF25F5" Ref="#PWR?"  Part="1" 
AR Path="/5CCB086C/5CBF25F5" Ref="#PWR0173"  Part="1" 
F 0 "#PWR0173" H 7050 5500 50  0001 C CNN
F 1 "GND" H 7050 5600 50  0000 C CNN
F 2 "" H 7050 5750 50  0000 C CNN
F 3 "" H 7050 5750 50  0000 C CNN
	1    7050 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 5650 7050 5750
$Comp
L power:+3V3 #PWR?
U 1 1 5CBF4B8D
P 7050 5150
AR Path="/5CBF4B8D" Ref="#PWR?"  Part="1" 
AR Path="/5CCB086C/5CBF4B8D" Ref="#PWR0174"  Part="1" 
F 0 "#PWR0174" H 7050 5000 50  0001 C CNN
F 1 "+3V3" H 7050 5290 50  0000 C CNN
F 2 "" H 7050 5150 50  0000 C CNN
F 3 "" H 7050 5150 50  0000 C CNN
	1    7050 5150
	1    0    0    -1  
$EndComp
Text Notes 2200 4950 0    50   ~ 0
Default I2C Address of:\n- ATSHA204A is 0xC8/0xC9\n- ATECC508A is 0xC0/0xC1\n- ATECC608A is 0xC4/0xC5 (probably)
Text Notes 8350 5950 0    50   ~ 0
Default I2C address is 1000000 (0x80/0x81)
Wire Notes Line width 20 style dotted
	5650 1100 5650 7100
Wire Notes Line width 20 style dotted
	1200 5250 4900 5250
Wire Notes Line width 20 style dotted
	6400 4600 10450 4600
Wire Notes Line width 20 style dotted
	6400 3150 10450 3150
Wire Wire Line
	7700 2200 7200 2200
Text HLabel 7200 1300 0    50   Input ~ 0
LEDc0
Text HLabel 7200 1600 0    50   Input ~ 0
LEDc1
Text HLabel 7200 1900 0    50   Input ~ 0
LEDc2
Text HLabel 7200 2200 0    50   Input ~ 0
LEDc3
Wire Notes Line width 20 style dotted
	1200 3150 4900 3150
Wire Wire Line
	7700 1900 7200 1900
Wire Wire Line
	7700 1600 7200 1600
Wire Wire Line
	7700 1300 7200 1300
$Comp
L calin:HDC1080DMB U41
U 1 1 5CCCFB95
P 8200 5500
F 0 "U41" H 8200 5700 50  0000 C CNN
F 1 "HDC1080DMB" H 8200 5300 50  0000 C CNN
F 2 "CalinGeneric:WSON6-TI-HDC-HS" H 8200 5500 50  0001 C CNN
F 3 "" H 8200 5500 50  0001 C CNN
F 4 "Texas Instruments" H 8200 5800 50  0001 C CNN "manufacturer"
F 5 "HDC1080DMB" H 8200 5850 50  0001 C CNN "part-number"
F 6 "I2C Humidity and Temperature Sensor" H 8200 5900 50  0001 C CNN "characteristics"
F 7 "WSON6" H 8200 5950 50  0001 C CNN "package"
F 8 "Sensor" H 0   0   50  0001 C CNN "Variant"
	1    8200 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 5150 7050 5350
Wire Wire Line
	7900 5500 7800 5500
Wire Wire Line
	7800 5500 7800 5750
Wire Wire Line
	8700 5150 8700 5500
Wire Wire Line
	8700 5500 8500 5500
Wire Wire Line
	7900 5400 7400 5400
Wire Wire Line
	8500 5400 8600 5400
Wire Wire Line
	8600 5400 8600 5250
Wire Wire Line
	8600 5250 7400 5250
$Comp
L calin:C C?
U 1 1 5CD1A826
P 8200 3850
AR Path="/5CD1A826" Ref="C?"  Part="1" 
AR Path="/5CCB086C/5CD1A826" Ref="C10"  Part="1" 
F 0 "C10" H 8225 3950 50  0000 L CNN
F 1 "10uF" V 8250 3550 50  0000 L CNN
F 2 "CalinGeneric:C0805HS" H 8238 3700 50  0001 C CNN
F 3 "" H 8200 3850 50  0000 C CNN
F 4 "10 µF / 6,3 V" H 1700 -1650 50  0001 C CNN "characteristics"
F 5 "Samsung" H 1700 -1650 50  0001 C CNN "manufacturer"
F 6 "0805" H 1700 -1650 50  0001 C CNN "package"
F 7 "CL21B106KQQNNNE" H 1700 -1650 50  0001 C CNN "part-number"
	1    8200 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CD1A82C
P 8200 4100
AR Path="/5CD1A82C" Ref="#PWR?"  Part="1" 
AR Path="/5CCB086C/5CD1A82C" Ref="#PWR0169"  Part="1" 
F 0 "#PWR0169" H 8200 3850 50  0001 C CNN
F 1 "GND" H 8200 3950 50  0000 C CNN
F 2 "" H 8200 4100 50  0000 C CNN
F 3 "" H 8200 4100 50  0000 C CNN
	1    8200 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 4000 8200 4100
$Comp
L power:+3V3 #PWR?
U 1 1 5CD1A833
P 8200 3600
AR Path="/5CD1A833" Ref="#PWR?"  Part="1" 
AR Path="/5CCB086C/5CD1A833" Ref="#PWR0170"  Part="1" 
F 0 "#PWR0170" H 8200 3450 50  0001 C CNN
F 1 "+3V3" H 8200 3740 50  0000 C CNN
F 2 "" H 8200 3600 50  0000 C CNN
F 3 "" H 8200 3600 50  0000 C CNN
	1    8200 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 3600 8200 3700
$Comp
L calin:Symbol_Enclosure SYM9
U 1 1 5CE0FF1C
P 3800 2650
F 0 "SYM9" H 4050 2650 50  0001 C CNN
F 1 "Enclosure" H 3978 2675 50  0000 L CNN
F 2 "CalinGeneric:VirtualFootprint" H 3800 2650 50  0001 C CNN
F 3 "" H 3800 2650 50  0001 C CNN
F 4 "Gainta G706 (dark grey) or G738 (light grey)" H 800 50  50  0001 C CNN "characteristics"
F 5 "Gainta" H 0   0   50  0001 C CNN "manufacturer"
F 6 "*" H 0   0   50  0001 C CNN "package"
F 7 "Gainta G706" H 0   0   50  0001 C CNN "part-number"
	1    3800 2650
	1    0    0    -1  
$EndComp
$Comp
L calin:Symbol_Antenna SYM6
U 1 1 5CE1322C
P 3900 2200
F 0 "SYM6" H 4050 2250 50  0001 C CNN
F 1 "Antenna 868MHz" H 3950 2200 50  0000 L CNN
F 2 "CalinGeneric:VirtualFootprint" H 3900 2200 50  0001 C CNN
F 3 "" H 3900 2200 50  0001 C CNN
F 4 "868 MHz, 90 deg. SMA Male connector" H 0   -150 50  0001 C CNN "characteristics"
F 5 "SR Passives" H 0   -150 50  0001 C CNN "manufacturer"
F 6 "*" H 0   -150 50  0001 C CNN "package"
F 7 "868M-ANT410" H 0   -150 50  0001 C CNN "part-number"
	1    3900 2200
	1    0    0    -1  
$EndComp
$EndSCHEMATC
