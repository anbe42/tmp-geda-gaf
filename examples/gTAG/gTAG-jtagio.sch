v 20080110 1
C 40200 42900 0 0 0 title-A2.sym
C 45400 53600 1 0 0 in-1.sym
{
T 45400 53900 5 10 1 1 0 0 1
refdes=tdo_ttl
T 45400 53900 5 10 0 0 0 0 1
device=INPUT
}
C 45400 51800 1 0 0 in-1.sym
{
T 45400 52100 5 10 1 1 0 0 1
refdes=tms_ttl
T 45400 52100 5 10 0 0 0 0 1
device=INPUT
}
C 45400 50100 1 0 0 in-1.sym
{
T 45400 50400 5 10 1 1 0 0 1
refdes=tck_ttl
T 45400 50400 5 10 0 0 0 0 1
device=INPUT
}
C 45400 48400 1 0 0 in-1.sym
{
T 45400 48700 5 10 1 1 0 0 1
refdes=trst_ttl
T 45400 48700 5 10 0 0 0 0 1
device=INPUT
}
C 45400 56000 1 0 0 in-1.sym
{
T 45400 56300 5 10 1 1 0 0 1
refdes=jtag_power
T 45400 56300 5 10 0 0 0 0 1
device=INPUT
}
C 54200 54800 1 0 1 7414-1.sym
{
T 53400 55600 5 10 1 1 0 6 1
refdes=U20
T 53100 54800 5 10 1 1 0 6 1
slot=1
T 52800 54600 5 10 1 0 0 0 1
net=jtag_power:14
T 53000 54300 5 10 1 0 0 0 1
net=GND:7
T 53600 55600 5 10 0 1 0 0 1
footprint=SO14
T 54500 54800 5 10 1 1 0 0 1
device=7414
}
C 53000 53200 1 0 0 7414-1.sym
{
T 53800 54000 5 10 1 1 0 0 1
refdes=U20
T 53000 53200 5 10 1 1 0 0 1
slot=2
T 52800 52900 5 10 1 0 0 0 1
net=jtag_power:14
T 53000 52600 5 10 1 0 0 0 1
net=GND:7
T 53100 54000 5 10 0 1 0 0 1
footprint=so14
T 53300 53200 5 10 1 1 0 0 1
device=7414
}
C 53000 51400 1 0 0 7414-1.sym
{
T 53800 52200 5 10 1 1 0 0 1
refdes=U20
T 53000 51400 5 10 1 1 0 0 1
slot=3
T 52800 51100 5 10 1 0 0 0 1
net=jtag_power:14
T 53000 50800 5 10 1 0 0 0 1
net=GND:7
T 53200 52200 5 10 0 1 0 0 1
footprint=so14
T 53300 51400 5 10 1 1 0 0 1
device=7414
}
C 53000 49700 1 0 0 7414-1.sym
{
T 53800 50500 5 10 1 1 0 0 1
refdes=U20
T 53000 49700 5 10 1 1 0 0 1
slot=4
T 52800 49400 5 10 1 0 0 0 1
net=jtag_power:14
T 53000 49100 5 10 1 0 0 0 1
net=GND:7
T 53300 50500 5 10 0 1 0 0 1
footprint=so14
T 53300 49700 5 10 1 1 0 0 1
device=7414
}
C 53000 48000 1 0 0 7414-1.sym
{
T 53800 48800 5 10 1 1 0 0 1
refdes=U20
T 53000 48000 5 10 1 1 0 0 1
slot=5
T 52800 47800 5 10 1 0 0 0 1
net=jtag_power:14
T 53000 47500 5 10 1 0 0 0 1
net=GND:7
T 53200 48800 5 10 0 1 0 0 1
footprint=so14
T 53300 48000 5 10 1 1 0 0 1
device=7414
}
C 46000 55200 1 0 1 out-1.sym
{
T 46000 55500 5 10 1 1 0 6 1
refdes=tdi_ttl
T 46000 55500 5 10 0 0 0 0 1
device=OUTPUT
}
C 58600 50500 1 0 1 connector8-1.sym
{
T 58500 53100 5 10 1 1 0 6 1
refdes=CONN4
T 58700 53100 5 10 0 1 0 0 1
footprint=conn_jtag
T 58700 53700 5 10 0 0 0 0 1
device=CONNECTOR_8
}
N 54200 51900 56900 51900 4
N 54200 53700 55000 53700 4
N 55000 53700 55000 52200 4
N 55000 52200 56900 52200 4
N 54200 55300 55600 55300 4
N 55600 55300 55600 52500 4
N 55600 52500 56900 52500 4
N 56900 51600 55000 51600 4
N 55000 51600 55000 50200 4
N 55000 50200 54200 50200 4
N 56900 51300 55600 51300 4
N 55600 51300 55600 48500 4
N 55600 48500 54200 48500 4
C 56100 50200 1 0 0 gnd-1.sym
N 56900 51000 56200 51000 4
N 56200 51000 56200 50500 4
N 56900 52800 56200 52800 4
N 56200 52800 56200 56100 4
N 56200 56100 46000 56100 4
N 46000 55300 53000 55300 4
N 46000 53700 53000 53700 4
N 46000 51900 53000 51900 4
N 46000 50200 53000 50200 4
N 46000 48500 53000 48500 4
T 56500 50500 9 10 1 0 0 0 1
N.C
T 58000 43800 9 20 1 0 0 0 1
gTAG - JTAG IO 
T 56600 43300 9 10 1 0 0 0 1
gTAG-jtagio.sch
T 56600 43000 9 10 1 0 0 0 1
5
T 58000 43000 9 10 1 0 0 0 1
5
T 60400 43300 9 10 1 0 0 0 1
$Revision$
T 60400 43000 9 10 1 0 0 0 1
Stefan Petersen (spe@stacken.kth.se)
T 58900 52000 9 25 1 0 0 0 1
JTAG connector
C 40500 43100 1 0 0 copyleft.sym
{
T 42800 46300 5 10 0 0 0 0 1
device=none
}
C 59200 56300 1 90 0 capacitor-1.sym
{
T 58700 56500 5 10 1 1 90 0 1
refdes=C20
T 59400 56500 5 10 1 1 90 0 1
value=100n
T 58200 56200 5 10 0 1 0 0 1
footprint=sm1206
T 59400 57000 5 10 0 0 0 0 1
device=CAPACITOR
T 59400 57200 5 10 0 0 0 0 1
symversion=0.1
}
N 59000 57200 59000 57600 4
N 59000 55900 59000 56300 4
C 58900 55600 1 0 0 gnd-1.sym
T 57200 55200 9 15 1 0 0 0 1
Place near the VCC pin for U20
C 58800 57600 1 0 0 5V-plus-1.sym
{
T 59100 57600 5 10 1 1 0 0 1
net=jtag_power:1
}
C 47500 56700 1 90 0 resistor-2.sym
{
T 47200 56900 5 10 1 1 90 0 1
refdes=R20
T 47700 57000 5 10 1 1 90 0 1
value=10k
T 47400 56900 5 10 0 1 0 0 1
footprint=sm0805
T 47900 57050 5 10 0 0 0 0 1
device=RESISTOR
}
C 48800 56700 1 90 0 resistor-2.sym
{
T 48500 56900 5 10 1 1 90 0 1
refdes=R21
T 49000 57000 5 10 1 1 90 0 1
value=10k
T 48700 57100 5 10 0 1 0 0 1
footprint=sm0805
T 49200 57050 5 10 0 0 0 0 1
device=RESISTOR
}
C 50100 56700 1 90 0 resistor-2.sym
{
T 49800 56900 5 10 1 1 90 0 1
refdes=R22
T 50300 57000 5 10 1 1 90 0 1
value=10k
T 50100 57100 5 10 0 1 0 0 1
footprint=sm0805
T 50500 57050 5 10 0 0 0 0 1
device=RESISTOR
}
C 51500 56700 1 90 0 resistor-2.sym
{
T 51200 56900 5 10 1 1 90 0 1
refdes=R23
T 51700 57000 5 10 1 1 90 0 1
value=10k
T 51400 57200 5 10 0 1 0 0 1
footprint=sm0805
T 51900 57050 5 10 0 0 0 0 1
device=RESISTOR
}
N 47400 56700 47400 48500 4
N 48700 56700 48700 50200 4
N 50000 56700 50000 51900 4
N 51400 56700 51400 53700 4
C 47200 57800 1 0 0 5V-plus-1.sym
{
T 47500 57800 5 10 1 1 0 0 1
net=jtag_power:1
}
C 48500 57800 1 0 0 5V-plus-1.sym
{
T 48800 57800 5 10 1 1 0 0 1
net=jtag_power:1
}
C 49800 57800 1 0 0 5V-plus-1.sym
{
T 50100 57800 5 10 1 1 0 0 1
net=jtag_power:1
}
C 51200 57800 1 0 0 5V-plus-1.sym
{
T 51500 57800 5 10 1 1 0 0 1
net=jtag_power:1
}
N 47400 57800 47400 57600 4
N 48700 57800 48700 57600 4
N 50000 57800 50000 57600 4
N 51400 57800 51400 57600 4
