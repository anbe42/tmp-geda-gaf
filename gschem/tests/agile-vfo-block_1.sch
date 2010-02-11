v 20031019 1
T 26500 6400 9 10 1 0 0 0 1
Roger Williams
T 23400 6400 9 10 1 0 0 0 1
v0.1, 1 Nov 1998
T 22400 7400 9 20 1 0 0 0 1
Agile 0.1-110 MHz VFO
T 22400 7000 9 20 1 0 0 0 1
FHSS Development Platform
C 10500 18900 1 0 0 dac.sym
{
T 10600 18700 5 10 1 1 0 0 1
value=15..25 MHz
}
C 11700 18900 1 0 0 lowpass.sym
C 13300 18700 1 0 0 mixer-ansi.sym
{
T 13600 19800 5 10 1 1 0 0 1
value=AD831
}
C 11300 17200 1 0 0 lowpass.sym
C 10100 17000 1 0 0 phase-detector.sym
C 12900 16000 1 0 1 divide-by-N.sym
{
T 12025 15800 5 10 1 1 0 0 1
value=N=160
}
C 12500 17200 1 0 0 EMBEDDEDosc-var2.sym
[
B 12702 17199 800 800 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
P 13500 17600 13700 17600 1 0 -1
A 13020 17559 90 27 125 3 0 0 0 -1 -1
A 13180 17641 90 207 125 3 0 0 0 -1 -1
V 13100 17600 250 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
L 13400 17900 13300 17860 3 0 0 0 -1 -1
L 13400 17900 13360 17800 3 0 0 0 -1 -1
L 13360 17800 13300 17860 3 0 0 0 -1 -1
L 12800 17300 13330 17830 3 0 0 0 -1 -1
P 12700 17600 12500 17600 1 0 -1
]
{
T 12700 17000 5 10 1 1 0 0 1
value=160 MHz
}
N 10700 17000 10700 16400 4
T 9400 19800 9 10 1 0 0 0 1
AD9851 DDS
T 9000 15800 9 10 1 0 0 0 1
160 MHz Synthesiser
C 14700 18900 1 0 0 bandpass.sym
{
T 15050 19800 5 10 1 1 0 0 1
name=SAW
T 14750 18700 5 10 1 1 0 0 1
value=135..145 MHz
}
C 16100 18900 1 0 0 amp.sym
{
T 16400 18700 5 10 1 1 0 0 1
value=+12 dB
}
C 17500 18700 1 0 0 mixer-ansi.sym
{
T 17800 19800 5 10 1 1 0 0 1
value=AD831
}
C 5800 6100 0 0 0 EMBEDDEDtitle-C.sym
[
B 5900 6200 22000 17000 15 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
{
T 20300 7700 5 10 0 0 0 0 1
graphical=1
}
T 22000 6300 15 8 1 0 0 0 1
REVISION:
T 25000 6300 15 8 1 0 0 0 1
DRAWN BY: 
T 22000 8750 15 20 1 0 0 0 1
Coelacanth Engineering Inc
T 22000 8500 15 10 1 0 0 0 1
69 Highland Street, Middleborough, MA 02346, USA
T 22000 8300 15 10 1 0 0 0 1
tel +1 508 947-5585    http://www.coelacanth.com/
L 21900 6200 21900 9100 15 0 0 0 -1 -1
L 24900 6700 24900 6200 15 0 0 0 -1 -1
L 21900 9100 27900 9100 15 0 0 0 -1 -1
L 21900 8100 27900 8100 15 0 0 0 -1 -1
L 21900 8200 27900 8200 15 0 0 0 -1 -1
L 21900 6700 27900 6700 15 0 0 0 -1 -1
]
C 15500 14300 1 0 0 lowpass.sym
C 14300 14100 1 0 0 phase-detector.sym
C 17100 13100 1 0 1 divide-by-N.sym
{
T 16025 12900 5 10 1 1 0 0 1
value=N=145..245
}
C 16700 14300 1 0 0 EMBEDDEDosc-var2.sym
[
B 16902 14299 800 800 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
P 17700 14700 17900 14700 1 0 -1
A 17220 14659 90 27 125 3 0 0 0 -1 -1
A 17380 14741 90 207 125 3 0 0 0 -1 -1
V 17300 14700 250 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
L 17600 15000 17500 14960 3 0 0 0 -1 -1
L 17600 15000 17560 14900 3 0 0 0 -1 -1
L 17560 14900 17500 14960 3 0 0 0 -1 -1
L 17000 14400 17530 14930 3 0 0 0 -1 -1
P 16900 14700 16700 14700 1 0 -1
]
{
T 16700 14100 5 10 1 1 0 0 1
value=145..245 MHz
}
N 14900 14100 14900 13500 4
N 18100 13500 18100 14700 4
N 18100 14700 17900 14700 4
T 13200 12900 9 10 1 0 0 0 1
145..245 MHz Synthesiser
N 13900 16400 13900 17600 4
N 13900 17600 13700 17600 4
N 13900 18700 13900 17600 4
B 8900 15700 5200 2500 6 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
N 8500 17600 8500 19300 4
N 8500 14700 8500 17600 4
N 14900 13500 15900 13500 4
N 18100 13500 17100 13500 4
B 13100 12800 5200 2500 6 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
N 11700 16400 10700 16400 4
N 12900 16400 13900 16400 4
N 14500 19300 14700 19300 4
N 15900 19300 16100 19300 4
C 18900 18900 1 0 0 lowpass.sym
{
T 19150 18700 5 10 1 1 0 0 1
value=110 MHz
}
C 20300 18900 1 0 0 amp.sym
{
T 20550 18700 5 10 1 1 0 0 1
value=+27 dB
}
C 21900 19700 1 0 0 atten-var.sym
{
T 22050 19500 5 10 1 1 0 0 1
value=-3..-23 dB
}
N 18100 14700 18100 18700 4
N 17300 19300 17500 19300 4
N 18700 19300 18900 19300 4
N 20100 19300 20300 19300 4
C 24700 19700 1 0 0 amp.sym
{
T 25000 19500 5 10 1 1 0 0 1
value=+13 dB
}
C 23300 19700 1 0 0 spst.sym
N 23100 20100 23300 20100 4
N 24500 20100 24700 20100 4
C 23300 18100 1 0 0 spst.sym
N 23100 18500 23300 18500 4
N 24500 18500 24700 18500 4
C 26400 20000 1 0 1 con-coaxial.sym
N 26100 20100 25900 20100 4
C 26400 18400 1 0 1 con-coaxial.sym
N 26100 18500 25900 18500 4
N 12900 19300 13300 19300 4
N 21700 19300 21500 19300 4
N 21700 19300 21700 20100 4
N 21700 20100 21900 20100 4
N 21700 19300 21700 18500 4
N 21700 18500 21900 18500 4
C 13900 21200 1 0 0 amp.sym
N 13700 21600 13900 21600 4
C 15600 21500 1 0 1 con-coaxial.sym
N 15300 21600 15100 21600 4
T 15700 21550 9 10 1 0 0 0 1
Reference
T 15700 21350 9 10 1 0 0 0 1
Output
T 15700 21750 9 10 1 0 0 0 1
30 MHz
T 26500 20050 9 10 1 0 0 0 1
0.1..110 MHz
T 26500 20250 9 10 1 0 0 0 1
Output 1
T 26500 18450 9 10 1 0 0 0 1
0.1..110 MHz
T 26500 18650 9 10 1 0 0 0 1
Output 2
T 26500 19850 9 10 1 0 0 0 1
0..+20 dBm
T 26500 18250 9 10 1 0 0 0 1
0..+20 dBm
C 9900 21000 1 0 0 phase-detector.sym
{
T 10050 22100 5 10 1 1 0 0 1
value=Harmonic
}
C 11100 21200 1 0 0 lowpass.sym
{
T 11500 21000 5 10 1 1 0 0 1
value=1 Hz
}
C 12300 21200 1 0 0 EMBEDDEDosc-xtal2.sym
[
B 12502 21199 800 800 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
P 13300 21600 13500 21600 1 0 -1
A 12820 21659 90 27 125 3 0 0 0 -1 -1
A 12980 21741 90 207 125 3 0 0 0 -1 -1
V 12900 21700 200 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
B 12800 21320 200 60 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
L 12840 21400 12960 21400 3 0 0 0 -1 -1
L 12840 21300 12960 21300 3 0 0 0 -1 -1
P 12500 21600 12300 21600 1 0 -1
]
{
T 12550 22100 5 10 1 1 0 0 1
name=VTCXO
T 12550 21000 5 10 1 1 0 0 1
value=30 MHz
}
N 10500 20800 13700 20800 4
N 13700 20800 13700 21600 4
N 13700 21600 13500 21600 4
C 8700 21200 1 0 0 square-up.sym
N 8500 21600 8700 21600 4
C 8200 21500 1 0 0 con-coaxial.sym
T 7160 21550 9 10 1 0 0 0 1
Reference
T 7670 21350 9 10 1 0 0 0 1
Input
T 7225 21750 9 10 1 0 0 0 1
1..30 MHz
N 10500 21000 10500 20800 4
N 10500 20800 8500 20800 4
N 13100 14700 8500 14700 4
{
T 9000 14800 5 10 1 1 0 0 1
netname=30 MHz fref
}
N 8900 17600 8500 17600 4
C 21900 18100 1 0 0 atten-var.sym
{
T 22050 17900 5 10 1 1 0 0 1
value=-3..-23 dB
}
C 24700 18100 1 0 0 amp.sym
{
T 25000 17900 5 10 1 1 0 0 1
value=+13 dB
}
C 8900 17200 1 0 0 EMBEDDEDdivide-by-30.sym
[
B 9100 17200 800 800 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
P 9100 17600 8900 17600 1 0 -1
P 9900 17600 10100 17600 1 0 -1
L 9100 17200 9900 18000 3 0 0 0 -1 -1
T 9650 17350 9 10 1 0 0 0 1
1
T 9250 17700 9 10 1 0 0 0 1
30
]
C 13100 14300 1 0 0 EMBEDDEDdivide-by-30.sym
[
B 13300 14300 800 800 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
P 13300 14700 13100 14700 1 0 -1
P 14100 14700 14300 14700 1 0 -1
L 13300 14300 14100 15100 3 0 0 0 -1 -1
T 13850 14450 9 10 1 0 0 0 1
1
T 13450 14800 9 10 1 0 0 0 1
30
]
C 10600 9500 1 0 0 EMBEDDEDselector-switch-16.sym
[
V 10400 9900 30 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
V 10100 9600 30 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
V 10010 10060 30 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
V 10010 9740 30 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
V 10100 10200 30 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
L 10120 10180 10220 10140 3 0 0 0 -1 -1
L 10120 10180 10160 10080 3 0 0 0 -1 -1
L 10160 10080 10220 10140 3 0 0 0 -1 -1
L 10190 10110 10380 9920 3 0 0 0 -1 -1
P 10600 9900 10430 9900 1 0 -1
T 9930 9840 9 10 1 0 0 0 1
16
]
C 8400 11300 1 0 0 EMBEDDEDcon-rect.sym
[
B 8400 11300 200 400 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
P 8600 11500 8800 11500 1 0 -1
]
C 9200 11100 1 0 0 amp-bidir.sym
C 8900 11100 1 270 0 spst-noblock.sym
C 8900 9500 1 0 0 termination.sym
N 8800 11500 9000 11500 4
N 9000 11500 9200 11500 4
T 7570 11550 9 10 1 0 0 0 1
RS-485
T 7515 11350 9 10 1 0 0 0 1
Interface
N 9000 11100 9000 11500 4
T 9800 10400 9 10 1 0 0 0 1
Address
T 8070 10400 9 10 1 0 0 0 1
RS-485
T 7710 10200 9 10 1 0 0 0 1
Termination
C 10600 9500 1 0 0 EMBEDDEDblock-1x3-2-3.sym
[
P 10800 11500 10600 11500 1 0 -1
P 11600 9900 11800 9900 1 0 -1
B 10800 9500 800 2400 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
P 11600 10700 11800 10700 1 0 -1
P 11600 11500 11800 11500 1 0 -1
P 10800 9900 10600 9900 1 0 -1
]
{
T 10950 12000 5 10 1 1 0 0 1
device=EPLD
}
N 10400 11500 10600 11500 4
C 12000 11100 1 0 0 EMBEDDEDblock-in.sym
[
B 12200 11100 800 800 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
P 12200 11500 12000 11500 1 0 -1
]
{
T 12200 12000 5 10 1 1 0 0 1
device=EEPROM
}
C 12000 9500 1 0 0 EMBEDDEDblock-in.sym
[
B 12200 9500 800 800 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
P 12200 9900 12000 9900 1 0 -1
]
{
T 12400 10400 5 10 1 1 0 0 1
device=RTC
}
N 11800 11500 12000 11500 4
N 11800 9900 12000 9900 4
C 9000 7600 1 0 0 lowpass.sym
C 10600 7600 1 0 0 spst.sym
C 12000 7600 1 0 0 dc-dc.sym
N 12000 8000 11800 8000 4
N 10200 8000 10400 8000 4
N 10400 8000 10400 8700 4
N 10400 8700 11200 8700 4
{
T 10400 8800 5 10 1 1 0 0 1
netname=Vstby
}
N 10400 8000 10600 8000 4
N 13200 8000 14000 8000 4
{
T 13200 8100 5 10 1 1 0 0 1
netname=+9V
}
C 8400 7800 1 0 0 EMBEDDEDcon-rect.sym
[
B 8400 7800 200 400 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
P 8600 8000 8800 8000 1 0 -1
]
T 7310 7950 9 10 1 0 0 0 1
+10..18 Vdc
N 8800 8000 9000 8000 4
N 8500 20800 8500 19300 4
C 9300 18900 1 0 0 EMBEDDEDmultiply-by-6.sym
[
B 9500 18900 800 800 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
P 9500 19300 9300 19300 1 0 -1
P 10300 19300 10500 19300 1 0 -1
L 9500 18900 10300 19700 3 0 0 0 -1 -1
T 10050 19050 9 10 1 0 0 0 1
6
T 9700 19400 9 10 1 0 0 0 1
1
]
{
T 9500 18700 5 10 1 1 0 0 1
value=180 MHz
}
B 9300 18600 3600 1400 6 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
N 9300 19300 8500 19300 4
T 22400 12100 9 10 1 0 0 0 1
SSB phase noise < -120 dBc/Hz @ 10 kHz
T 22400 11200 9 10 1 0 0 0 1
Reference stability < 0.1 ppm
T 22400 12400 9 10 1 0 0 0 1
Offset synthesiser switching time < 1 ms
T 22400 12700 9 10 1 0 0 0 1
DDS chip rate > 30 kHz (10 MHz range)
T 22400 13000 9 10 1 0 0 0 1
Output level flatness < 1 dB (10 MHz range)
T 22300 14200 9 10 1 0 0 0 1
Selected Target Specifications
T 22400 10600 9 10 1 0 0 0 1
Active current drain < 500 mA
T 22400 10300 9 10 1 0 0 0 1
Standby current drain < 50 mA
T 22400 10000 9 10 1 0 0 0 1
Construction: 4-layer SMD board w/removable shields
T 22400 13900 9 10 1 0 0 0 1
Complete FHSS synthesiser for any HF transceiver
T 22400 13600 9 10 1 0 0 0 1
Individual TX and RX local oscillator outputs
T 22400 10900 9 10 1 0 0 0 1
Real-time clock resolution = 1 ms
T 22400 13300 9 10 1 0 0 0 1
Frequency resolution << 1 Hz
T 22400 11800 9 10 1 0 0 0 1
Spurious outputs < -70 dBc
T 22400 11500 9 10 1 0 0 0 1
Harmonics < -40 dBc
N 11800 10700 12600 10700 4
{
T 11800 10800 5 10 1 1 0 0 1
netname=Control
}
T 22400 9700 9 10 1 0 0 0 1
Prototype release date: January 1999
B 22300 9600 5400 4500 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
