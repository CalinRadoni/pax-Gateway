EESchema Schematic File Version 4
LIBS:esp32-rfm-gateway-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
Title "ESP32 RFM69/RFM9x Gateway"
Date "2019-05-18"
Rev "38"
Comp "Calin Radoni"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	6500 4700 6150 4700
Wire Wire Line
	7350 5150 7350 5500
Wire Wire Line
	7350 4500 7450 4500
Wire Wire Line
	7350 4850 7350 4500
Connection ~ 7350 4500
Wire Wire Line
	7100 4500 7350 4500
Wire Wire Line
	6400 4600 6400 5500
Wire Wire Line
	6500 4600 6400 4600
Wire Wire Line
	5900 5000 5900 5100
Wire Wire Line
	6150 4700 6150 5000
Wire Wire Line
	6150 5000 6150 5100
Connection ~ 6150 5000
Wire Wire Line
	5900 5000 6150 5000
Wire Wire Line
	6150 5400 6150 5500
Wire Wire Line
	5900 5400 5900 5500
Connection ~ 5900 5000
Wire Wire Line
	5900 4900 5900 5000
Wire Wire Line
	5900 4500 5900 4600
Wire Wire Line
	5800 4500 5900 4500
$Comp
L power:GND #PWR?
U 1 1 5CC2CA30
P 7350 5500
AR Path="/5CC2CA30" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CA30" Ref="#PWR0104"  Part="1" 
F 0 "#PWR0104" H 7350 5250 50  0001 C CNN
F 1 "GND" H 7350 5350 50  0000 C CNN
F 2 "" H 7350 5500 50  0000 C CNN
F 3 "" H 7350 5500 50  0000 C CNN
	1    7350 5500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CC2CA36
P 6150 5500
AR Path="/5CC2CA36" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CA36" Ref="#PWR0105"  Part="1" 
F 0 "#PWR0105" H 6150 5250 50  0001 C CNN
F 1 "GND" H 6150 5350 50  0000 C CNN
F 2 "" H 6150 5500 50  0000 C CNN
F 3 "" H 6150 5500 50  0000 C CNN
	1    6150 5500
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR?
U 1 1 5CC2CA3C
P 7450 4500
AR Path="/5CC2CA3C" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CA3C" Ref="#PWR0106"  Part="1" 
F 0 "#PWR0106" H 7450 4350 50  0001 C CNN
F 1 "+BATT" H 7300 4650 50  0000 L CNN
F 2 "" H 7450 4500 50  0001 C CNN
F 3 "" H 7450 4500 50  0001 C CNN
	1    7450 4500
	0    1    1    0   
$EndComp
$Comp
L calin:C C?
U 1 1 5CC2CA42
P 6150 5250
AR Path="/5CC2CA42" Ref="C?"  Part="1" 
AR Path="/5CBFFED5/5CC2CA42" Ref="C25"  Part="1" 
F 0 "C25" V 6200 5350 50  0000 L CNN
F 1 "100pF" V 6200 4950 50  0000 L CNN
F 2 "CalinGeneric:C0805HS" H 6188 5100 50  0001 C CNN
F 3 "" H 6150 5250 50  0000 C CNN
F 4 "100pF / 50V / X7R" H 0   0   50  0001 C CNN "characteristics"
F 5 "Wurth Electronics" H 0   0   50  0001 C CNN "manufacturer"
F 6 "0805" H 0   0   50  0001 C CNN "package"
F 7 "885012207080" H 0   0   50  0001 C CNN "part-number"
	1    6150 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 4700 7100 4700
Wire Wire Line
	7200 4300 7200 4700
Wire Wire Line
	6400 4300 7200 4300
Wire Wire Line
	6400 4500 6400 4300
Wire Wire Line
	6500 4500 6400 4500
$Comp
L calin:TLV379IDBV U?
U 1 1 5CC2CA4E
P 6800 4600
AR Path="/5CC2CA4E" Ref="U?"  Part="1" 
AR Path="/5CBFFED5/5CC2CA4E" Ref="U24"  Part="1" 
F 0 "U24" H 6800 4800 50  0000 C CNN
F 1 "TLV379IDBV" H 6800 4400 50  0000 C CNN
F 2 "CalinGeneric:SOT-23-5-HS" H 6800 4600 50  0001 C CNN
F 3 "" H 6800 4600 50  0001 C CNN
F 4 "MicroPower 4 μA, Low Offset Voltage, Unity-Gain Stable, Rail-to-Rail I/O " H 0   0   50  0001 C CNN "characteristics"
F 5 "Texas Instruments" H 0   0   50  0001 C CNN "manufacturer"
F 6 "SOT23-5" H 0   0   50  0001 C CNN "package"
F 7 "TLV379IDBV" H 0   0   50  0001 C CNN "part-number"
	1    6800 4600
	1    0    0    -1  
$EndComp
Text Label 1700 2200 1    50   ~ 0
Earth
$Comp
L calin:HolePlated H?
U 1 1 5CC2CA57
P 1500 2300
AR Path="/5CC2CA57" Ref="H?"  Part="1" 
AR Path="/5CBFFED5/5CC2CA57" Ref="H5"  Part="1" 
F 0 "H5" H 1500 2400 60  0000 C CNN
F 1 "HolePlated" H 1500 2200 60  0001 C CNN
F 2 "CalinConnectors:SMD_Pins_Big_1x1" H 1500 2300 60  0001 C CNN
F 3 "" H 1500 2300 60  0000 C CNN
F 4 "DNP" H 0   0   50  0001 C CNN "Notes"
F 5 "pcb" H 0   0   50  0001 C CNN "Variant"
	1    1500 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9400 3200 9500 3200
Wire Wire Line
	9500 3100 9400 3100
$Comp
L power:+3V3 #PWR?
U 1 1 5CC2CA60
P 9500 3200
AR Path="/5CC2CA60" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CA60" Ref="#PWR0107"  Part="1" 
F 0 "#PWR0107" H 9500 3050 50  0001 C CNN
F 1 "+3V3" V 9500 3450 50  0000 C CNN
F 2 "" H 9500 3200 50  0000 C CNN
F 3 "" H 9500 3200 50  0000 C CNN
	1    9500 3200
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CC2CA66
P 9500 3100
AR Path="/5CC2CA66" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CA66" Ref="#PWR0108"  Part="1" 
F 0 "#PWR0108" H 9500 2850 50  0001 C CNN
F 1 "GND" V 9500 2850 50  0000 C CNN
F 2 "" H 9500 3100 50  0000 C CNN
F 3 "" H 9500 3100 50  0000 C CNN
	1    9500 3100
	0    -1   -1   0   
$EndComp
$Comp
L calin:CS_2s J?
U 1 1 5CC2CA6C
P 9250 3150
AR Path="/5CC2CA6C" Ref="J?"  Part="1" 
AR Path="/5CBFFED5/5CC2CA6C" Ref="J25"  Part="1" 
F 0 "J25" H 9250 3300 60  0000 C CNN
F 1 "ph_1x2" V 9350 3150 50  0000 C CNN
F 2 "CalinConnectors:Pin_Header_Angled_1x02" H 9250 3200 60  0001 C CNN
F 3 "" H 9250 3200 60  0000 C CNN
F 4 "test" H 0   0   50  0001 C CNN "Variant"
F 5 "DNP" H 0   0   50  0001 C CNN "Notes"
	1    9250 3150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8000 3200 8100 3200
Wire Wire Line
	8000 3000 8100 3000
