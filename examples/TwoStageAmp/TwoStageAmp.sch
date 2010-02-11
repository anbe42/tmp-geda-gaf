v 20070216 1
C 31900 49200 1 0 0 transistor.sym
{
T 32800 49700 5 10 1 1 0 0 1
refdes=Q1
T 32800 49900 5 10 1 1 0 0 1
model-name=2N3904
T 32800 49900 5 10 0 0 0 0 1
device=NPN_TRANSISTOR
}
C 28100 49600 1 0 0 resistor-1.sym
{
T 28300 49900 5 10 1 1 0 0 1
refdes=R5
T 28400 49400 5 10 1 1 0 0 1
value=10
T 28400 50000 5 10 0 0 0 0 1
device=RESISTOR
}
C 31100 49900 1 90 0 resistor-1.sym
{
T 31400 50700 5 10 1 1 180 0 1
refdes=R1
T 31200 50200 5 10 1 1 0 0 1
value=28K
T 31400 50300 5 10 0 0 0 0 1
device=RESISTOR
}
C 31600 48200 1 90 0 resistor-1.sym
{
T 31900 48900 5 10 1 1 180 0 1
refdes=R2
T 31600 48200 5 10 1 1 0 0 1
value=2K
T 31900 48600 5 10 0 0 0 0 1
device=RESISTOR
}
C 32600 47900 1 90 0 resistor-1.sym
{
T 33000 48600 5 10 1 1 180 0 1
refdes=RE1
T 32600 47900 5 10 1 1 0 0 1
value=100
T 32900 48300 5 10 0 0 0 0 1
device=RESISTOR
}
C 38000 54600 1 90 0 resistor-1.sym
{
T 38400 55300 5 10 1 1 180 0 1
refdes=RC2
T 38000 54600 5 10 1 1 0 0 1
value=1K
T 38300 55000 5 10 0 0 0 0 1
device=RESISTOR
}
C 40800 52200 1 90 0 resistor-1.sym
{
T 41100 53100 5 10 1 1 180 0 1
refdes=RL
T 40800 52200 5 10 1 1 0 0 1
value=100K
T 41100 52600 5 10 0 0 0 0 1
device=RESISTOR
}
N 32500 49200 32500 48800 4
C 39300 53900 1 0 0 capacitor-1.sym
{
T 39500 54400 5 10 1 1 0 0 1
refdes=Cout
T 39500 53700 5 10 1 1 0 0 1
value=2.2uF
T 39500 54600 5 10 0 0 0 0 1
device=CAPACITOR
T 39500 54800 5 10 0 0 0 0 1
symversion=0.1
}
C 33700 47900 1 90 0 capacitor-1.sym
{
T 34100 48600 5 10 1 1 180 0 1
refdes=CE1
T 33700 47900 5 10 1 1 0 0 1
value=1pF
T 33900 48600 5 10 0 0 0 0 1
device=CAPACITOR
T 33900 48800 5 10 0 0 0 0 1
symversion=0.1
}
N 33500 48800 33500 49100 4
N 39300 54100 37900 54100 4
{
T 38000 53800 5 10 1 1 0 0 1
netname=VColl2
}
N 40700 54100 40700 53100 4
C 31400 47400 1 0 0 gnd-1.sym
C 32400 47400 1 0 0 gnd-1.sym
C 33400 47400 1 0 0 gnd-1.sym
C 40600 51200 1 0 0 gnd-1.sym
C 27200 48300 1 0 0 vsin-1.sym
{
T 27900 48950 5 10 1 1 0 0 1
refdes=Vinput
T 26800 48150 5 10 1 1 0 0 1
value=DC 1.6V AC 10MV SIN(0 1MV 1KHZ)
T 27900 49150 5 10 0 0 0 0 1
device=vsin
T 27900 49350 5 10 0 0 0 0 1
footprint=none
}
C 40700 48700 1 0 0 vdc-1.sym
{
T 41400 49350 5 10 1 1 0 0 1
refdes=VCC
T 41400 49150 5 10 1 1 0 0 1
value=DC 15V
T 41400 49550 5 10 0 0 0 0 1
device=VOLTAGE_SOURCE
T 41400 49750 5 10 0 0 0 0 1
footprint=none
}
C 40800 50100 1 0 0 vcc-1.sym
C 37700 55700 1 0 0 vcc-1.sym
N 37900 55700 37900 55500 4
N 41000 50100 41000 49900 4
C 40900 48200 1 0 0 gnd-1.sym
C 27400 47600 1 0 0 gnd-1.sym
N 27500 48300 27500 47900 4
N 27500 49700 27500 49500 4
N 31500 48200 31500 47700 4
N 32500 47900 32500 47700 4
N 33500 47900 33500 47700 4
N 40700 52200 40700 51500 4
N 41000 48700 41000 48500 4
N 40200 54100 41300 54100 4
{
T 41500 54100 5 10 1 1 0 0 1
netname=Vout
}
C 26000 46000 0 0 0 title-B.sym
C 26500 55500 1 0 0 spice-model-1.sym
{
T 26600 56100 5 10 1 1 0 0 1
refdes=A1
T 27800 55800 5 10 1 1 0 0 1
model-name=2N3904
T 27000 55600 5 10 1 1 0 0 1
file=./models/2N3904.mod
T 26600 56200 5 10 0 1 0 0 1
device=model
}
C 26500 54600 1 0 0 spice-include-1.sym
{
T 26600 55000 5 10 1 1 0 0 1
refdes=A2
T 27000 54700 5 10 1 1 0 0 1
file=./Simulation.cmd
T 26600 54900 5 10 0 1 0 0 1
device=include
}
C 26500 53700 1 0 0 spice-directive-1.sym
{
T 26600 54100 5 10 1 1 0 0 1
refdes=A3
T 26600 53800 5 10 1 1 0 0 1
value=.options TEMP=25
T 26600 54000 5 10 0 1 0 0 1
device=directive
T 26600 53800 5 10 1 1 0 0 1
file=?
}
N 27000 49700 28100 49700 4
{
T 26700 49700 5 10 1 1 0 0 1
netname=Vin
}
N 31000 49900 31000 49700 4
N 31500 49100 31500 49700 4
C 29400 49500 1 0 0 capacitor-1.sym
{
T 29600 50000 5 10 1 1 0 0 1
refdes=C1
T 29500 49300 5 10 1 1 0 0 1
value=2.2uF
T 29600 50200 5 10 0 0 0 0 1
device=CAPACITOR
T 29600 50400 5 10 0 0 0 0 1
symversion=0.1
}
N 29000 49700 29400 49700 4
C 37300 52600 1 0 0 transistor.sym
{
T 38200 53100 5 10 1 1 0 0 1
refdes=Q2
T 38200 52700 5 10 1 1 0 0 1
model-name=2N3904
T 38200 53300 5 10 0 0 0 0 1
device=NPN_TRANSISTOR
}
C 37800 48900 1 0 0 gnd-1.sym
N 37900 53600 37900 54600 4
C 30800 51000 1 0 0 vcc-1.sym
N 31000 50800 31000 51000 4
T 36100 46800 9 20 1 0 0 0 1
Two stage amplifier SPICE playpen
T 40000 46100 9 10 1 0 0 0 1
Stuart Brorson -- sdb@cloud9.net
C 32600 53500 1 90 0 resistor-1.sym
{
T 32900 54400 5 10 1 1 180 0 1
refdes=RC1
T 32600 53500 5 10 1 1 0 0 1
value=3.3K
T 32900 53900 5 10 0 0 0 0 1
device=RESISTOR
}
C 38000 49500 1 90 0 resistor-1.sym
{
T 38500 50300 5 10 1 1 180 0 1
refdes=RE2
T 38000 49500 5 10 1 1 0 0 1
value=100
T 38300 49900 5 10 0 0 0 0 1
device=RESISTOR
}
N 37900 49200 37900 49500 4
N 37900 50400 37900 52600 4
N 32500 50200 32500 53500 4
C 32300 54800 1 0 0 vcc-1.sym
N 32500 54400 32500 54800 4
N 30300 49700 31900 49700 4
{
T 30700 49500 5 10 1 1 0 0 1
netname=Vbase1
}
C 39200 49500 1 90 0 capacitor-1.sym
{
T 39600 50200 5 10 1 1 180 0 1
refdes=CE2
T 39200 49500 5 10 1 1 0 0 1
value=1pF
T 39400 50200 5 10 0 0 0 0 1
device=CAPACITOR
T 39400 50400 5 10 0 0 0 0 1
symversion=0.1
}
C 38900 48900 1 0 0 gnd-1.sym
N 39000 49500 39000 49200 4
N 39000 50400 39000 51000 4
N 39000 51000 37900 51000 4
{
T 38000 51100 5 10 1 1 0 0 1
netname=Vem2
}
N 32500 49100 33500 49100 4
{
T 32700 49200 5 10 1 1 0 0 1
netname=Vem1
}
C 33300 53000 1 0 0 resistor-1.sym
{
T 33500 53300 5 10 1 1 0 0 1
refdes=R8
T 33500 52700 5 10 1 1 0 0 1
value=1
T 33600 53400 5 10 0 0 0 0 1
device=RESISTOR
}
N 35900 53100 37300 53100 4
{
T 36800 52900 5 10 1 1 0 0 1
netname=Vbase2
}
N 32500 53100 33300 53100 4
{
T 32600 52900 5 10 1 1 0 0 1
netname=Vcoll1
}
C 36700 54700 1 90 0 resistor-1.sym
{
T 37000 55500 5 10 1 1 180 0 1
refdes=R3
T 36800 55000 5 10 1 1 0 0 1
value=28K
T 37000 55100 5 10 0 0 0 0 1
device=RESISTOR
}
C 36400 51600 1 90 0 resistor-1.sym
{
T 36700 52300 5 10 1 1 180 0 1
refdes=R4
T 36400 51600 5 10 1 1 0 0 1
value=2.8K
T 36700 52000 5 10 0 0 0 0 1
device=RESISTOR
}
C 36200 50800 1 0 0 gnd-1.sym
N 36300 51600 36300 51100 4
N 36300 52500 36300 53100 4
C 36400 55800 1 0 0 vcc-1.sym
N 36600 55600 36600 55800 4
C 35000 52900 1 0 0 capacitor-1.sym
{
T 35200 53400 5 10 1 1 0 0 1
refdes=C2
T 35100 52700 5 10 1 1 0 0 1
value=2.2uF
T 35200 53600 5 10 0 0 0 0 1
device=CAPACITOR
T 35200 53800 5 10 0 0 0 0 1
symversion=0.1
}
N 35000 53100 34200 53100 4
N 36600 53100 36600 54700 4