$Comp
L power:+BATT #PWR?
U 1 1 5CC2CA75
P 8100 3000
AR Path="/5CC2CA75" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CA75" Ref="#PWR0109"  Part="1" 
F 0 "#PWR0109" H 8100 2850 50  0001 C CNN
F 1 "+BATT" H 7950 3150 50  0000 L CNN
F 2 "" H 8100 3000 50  0001 C CNN
F 3 "" H 8100 3000 50  0001 C CNN
	1    8100 3000
	0    1    1    0   
$EndComp
$Comp
L calin:CS_3 J?
U 1 1 5CC2CA7B
P 7850 3100
AR Path="/5CC2CA7B" Ref="J?"  Part="1" 
AR Path="/5CBFFED5/5CC2CA7B" Ref="J24"  Part="1" 
F 0 "J24" H 7850 3300 60  0000 C CNN
F 1 "ph_1x3" V 7950 3100 50  0000 C CNN
F 2 "CalinConnectors:Pin_Header_Angled_1x03" H 7850 3200 60  0001 C CNN
F 3 "" H 7850 3200 60  0000 C CNN
F 4 "test" H 0   0   50  0001 C CNN "Variant"
F 5 "DNP" H 0   0   50  0001 C CNN "Notes"
	1    7850 3100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8000 3100 8100 3100
$Comp
L power:GND #PWR?
U 1 1 5CC2CA83
P 8100 3100
AR Path="/5CC2CA83" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CA83" Ref="#PWR0110"  Part="1" 
F 0 "#PWR0110" H 8100 2850 50  0001 C CNN
F 1 "GND" V 8100 2850 50  0000 C CNN
F 2 "" H 8100 3100 50  0000 C CNN
F 3 "" H 8100 3100 50  0000 C CNN
	1    8100 3100
	0    -1   -1   0   
$EndComp
$Comp
L power:+5VP #PWR?
U 1 1 5CC2CA89
P 8100 3200
AR Path="/5CC2CA89" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CA89" Ref="#PWR0111"  Part="1" 
F 0 "#PWR0111" H 8100 3050 50  0001 C CNN
F 1 "+5VP" V 8100 3450 50  0000 C CNN
F 2 "" H 8100 3200 50  0000 C CNN
F 3 "" H 8100 3200 50  0000 C CNN
	1    8100 3200
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5CC2CA8F
P 1800 2300
AR Path="/5CC2CA8F" Ref="#FLG?"  Part="1" 
AR Path="/5CBFFED5/5CC2CA8F" Ref="#FLG0101"  Part="1" 
F 0 "#FLG0101" H 1800 2375 50  0001 C CNN
F 1 "PWR_FLAG" V 1750 2400 20  0000 C CNN
F 2 "" H 1800 2300 50  0001 C CNN
F 3 "~" H 1800 2300 50  0001 C CNN
	1    1800 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	8200 1300 8200 1400
Wire Wire Line
	3800 4450 3800 4500
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5CC2CA97
P 3800 4450
AR Path="/5CC2CA97" Ref="#FLG?"  Part="1" 
AR Path="/5CBFFED5/5CC2CA97" Ref="#FLG0102"  Part="1" 
F 0 "#FLG0102" H 3800 4525 50  0001 C CNN
F 1 "PWR_FLAG" V 3900 4500 31  0000 C CNN
F 2 "" H 3800 4450 50  0001 C CNN
F 3 "~" H 3800 4450 50  0001 C CNN
	1    3800 4450
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5CC2CA9D
P 8200 1300
AR Path="/5CC2CA9D" Ref="#FLG?"  Part="1" 
AR Path="/5CBFFED5/5CC2CA9D" Ref="#FLG0103"  Part="1" 
F 0 "#FLG0103" H 8200 1375 50  0001 C CNN
F 1 "PWR_FLAG" H 8200 1459 31  0000 C CNN
F 2 "" H 8200 1300 50  0001 C CNN
F 3 "~" H 8200 1300 50  0001 C CNN
	1    8200 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 1300 9600 1400
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5CC2CAA4
P 9600 1300
AR Path="/5CC2CAA4" Ref="#FLG?"  Part="1" 
AR Path="/5CBFFED5/5CC2CAA4" Ref="#FLG0104"  Part="1" 
F 0 "#FLG0104" H 9600 1375 50  0001 C CNN
F 1 "PWR_FLAG" H 9600 1459 31  0000 C CNN
F 2 "" H 9600 1300 50  0001 C CNN
F 3 "~" H 9600 1300 50  0001 C CNN
	1    9600 1300
	1    0    0    -1  
$EndComp
Text Label 3200 4200 0    50   ~ 0
ChargeStat
Wire Wire Line
	3100 4200 3650 4200
Text Label 6300 2400 0    50   ~ 0
ScaledVin
Wire Wire Line
	6100 2400 6100 2500
Wire Wire Line
	6100 2400 6700 2400
Wire Wire Line
	6100 2800 6100 2900
Connection ~ 6100 2400
Wire Wire Line
	6100 2300 6100 2400
$Comp
L calin:R R?
U 1 1 5CC2CAB2
P 6100 2650
AR Path="/5CC2CAB2" Ref="R?"  Part="1" 
AR Path="/5CBFFED5/5CC2CAB2" Ref="R26"  Part="1" 
F 0 "R26" V 6180 2650 40  0000 C CNN
F 1 "10k" V 6100 2650 40  0000 C CNN
F 2 "CalinGeneric:R0805HS" V 6030 2650 30  0001 C CNN
F 3 "" H 6100 2650 30  0000 C CNN
F 4 "10k" H 0   0   50  0001 C CNN "characteristics"
F 5 "Vishay" H 0   0   50  0001 C CNN "manufacturer"
F 6 "0805" H 0   0   50  0001 C CNN "package"
F 7 "CRCW080510K0FKEA" H 0   0   50  0001 C CNN "part-number"
	1    6100 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 1650 7300 1400
Wire Wire Line
	7400 1650 7300 1650
Wire Wire Line
	8300 1400 8200 1400
Wire Wire Line
	8100 1750 8000 1750
Wire Wire Line
	8100 1500 8100 1750
Wire Wire Line
	8300 1500 8100 1500
$Comp
L calin:Symbol_Generic SYM?
U 1 1 5CC2CAC2
P 1450 1300
AR Path="/5CC2CAC2" Ref="SYM?"  Part="1" 
AR Path="/5CBFFED5/5CC2CAC2" Ref="SYM4"  Part="1" 
F 0 "SYM4" H 1600 1300 50  0001 C CNN
F 1 "High Voltage !" H 1528 1300 50  0000 L CNN
F 2 "CalinGeneric:Symbol_HighVoltage_SilkS" H 1450 1300 50  0001 C CNN
F 3 "" V 1450 1300 50  0001 C CNN
F 4 "DNP" H 0   0   50  0001 C CNN "Notes"
F 5 "pcb" H 0   0   50  0001 C CNN "Variant"
F 6 "DNP" H 0   0   50  0001 C CNN "part-number"
	1    1450 1300
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR?
U 1 1 5CC2CAC9
P 1700 2400
AR Path="/5CC2CAC9" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CAC9" Ref="#PWR0112"  Part="1" 
F 0 "#PWR0112" H 1700 2150 50  0001 C CNN
F 1 "Earth" H 1700 2250 50  0001 C CNN
F 2 "" H 1700 2400 50  0001 C CNN
F 3 "~" H 1700 2400 50  0001 C CNN
	1    1700 2400
	1    0    0    -1  
$EndComp
Text Label 1850 1900 0    50   ~ 0
ACN
Text Label 1850 1700 0    50   ~ 0
ACL
Wire Wire Line
	1600 1700 2050 1700
$Comp
L calin:CS_3 J?
U 1 1 5CC2CAD7
P 1450 1800
AR Path="/5CC2CAD7" Ref="J?"  Part="1" 
AR Path="/5CBFFED5/5CC2CAD7" Ref="J20"  Part="1" 
F 0 "J20" V 1550 1800 60  0000 C CNN
F 1 "220V~" H 1450 1600 50  0000 C CNN
F 2 "CalinConnectors:THT_Pins_Big_1x3" H 1450 1900 60  0001 C CNN
F 3 "" H 1450 1900 60  0000 C CNN
F 4 "DNP" H 0   0   50  0001 C CNN "Notes"
F 5 "pcb" H 0   0   50  0001 C CNN "Variant"
	1    1450 1800
	-1   0    0    1   
$EndComp
$Comp
L calin:C C?
U 1 1 5CC2CADE
P 7350 5000
AR Path="/5CC2CADE" Ref="C?"  Part="1" 
AR Path="/5CBFFED5/5CC2CADE" Ref="C26"  Part="1" 
F 0 "C26" V 7400 5100 50  0000 L CNN
F 1 "100nF" V 7400 4700 50  0000 L CNN
F 2 "CalinGeneric:C0805HS" H 7388 4850 50  0001 C CNN
F 3 "" H 7350 5000 50  0000 C CNN
F 4 "100 nF / 50V / X7R" H 0   0   50  0001 C CNN "characteristics"
F 5 "Samsung" H 0   0   50  0001 C CNN "manufacturer"
F 6 "0805" H 0   0   50  0001 C CNN "package"
F 7 "CL21B104KBCNNNC" H 0   0   50  0001 C CNN "part-number"
	1    7350 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 4750 3500 4500
Wire Wire Line
	3500 5150 3500 5200
$Comp
L calin:CS_2 J?
U 1 1 5CC2CAE7
P 3500 4950
AR Path="/5CC2CAE7" Ref="J?"  Part="1" 
AR Path="/5CBFFED5/5CC2CAE7" Ref="J22"  Part="1" 
F 0 "J22" V 3600 5050 60  0000 L CNN
F 1 "s14500" V 3600 4700 50  0000 L CNN
F 2 "CalinConnectors:BattHolder-AA-PCB" H 3500 5000 60  0001 C CNN
F 3 "" H 3500 5000 60  0000 C CNN
F 4 "14500" H 0   0   50  0001 C CNN "Variant"
	1    3500 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 5150 3800 5200
Wire Wire Line
	3800 4500 3500 4500
Connection ~ 3800 4500
Wire Wire Line
	3800 4750 3800 4500
$Comp
L power:GND #PWR?
U 1 1 5CC2CAF2
P 3800 5200
AR Path="/5CC2CAF2" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CAF2" Ref="#PWR0113"  Part="1" 
F 0 "#PWR0113" H 3800 4950 50  0001 C CNN
F 1 "GND" H 3800 5050 50  0000 C CNN
F 2 "" H 3800 5200 50  0000 C CNN
F 3 "" H 3800 5200 50  0000 C CNN
	1    3800 5200
	1    0    0    -1  
$EndComp
$Comp
L calin:CS_2 J?
U 1 1 5CC2CAF8
P 3800 4950
AR Path="/5CC2CAF8" Ref="J?"  Part="1" 
AR Path="/5CBFFED5/5CC2CAF8" Ref="J23"  Part="1" 
F 0 "J23" V 3900 5050 60  0000 L CNN
F 1 "s18650" V 3900 4700 50  0000 L CNN
F 2 "CalinConnectors:KEYS-1043" H 3800 5000 60  0001 C CNN
F 3 "" H 3800 5000 60  0000 C CNN
F 4 "18650" H 0   0   50  0001 C CNN "Variant"
F 5 "Keystone" H 0   0   50  0001 C CNN "manufacturer"
F 6 "*" H 0   0   50  0001 C CNN "package"
F 7 "KEYS1043" H 0   0   50  0001 C CNN "part-number"
	1    3800 4950
	1    0    0    -1  
$EndComp
$Comp
L calin:Symbol_Generic SYM?
U 1 1 5CC2CAFF
P 1450 1100
AR Path="/5CC2CAFF" Ref="SYM?"  Part="1" 
AR Path="/5CBFFED5/5CC2CAFF" Ref="SYM3"  Part="1" 
F 0 "SYM3" H 1600 1100 50  0001 C CNN
F 1 "High Voltage !" H 1528 1100 50  0000 L CNN
F 2 "CalinGeneric:Symbol_HighVoltage_SilkS" H 1450 1100 50  0001 C CNN
F 3 "" V 1450 1100 50  0001 C CNN
F 4 "DNP" H 0   0   50  0001 C CNN "Notes"
F 5 "pcb" H 0   0   50  0001 C CNN "Variant"
F 6 "DNP" H 0   0   50  0001 C CNN "part-number"
	1    1450 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 2200 4000 2200
Wire Wire Line
	4000 2100 3900 2100
$Comp
L power:GND #PWR?
U 1 1 5CC2CB07
P 4000 2200
AR Path="/5CC2CB07" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB07" Ref="#PWR0114"  Part="1" 
F 0 "#PWR0114" H 4000 1950 50  0001 C CNN
F 1 "GND" V 4000 1950 50  0000 C CNN
F 2 "" H 4000 2200 50  0000 C CNN
F 3 "" H 4000 2200 50  0000 C CNN
	1    4000 2200
	0    -1   -1   0   
$EndComp
$Comp
L power:+5VP #PWR?
U 1 1 5CC2CB0D
P 4000 2100
AR Path="/5CC2CB0D" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB0D" Ref="#PWR0123"  Part="1" 
F 0 "#PWR0123" H 4000 1950 50  0001 C CNN
F 1 "+5VP" V 4000 2350 50  0000 C CNN
F 2 "" H 4000 2100 50  0000 C CNN
F 3 "" H 4000 2100 50  0000 C CNN
	1    4000 2100
	0    1    1    0   
$EndComp
$Comp
L calin:CS_2s J?
U 1 1 5CC2CB13
P 3750 2150
AR Path="/5CC2CB13" Ref="J?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB13" Ref="J21"  Part="1" 
F 0 "J21" H 3750 2300 60  0000 C CNN
F 1 "ph_1x2" V 3850 2150 50  0000 C CNN
F 2 "CalinConnectors:Pin_Header_Straight_1x02" H 3750 2200 60  0001 C CNN
F 3 "" H 3750 2200 60  0000 C CNN
F 4 "DNP" H 0   0   50  0001 C CNN "Notes"
F 5 "test" H 0   0   50  0001 C CNN "Variant"
	1    3750 2150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2950 1900 2850 1900
Wire Wire Line
	2950 1700 2850 1700
$Comp
L power:GND #PWR?
U 1 1 5CC2CB1C
P 2950 1700
AR Path="/5CC2CB1C" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB1C" Ref="#PWR0124"  Part="1" 
F 0 "#PWR0124" H 2950 1450 50  0001 C CNN
F 1 "GND" V 2950 1500 50  0000 C CNN
F 2 "" H 2950 1700 50  0000 C CNN
F 3 "" H 2950 1700 50  0000 C CNN
	1    2950 1700
	0    -1   -1   0   
$EndComp
$Comp
L power:+5VP #PWR?
U 1 1 5CC2CB22
P 2950 1900
AR Path="/5CC2CB22" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB22" Ref="#PWR0125"  Part="1" 
F 0 "#PWR0125" H 2950 1750 50  0001 C CNN
F 1 "+5VP" V 2950 2150 50  0000 C CNN
F 2 "" H 2950 1900 50  0000 C CNN
F 3 "" H 2950 1900 50  0000 C CNN
	1    2950 1900
	0    1    1    0   
$EndComp
$Comp
L calin:IRM-05 U?
U 1 1 5CC2CB28
P 2450 1800
AR Path="/5CC2CB28" Ref="U?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB28" Ref="U20"  Part="1" 
F 0 "U20" H 2450 2000 60  0000 C CNN
F 1 "IRM-10-5" H 2450 1600 60  0000 C CNN
F 2 "CalinGeneric:IRM222A" H 2450 1800 60  0001 C CNN
F 3 "" H 2450 1800 60  0001 C CNN
F 4 "10W AC-DC module-type power supply" H 0   0   50  0001 C CNN "characteristics"
F 5 "Mean Well" H 0   0   50  0001 C CNN "manufacturer"
F 6 "222A" H 0   0   50  0001 C CNN "package"
F 7 "IRM-10-5" H 0   0   50  0001 C CNN "part-number"
	1    2450 1800
	1    0    0    -1  
$EndComp
Text Label 9050 1400 1    50   ~ 0
PwrSW
Text Label 7600 1400 0    50   ~ 0
VinReg
Wire Wire Line
	7300 1850 7300 2000
Wire Wire Line
	7400 1850 7300 1850
$Comp
L power:GND #PWR?
U 1 1 5CC2CB33
P 7300 2000
AR Path="/5CC2CB33" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB33" Ref="#PWR0126"  Part="1" 
F 0 "#PWR0126" H 7300 1750 50  0001 C CNN
F 1 "GND" H 7300 1850 50  0000 C CNN
F 2 "" H 7300 2000 50  0000 C CNN
F 3 "" H 7300 2000 50  0000 C CNN
	1    7300 2000
	1    0    0    -1  
$EndComp
$Comp
L calin:BD49K U?
U 1 1 5CC2CB39
P 7700 1750
AR Path="/5CC2CB39" Ref="U?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB39" Ref="U22"  Part="1" 
F 0 "U22" H 7700 1950 50  0000 C CNN
F 1 "BD49K35" H 7700 1550 50  0000 C CNN
F 2 "CalinGeneric:SOT-23-HS" H 7700 1750 50  0001 C CNN
F 3 "" H 7700 1750 50  0001 C CNN
F 4 "Standard CMOS Voltage Detector IC 3.5V" H 0   0   50  0001 C CNN "characteristics"
F 5 "ROHM Semiconductor" H 0   0   50  0001 C CNN "manufacturer"
F 6 "SSOP3 (SOT23-3)" H 0   0   50  0001 C CNN "package"
F 7 "BD49K37G-TL" H 0   0   50  0001 C CNN "part-number"
	1    7700 1750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CC2CB40
P 5900 5500
AR Path="/5CC2CB40" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB40" Ref="#PWR0127"  Part="1" 
F 0 "#PWR0127" H 5900 5250 50  0001 C CNN
F 1 "GND" H 5900 5350 50  0000 C CNN
F 2 "" H 5900 5500 50  0000 C CNN
F 3 "" H 5900 5500 50  0000 C CNN
	1    5900 5500
	1    0    0    -1  
$EndComp
$Comp
L calin:R R?
U 1 1 5CC2CB46
P 5900 4750
AR Path="/5CC2CB46" Ref="R?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB46" Ref="R22"  Part="1" 
F 0 "R22" V 5980 4750 40  0000 C CNN
F 1 "2M" V 5900 4750 40  0000 C CNN
F 2 "CalinGeneric:R0805HS" V 5830 4750 30  0001 C CNN
F 3 "" H 5900 4750 30  0000 C CNN
F 4 "Mouser" H 0   0   50  0001 C CNN "Source"
F 5 "2M 1%" H 0   0   50  0001 C CNN "characteristics"
F 6 "Panasonic" H 0   0   50  0001 C CNN "manufacturer"
F 7 "0805" H 0   0   50  0001 C CNN "package"
F 8 "ERJ-6ENF2004V" H 0   0   50  0001 C CNN "part-number"
	1    5900 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CC2CB4D
P 6400 5500
AR Path="/5CC2CB4D" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB4D" Ref="#PWR0134"  Part="1" 
F 0 "#PWR0134" H 6400 5250 50  0001 C CNN
F 1 "GND" H 6400 5350 50  0000 C CNN
F 2 "" H 6400 5500 50  0000 C CNN
F 3 "" H 6400 5500 50  0000 C CNN
	1    6400 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 1950 9100 2000
Wire Wire Line
	9100 1600 9200 1600
Wire Wire Line
	9100 1650 9100 1600
Connection ~ 9100 1600
Wire Wire Line
	9000 1600 9100 1600
Wire Wire Line
	9600 1400 9800 1400
Connection ~ 9600 1400
Wire Wire Line
	9600 1600 9600 1400
Wire Wire Line
	9500 1600 9600 1600
Wire Wire Line
	9500 1400 9600 1400
Wire Wire Line
	9000 1400 9100 1400
$Comp
L power:GND #PWR?
U 1 1 5CC2CB5E
P 9100 2000
AR Path="/5CC2CB5E" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB5E" Ref="#PWR0135"  Part="1" 
F 0 "#PWR0135" H 9100 1750 50  0001 C CNN
F 1 "GND" H 9100 1850 50  0000 C CNN
F 2 "" H 9100 2000 50  0000 C CNN
F 3 "" H 9100 2000 50  0000 C CNN
	1    9100 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 1600 8200 2000
Wire Wire Line
	8300 1600 8200 1600
$Comp
L calin:TLV62569DBV U?
U 1 1 5CC2CB66
P 8650 1500
AR Path="/5CC2CB66" Ref="U?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB66" Ref="U23"  Part="1" 
F 0 "U23" H 8650 1700 60  0000 C CNN
F 1 "TLV62569DBV" H 8650 1300 60  0000 C CNN
F 2 "CalinGeneric:SOT-23-5-HS" H 8550 1600 60  0001 C CNN
F 3 "" H 8650 1700 60  0001 C CNN
F 4 "Step-Down Converter 2A 1.5MHz Iq=35uA" H 0   0   50  0001 C CNN "characteristics"
F 5 "Texas Instrumnets" H 0   0   50  0001 C CNN "manufacturer"
F 6 "SOT23-5" H 0   0   50  0001 C CNN "package"
F 7 "TLV62569DBV" H 0   0   50  0001 C CNN "part-number"
	1    8650 1500
	1    0    0    -1  
$EndComp
$Comp
L calin:R R?
U 1 1 5CC2CB6D
P 9100 1800
AR Path="/5CC2CB6D" Ref="R?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB6D" Ref="R28"  Part="1" 
F 0 "R28" V 9100 1800 40  0000 C CNN
F 1 "100k 1%" V 9000 1800 40  0000 C CNN
F 2 "CalinGeneric:R0805HS" V 9030 1800 30  0001 C CNN
F 3 "" H 9100 1800 30  0000 C CNN
F 4 "Mouser" H 0   0   50  0001 C CNN "Source"
F 5 "100k 1%" H 0   0   50  0001 C CNN "characteristics"
F 6 "Panasonic" H 0   0   50  0001 C CNN "manufacturer"
F 7 "0805" H 0   0   50  0001 C CNN "package"
F 8 "ERJ-6ENF1003V" H 0   0   50  0001 C CNN "part-number"
	1    9100 1800
	1    0    0    -1  
$EndComp
$Comp
L calin:R R?
U 1 1 5CC2CB74
P 9350 1600
AR Path="/5CC2CB74" Ref="R?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB74" Ref="R27"  Part="1" 
F 0 "R27" V 9350 1600 40  0000 C CNN
F 1 "442k 1%" V 9450 1600 40  0000 C CNN
F 2 "CalinGeneric:R0805HS" V 9280 1600 30  0001 C CNN
F 3 "" H 9350 1600 30  0000 C CNN
F 4 "Mouser" H 0   0   50  0001 C CNN "Source"
F 5 "442k 1%" H 0   0   50  0001 C CNN "characteristics"
F 6 "Panasonic" H 0   0   50  0001 C CNN "manufacturer"
F 7 "0805" H 0   0   50  0001 C CNN "package"
F 8 "ERJ-6ENF4423V" H 0   0   50  0001 C CNN "part-number"
	1    9350 1600
	0    1    1    0   
$EndComp
Wire Wire Line
	1450 5100 1450 5200
$Comp
L power:GND #PWR?
U 1 1 5CC2CB7C
P 1450 5200
AR Path="/5CC2CB7C" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB7C" Ref="#PWR0136"  Part="1" 
F 0 "#PWR0136" H 1450 4950 50  0001 C CNN
F 1 "GND" H 1450 5050 50  0000 C CNN
F 2 "" H 1450 5200 50  0000 C CNN
F 3 "" H 1450 5200 50  0000 C CNN
	1    1450 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 4500 1350 4500
Wire Wire Line
	1450 4800 1450 4500
Connection ~ 1450 4500
Wire Wire Line
	1800 4500 1450 4500
$Comp
L calin:C C?
U 1 1 5CC2CB86
P 1450 4950
AR Path="/5CC2CB86" Ref="C?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB86" Ref="C20"  Part="1" 
F 0 "C20" V 1500 5050 50  0000 L CNN
F 1 "10uF" V 1500 4700 50  0000 L CNN
F 2 "CalinGeneric:C0805HS" H 1488 4800 50  0001 C CNN
F 3 "" H 1450 4950 50  0000 C CNN
F 4 "10 µF / 6,3 V" H 0   0   50  0001 C CNN "characteristics"
F 5 "Samsung" H 0   0   50  0001 C CNN "manufacturer"
F 6 "0805" H 0   0   50  0001 C CNN "package"
F 7 "CL21B106KQQNNNE" H 0   0   50  0001 C CNN "part-number"
	1    1450 4950
	1    0    0    -1  
$EndComp
$Comp
L calin:LED D?
U 1 1 5CC2CB8D
P 1950 4200
AR Path="/5CC2CB8D" Ref="D?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB8D" Ref="D20"  Part="1" 
F 0 "D20" H 1950 4300 50  0000 C CNN
F 1 "LED-NC" H 2000 4100 39  0000 C CIN
F 2 "CalinGeneric:LED0805HS" H 1950 4200 50  0001 C CNN
F 3 "" H 1950 4200 50  0001 C CNN
F 4 "DNP" H 0   0   50  0001 C CNN "Notes"
F 5 "DNP" H 0   0   50  0001 C CNN "Variant"
F 6 "DNP" H 0   0   50  0001 C CNN "part-number"
	1    1950 4200
	-1   0    0    1   
$EndComp
Text Label 6950 4300 2    50   ~ 0
ScaledVBatt
$Comp
L power:+BATT #PWR?
U 1 1 5CC2CB95
P 5800 4500
AR Path="/5CC2CB95" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB95" Ref="#PWR0137"  Part="1" 
F 0 "#PWR0137" H 5800 4350 50  0001 C CNN
F 1 "+BATT" H 5650 4650 50  0000 L CNN
F 2 "" H 5800 4500 50  0001 C CNN
F 3 "" H 5800 4500 50  0001 C CNN
	1    5800 4500
	0    -1   -1   0   
$EndComp
$Comp
L calin:R R?
U 1 1 5CC2CB9B
P 5900 5250
AR Path="/5CC2CB9B" Ref="R?"  Part="1" 
AR Path="/5CBFFED5/5CC2CB9B" Ref="R23"  Part="1" 
F 0 "R23" V 5980 5250 40  0000 C CNN
F 1 "2M" V 5900 5250 40  0000 C CNN
F 2 "CalinGeneric:R0805HS" V 5830 5250 30  0001 C CNN
F 3 "" H 5900 5250 30  0000 C CNN
F 4 "Mouser" H 0   0   50  0001 C CNN "Source"
F 5 "2M 1%" H 0   0   50  0001 C CNN "characteristics"
F 6 "Panasonic" H 0   0   50  0001 C CNN "manufacturer"
F 7 "0805" H 0   0   50  0001 C CNN "package"
F 8 "ERJ-6ENF2004V" H 0   0   50  0001 C CNN "part-number"
	1    5900 5250
	1    0    0    -1  
$EndComp
Connection ~ 3500 4500
Wire Wire Line
	3500 4450 3500 4500
Wire Wire Line
	3000 4600 3000 5200
Wire Wire Line
	2900 4600 3000 4600
Wire Wire Line
	3100 4700 2900 4700
Wire Wire Line
	3100 4200 3100 4700
Connection ~ 3100 4200
Wire Wire Line
	2900 4200 3100 4200
Wire Wire Line
	2100 4200 2600 4200
Wire Wire Line
	3500 4500 3200 4500
Wire Wire Line
	3200 5100 3200 5200
Wire Wire Line
	1700 5100 1700 5200
Wire Wire Line
	1700 4700 1700 4800
Wire Wire Line
	1800 4700 1700 4700
Wire Wire Line
	1350 4200 1800 4200
$Comp
L power:+5VP #PWR?
U 1 1 5CC2CBB1
P 1350 4200
AR Path="/5CC2CBB1" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CBB1" Ref="#PWR0138"  Part="1" 
F 0 "#PWR0138" H 1350 4050 50  0001 C CNN
F 1 "+5VP" H 1350 4340 50  0000 C CNN
F 2 "" H 1350 4200 50  0000 C CNN
F 3 "" H 1350 4200 50  0000 C CNN
	1    1350 4200
	0    -1   -1   0   
$EndComp
$Comp
L calin:R R?
U 1 1 5CC2CBB7
P 2750 4200
AR Path="/5CC2CBB7" Ref="R?"  Part="1" 
AR Path="/5CBFFED5/5CC2CBB7" Ref="R21"  Part="1" 
F 0 "R21" V 2830 4200 40  0000 C CNN
F 1 "330-NC" V 2650 4200 39  0000 C CIN
F 2 "CalinGeneric:R0805HS" V 2680 4200 30  0001 C CNN
F 3 "" H 2750 4200 30  0000 C CNN
F 4 "330" H 0   0   50  0001 C CNN "characteristics"
F 5 "Vishay" H 0   0   50  0001 C CNN "manufacturer"
F 6 "0805" H 0   0   50  0001 C CNN "package"
F 7 "DNP" H 0   0   50  0001 C CNN "part-number"
F 8 "DNP" H 0   0   50  0001 C CNN "Notes"
F 9 "DNP" H 0   0   50  0001 C CNN "Variant"
	1    2750 4200
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CC2CBBE
P 3500 5200
AR Path="/5CC2CBBE" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CBBE" Ref="#PWR0140"  Part="1" 
F 0 "#PWR0140" H 3500 4950 50  0001 C CNN
F 1 "GND" H 3500 5050 50  0000 C CNN
F 2 "" H 3500 5200 50  0000 C CNN
F 3 "" H 3500 5200 50  0000 C CNN
	1    3500 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CC2CBC4
P 3200 5200
AR Path="/5CC2CBC4" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CBC4" Ref="#PWR0141"  Part="1" 
F 0 "#PWR0141" H 3200 4950 50  0001 C CNN
F 1 "GND" H 3200 5050 50  0000 C CNN
F 2 "" H 3200 5200 50  0000 C CNN
F 3 "" H 3200 5200 50  0000 C CNN
	1    3200 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CC2CBCA
P 3000 5200
AR Path="/5CC2CBCA" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CBCA" Ref="#PWR0144"  Part="1" 
F 0 "#PWR0144" H 3000 4950 50  0001 C CNN
F 1 "GND" H 3000 5050 50  0000 C CNN
F 2 "" H 3000 5200 50  0000 C CNN
F 3 "" H 3000 5200 50  0000 C CNN
	1    3000 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CC2CBD0
P 1700 5200
AR Path="/5CC2CBD0" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CBD0" Ref="#PWR0145"  Part="1" 
F 0 "#PWR0145" H 1700 4950 50  0001 C CNN
F 1 "GND" H 1700 5050 50  0000 C CNN
F 2 "" H 1700 5200 50  0000 C CNN
F 3 "" H 1700 5200 50  0000 C CNN
	1    1700 5200
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR?
U 1 1 5CC2CBD6
P 3500 4450
AR Path="/5CC2CBD6" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CBD6" Ref="#PWR0146"  Part="1" 
F 0 "#PWR0146" H 3500 4300 50  0001 C CNN
F 1 "+BATT" H 3350 4600 50  0000 L CNN
F 2 "" H 3500 4450 50  0001 C CNN
F 3 "" H 3500 4450 50  0001 C CNN
	1    3500 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 4500 3200 4800
Connection ~ 3200 4500
Wire Wire Line
	2900 4500 3200 4500
$Comp
L calin:C C?
U 1 1 5CC2CBDF
P 3200 4950
AR Path="/5CC2CBDF" Ref="C?"  Part="1" 
AR Path="/5CBFFED5/5CC2CBDF" Ref="C21"  Part="1" 
F 0 "C21" V 3250 5050 50  0000 L CNN
F 1 "10uF" V 3250 4700 50  0000 L CNN
F 2 "CalinGeneric:C0805HS" H 3238 4800 50  0001 C CNN
F 3 "" H 3200 4950 50  0000 C CNN
F 4 "10 µF / 6,3 V" H 0   0   50  0001 C CNN "characteristics"
F 5 "Samsung" H 0   0   50  0001 C CNN "manufacturer"
F 6 "0805" H 0   0   50  0001 C CNN "package"
F 7 "CL21B106KQQNNNE" H 0   0   50  0001 C CNN "part-number"
	1    3200 4950
	1    0    0    -1  
$EndComp
$Comp
L calin:R R?
U 1 1 5CC2CBE7
P 1700 4950
AR Path="/5CC2CBE7" Ref="R?"  Part="1" 
AR Path="/5CBFFED5/5CC2CBE7" Ref="R20"  Part="1" 
F 0 "R20" V 1780 4950 40  0000 C CNN
F 1 "2k2" V 1700 4950 40  0000 C CNN
F 2 "CalinGeneric:R0805HS" V 1630 4950 30  0001 C CNN
F 3 "" H 1700 4950 30  0000 C CNN
F 4 "2k2" H 0   0   50  0001 C CNN "characteristics"
F 5 "Panasonic" H 0   0   50  0001 C CNN "manufacturer"
F 6 "0805" H 0   0   50  0001 C CNN "package"
F 7 "ERJ-6ENF2201V" H 0   0   50  0001 C CNN "part-number"
	1    1700 4950
	1    0    0    -1  
$EndComp
$Comp
L power:+5VP #PWR?
U 1 1 5CC2CBEE
P 1350 4500
AR Path="/5CC2CBEE" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CBEE" Ref="#PWR0147"  Part="1" 
F 0 "#PWR0147" H 1350 4350 50  0001 C CNN
F 1 "+5VP" H 1350 4640 50  0000 C CNN
F 2 "" H 1350 4500 50  0000 C CNN
F 3 "" H 1350 4500 50  0000 C CNN
	1    1350 4500
	0    -1   -1   0   
$EndComp
$Comp
L calin:MCP73832 U?
U 1 1 5CC2CBF4
P 2350 4600
AR Path="/5CC2CBF4" Ref="U?"  Part="1" 
AR Path="/5CBFFED5/5CC2CBF4" Ref="U21"  Part="1" 
F 0 "U21" H 2350 4400 50  0000 C CNN
F 1 "MCP73832T-2ACI" H 2350 4800 50  0000 C CNN
F 2 "CalinGeneric:SOT-23-5-HS" H 2350 4600 60  0001 C CNN
F 3 "" H 2350 4600 60  0000 C CNN
F 4 "Single-Cell, Li-Ion, Li-Polymer Charge Management Controller, Tri-State Charge Status Output" H 0   0   50  0001 C CNN "characteristics"
F 5 "Microchip" H 0   0   50  0001 C CNN "manufacturer"
F 6 "SOT23-5" H 0   0   50  0001 C CNN "package"
F 7 "MCP73832T-2ACI" H 0   0   50  0001 C CNN "part-number"
	1    2350 4600
	-1   0    0    1   
$EndComp
Wire Wire Line
	6400 1400 6400 1500
Connection ~ 6400 1400
Wire Wire Line
	6300 1400 6400 1400
Wire Wire Line
	6400 1900 6100 1900
Wire Wire Line
	6400 1800 6400 1900
Wire Wire Line
	5800 1400 5900 1400
$Comp
L power:+BATT #PWR?
U 1 1 5CC2CC01
P 5800 1400
AR Path="/5CC2CC01" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CC01" Ref="#PWR0148"  Part="1" 
F 0 "#PWR0148" H 5800 1250 50  0001 C CNN
F 1 "+BATT" V 5800 1550 50  0000 L CNN
F 2 "" H 5800 1400 50  0001 C CNN
F 3 "" H 5800 1400 50  0001 C CNN
	1    5800 1400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6100 1750 6100 1900
Connection ~ 6100 1900
Wire Wire Line
	6100 2000 6100 1900
Wire Wire Line
	5800 1900 6100 1900
$Comp
L power:+5VP #PWR?
U 1 1 5CC2CC0B
P 5800 1900
AR Path="/5CC2CC0B" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CC0B" Ref="#PWR0149"  Part="1" 
F 0 "#PWR0149" H 5800 1750 50  0001 C CNN
F 1 "+5VP" V 5800 2150 50  0000 C CNN
F 2 "" H 5800 1900 50  0000 C CNN
F 3 "" H 5800 1900 50  0000 C CNN
	1    5800 1900
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CC2CC11
P 6100 2900
AR Path="/5CC2CC11" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CC11" Ref="#PWR0150"  Part="1" 
F 0 "#PWR0150" H 6100 2650 50  0001 C CNN
F 1 "GND" H 6100 2750 50  0000 C CNN
F 2 "" H 6100 2900 50  0000 C CNN
F 3 "" H 6100 2900 50  0000 C CNN
	1    6100 2900
	1    0    0    -1  
$EndComp
$Comp
L calin:R R?
U 1 1 5CC2CC17
P 6100 2150
AR Path="/5CC2CC17" Ref="R?"  Part="1" 
AR Path="/5CBFFED5/5CC2CC17" Ref="R25"  Part="1" 
F 0 "R25" V 6180 2150 40  0000 C CNN
F 1 "10k" V 6100 2150 40  0000 C CNN
F 2 "CalinGeneric:R0805HS" V 6030 2150 30  0001 C CNN
F 3 "" H 6100 2150 30  0000 C CNN
F 4 "10k" H 0   0   50  0001 C CNN "characteristics"
F 5 "Vishay" H 0   0   50  0001 C CNN "manufacturer"
F 6 "0805" H 0   0   50  0001 C CNN "package"
F 7 "CRCW080510K0FKEA" H 0   0   50  0001 C CNN "part-number"
	1    6100 2150
	1    0    0    -1  
$EndComp
$Comp
L calin:DiodeSchottky D?
U 1 1 5CC2CC1E
P 6400 1650
AR Path="/5CC2CC1E" Ref="D?"  Part="1" 
AR Path="/5CBFFED5/5CC2CC1E" Ref="D21"  Part="1" 
F 0 "D21" V 6500 1650 50  0000 R CNN
F 1 "B340AE-13" H 6100 1600 50  0000 C CNN
F 2 "CalinGeneric:SMA-HS" H 6400 1650 50  0001 C CNN
F 3 "" H 6400 1650 50  0000 C CNN
F 4 "3A schottky rectifier" H 0   0   50  0001 C CNN "characteristics"
F 5 "Diodes" H 0   0   50  0001 C CNN "manufacturer"
F 6 "SMA" H 0   0   50  0001 C CNN "package"
F 7 "B340AE-13" H 0   0   50  0001 C CNN "part-number"
	1    6400 1650
	0    -1   -1   0   
$EndComp
$Comp
L calin:IRLML2244 Q?
U 1 1 5CC2CC25
P 6100 1550
AR Path="/5CC2CC25" Ref="Q?"  Part="1" 
AR Path="/5CBFFED5/5CC2CC25" Ref="Q20"  Part="1" 
F 0 "Q20" V 5950 1450 50  0000 C CNN
F 1 "IRLML2244" V 6350 1550 50  0000 C CNN
F 2 "CalinGeneric:SOT-23-GSD-HS" H 6090 1550 60  0001 C CNN
F 3 "" H 6090 1550 60  0000 C CNN
F 4 "*" H 0   0   50  0001 C CNN "characteristics"
F 5 "International Rectifier" H 0   0   50  0001 C CNN "manufacturer"
F 6 "SOT23-3" H 0   0   50  0001 C CNN "package"
F 7 "IRLML2244TRPbF" H 0   0   50  0001 C CNN "part-number"
	1    6100 1550
	0    -1   -1   0   
$EndComp
$Comp
L calin:InductorFB L?
U 1 1 5CC2CC2C
P 9300 1400
AR Path="/5CC2CC2C" Ref="L?"  Part="1" 
AR Path="/5CBFFED5/5CC2CC2C" Ref="L21"  Part="1" 
F 0 "L21" H 9300 1300 50  0000 C CNN
F 1 "2.2uH" H 9300 1500 40  0000 C CNN
F 2 "CalinGeneric:ASPI-0530HI" H 9300 1400 60  0001 C CNN
F 3 "" H 9300 1400 60  0001 C CNN
F 4 "Abracon Corporation" H 0   0   50  0001 C CNN "manufacturer"
F 5 "ASPI-0530HI-2R2M-T2" H 0   0   50  0001 C CNN "part-number"
	1    9300 1400
	-1   0    0    1   
$EndComp
Wire Wire Line
	6400 1400 6700 1400
Connection ~ 6700 1400
Wire Wire Line
	6700 1500 6700 1400
Wire Wire Line
	6700 1800 6700 2000
$Comp
L power:GND #PWR?
U 1 1 5CC2CC37
P 6700 2000
AR Path="/5CC2CC37" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CC37" Ref="#PWR0151"  Part="1" 
F 0 "#PWR0151" H 6700 1750 50  0001 C CNN
F 1 "GND" H 6700 1850 50  0000 C CNN
F 2 "" H 6700 2000 50  0000 C CNN
F 3 "" H 6700 2000 50  0000 C CNN
	1    6700 2000
	1    0    0    -1  
$EndComp
$Comp
L calin:C C?
U 1 1 5CC2CC3D
P 6700 1650
AR Path="/5CC2CC3D" Ref="C?"  Part="1" 
AR Path="/5CBFFED5/5CC2CC3D" Ref="C22"  Part="1" 
F 0 "C22" H 6750 1750 50  0000 L CNN
F 1 "100nF" V 6750 1350 50  0000 L CNN
F 2 "CalinGeneric:C0805HS" H 6738 1500 50  0001 C CNN
F 3 "" H 6700 1650 50  0000 C CNN
F 4 "100 nF / 50V / X7R" H 0   0   50  0001 C CNN "characteristics"
F 5 "Samsung" H 0   0   50  0001 C CNN "manufacturer"
F 6 "0805" H 0   0   50  0001 C CNN "package"
F 7 "CL21B104KBCNNNC" H 0   0   50  0001 C CNN "part-number"
	1    6700 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 1900 9600 2000
Wire Wire Line
	7000 1800 7000 2000
Wire Wire Line
	7300 1400 7000 1400
Wire Wire Line
	6700 1400 7000 1400
Connection ~ 7000 1400
Wire Wire Line
	7000 1400 7000 1500
$Comp
L power:+3V3 #PWR?
U 1 1 5CC2CC4A
P 9800 1400
AR Path="/5CC2CC4A" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CC4A" Ref="#PWR0152"  Part="1" 
F 0 "#PWR0152" H 9800 1250 50  0001 C CNN
F 1 "+3V3" H 9800 1540 50  0000 C CNN
F 2 "" H 9800 1400 50  0000 C CNN
F 3 "" H 9800 1400 50  0000 C CNN
	1    9800 1400
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CC2CC50
P 9600 2000
AR Path="/5CC2CC50" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CC50" Ref="#PWR0153"  Part="1" 
F 0 "#PWR0153" H 9600 1750 50  0001 C CNN
F 1 "GND" H 9600 1850 50  0000 C CNN
F 2 "" H 9600 2000 50  0000 C CNN
F 3 "" H 9600 2000 50  0000 C CNN
	1    9600 2000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CC2CC56
P 7000 2000
AR Path="/5CC2CC56" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CC56" Ref="#PWR0154"  Part="1" 
F 0 "#PWR0154" H 7000 1750 50  0001 C CNN
F 1 "GND" H 7000 1850 50  0000 C CNN
F 2 "" H 7000 2000 50  0000 C CNN
F 3 "" H 7000 2000 50  0000 C CNN
	1    7000 2000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CC2CC5C
P 8200 2000
AR Path="/5CC2CC5C" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC2CC5C" Ref="#PWR0155"  Part="1" 
F 0 "#PWR0155" H 8200 1750 50  0001 C CNN
F 1 "GND" H 8200 1850 50  0000 C CNN
F 2 "" H 8200 2000 50  0000 C CNN
F 3 "" H 8200 2000 50  0000 C CNN
	1    8200 2000
	1    0    0    -1  
$EndComp
Connection ~ 9600 1600
$Comp
L calin:C C?
U 1 1 5CC2CC63
P 9600 1750
AR Path="/5CC2CC63" Ref="C?"  Part="1" 
AR Path="/5CBFFED5/5CC2CC63" Ref="C24"  Part="1" 
F 0 "C24" V 9650 1550 50  0000 L CNN
F 1 "22uF/6.3V/1mOhm" V 9750 1750 40  0000 C CNN
F 2 "CalinGeneric:C0805HS" H 9638 1600 50  0001 C CNN
F 3 "" H 9600 1750 50  0000 C CNN
F 4 "Taiyo Yuden" H 0   0   50  0001 C CNN "manufacturer"
F 5 "0805" H 0   0   50  0001 C CNN "package"
F 6 "JMK212BBJ226MGHT" H 0   0   50  0001 C CNN "part-number"
F 7 "22 µF / 6.3 V / X5R / ESR: 1 mΩ" H 0   0   50  0001 C CNN "characteristics"
	1    9600 1750
	1    0    0    -1  
$EndComp
$Comp
L calin:C C?
U 1 1 5CC2CC6A
P 7000 1650
AR Path="/5CC2CC6A" Ref="C?"  Part="1" 
AR Path="/5CBFFED5/5CC2CC6A" Ref="C23"  Part="1" 
F 0 "C23" V 7050 1450 50  0000 L CNN
F 1 "10uF/10V/1mOhm" V 7150 1550 40  0000 C CNN
F 2 "CalinGeneric:C0805HS" H 7038 1500 50  0001 C CNN
F 3 "" H 7000 1650 50  0000 C CNN
F 4 "Taiyo Yuden" H 0   0   50  0001 C CNN "manufacturer"
F 5 "0805" H 0   0   50  0001 C CNN "package"
F 6 "10 µF / 10 V / X5R / ESR: 1 mΩ" H 0   0   50  0001 C CNN "characteristics"
F 7 "EMK212BJ106KG-T" H 0   0   50  0001 C CNN "part-number"
	1    7000 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 1400 7300 1400
Connection ~ 8200 1400
Connection ~ 7300 1400
Wire Wire Line
	9650 4300 9000 4300
Wire Wire Line
	9650 4450 9000 4450
Wire Wire Line
	9650 4600 9000 4600
Text Label 9450 4450 2    50   ~ 0
ScaledVBatt
Text Label 9100 4300 0    50   ~ 0
ScaledVin
Text Label 9100 4600 0    50   ~ 0
ChargeStat
Text HLabel 9650 4300 2    50   UnSpc ~ 0
ScaledInputVoltage
Text HLabel 9650 4450 2    50   UnSpc ~ 0
ScaledBatteryVoltage
Text HLabel 9650 4600 2    50   UnSpc ~ 0
ChargeStatus
Wire Wire Line
	1600 2300 1700 2300
Wire Notes Line width 20 style dotted
	5000 3100 900  3100
Wire Notes Line width 20 style dotted
	5000 1000 5000 6550
Wire Notes Line width 20 style dotted
	5000 3900 10700 3900
Wire Notes Line width 20 style dotted
	8500 3900 8500 5800
Text Notes 7700 3500 0    50   Italic 0
J24 and J25 are placed for unplanned extensibility
Text Notes 3250 2450 0    50   Italic 0
J21 is placed for unplanned extensibility
Text Notes 1450 5750 0    50   Italic 0
R20 sets the charging current. The formula is:\n   I[mA] = 1000V / R[Kohms]\nExample: a 2K resistor sets the charging current to 500 mA.
Text Notes 3000 6200 0    50   Italic 0
J22 and J23 are placeholders for a 14500 size\nand a 18650 size battery sockets, respectively.\nOnly one of them can be mounted and used.
Text Notes 1050 2750 0    50   Italic 0
H5 is for a Earth connection, if ever needed,\nAND to make a connection for Earth plane in PCB
Wire Wire Line
	1600 1900 1700 1900
Wire Wire Line
	1700 1900 1700 2300
Wire Wire Line
	1600 1800 1800 1800
Wire Wire Line
	1800 1800 1800 1900
Wire Wire Line
	1800 1900 2050 1900
Wire Wire Line
	1800 2300 1700 2300
Connection ~ 1700 2300
Wire Wire Line
	1700 2400 1700 2300
$Comp
L calin:R R?
U 1 1 5CC2393E
P 3350 1200
AR Path="/5CC2393E" Ref="R?"  Part="1" 
AR Path="/5CBFFED5/5CC2393E" Ref="R29"  Part="1" 
F 0 "R29" V 3430 1200 40  0000 C CNN
F 1 "330" V 3350 1200 40  0000 C CNN
F 2 "CalinGeneric:R0805HS" V 3280 1200 30  0001 C CNN
F 3 "" H 3350 1200 30  0000 C CNN
F 4 "330" H 0   0   50  0001 C CNN "characteristics"
F 5 "Vishay" H 0   0   50  0001 C CNN "manufacturer"
F 6 "0805" H 0   0   50  0001 C CNN "package"
F 7 "CRCW0805330RFKTABC" H 0   0   50  0001 C CNN "part-number"
	1    3350 1200
	0    1    1    0   
$EndComp
$Comp
L calin:LED D?
U 1 1 5CC23A10
P 3750 1200
AR Path="/5CC23A10" Ref="D?"  Part="1" 
AR Path="/5CBFFED5/5CC23A10" Ref="D29"  Part="1" 
F 0 "D29" H 3750 1100 50  0000 C CNN
F 1 "LED Green" H 3750 1300 50  0000 C CNN
F 2 "CalinGeneric:LED0805HS" H 3750 1200 50  0001 C CNN
F 3 "" H 3750 1200 50  0001 C CNN
F 4 "test" H 0   0   50  0001 C CNN "Variant"
	1    3750 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CC23BE5
P 3100 1200
AR Path="/5CC23BE5" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC23BE5" Ref="#PWR0181"  Part="1" 
F 0 "#PWR0181" H 3100 950 50  0001 C CNN
F 1 "GND" V 3100 1000 50  0000 C CNN
F 2 "" H 3100 1200 50  0000 C CNN
F 3 "" H 3100 1200 50  0000 C CNN
	1    3100 1200
	0    1    1    0   
$EndComp
$Comp
L power:+5VP #PWR?
U 1 1 5CC23D54
P 4000 1200
AR Path="/5CC23D54" Ref="#PWR?"  Part="1" 
AR Path="/5CBFFED5/5CC23D54" Ref="#PWR0182"  Part="1" 
F 0 "#PWR0182" H 4000 1050 50  0001 C CNN
F 1 "+5VP" V 4000 1450 50  0000 C CNN
F 2 "" H 4000 1200 50  0000 C CNN
F 3 "" H 4000 1200 50  0000 C CNN
	1    4000 1200
	0    1    1    0   
$EndComp
Wire Wire Line
	4000 1200 3900 1200
Wire Wire Line
	3600 1200 3500 1200
Wire Wire Line
	3200 1200 3100 1200
Text Notes 3000 3850 0    50   Italic 10
Do NOT connect D20 and R21 if ChargeStat\nis connected to pins that\ndo not support 5V voltages !
$EndSCHEMATC
