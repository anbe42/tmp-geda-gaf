v 20021103
C 59400 73800 1 0 0 resistor.sym
{
T 60100 74700 5 7 0 0 0 0
refdes=RES_base
T 60200 74400 5 5 0 0 0 0
r=RB
}
C 64700 73800 1 90 0 resistor.sym
{
T 63800 74500 5 7 0 0 90 0
refdes=RES_collector
T 64100 74600 5 5 0 0 90 0
r=RC
}
C 64700 70600 1 90 0 resistor.sym
{
T 63800 71300 5 7 0 0 90 0
refdes=RES_emitter
T 64100 71400 5 5 0 0 90 0
r=RE
}
C 65500 72300 1 90 0 capacitor.sym
{
T 64700 72900 5 4 0 0 90 0
refdes=CAP3
T 64800 72800 5 2 0 0 90 0
c=CCS
T 64800 73100 5 2 0 0 90 0
v_init=?0.0
}
C 65300 72400 1 0 0 gnd_node.sym
{
T 65000 72200 5 5 0 0 0 0
value=?0
T 65500 72200 5 10 0 1 0 0
refdes=GND1
}
N 59400 73900 59800 73900 4
N 64600 75100 64600 75200 4
N 65300 72700 65300 72600 4
N 64600 71000 64600 70800 4
C 64900 75000 1 90 0 port.sym
{
T 64800 75700 5 8 1 1 180 0
refdes=collector
}
C 59600 74200 1 180 0 port.sym
{
T 59400 73800 5 8 1 1 180 0
refdes=base
}
C 64300 71000 1 270 0 port.sym
{
T 64800 70600 5 8 1 1 0 0
refdes=emitter
}
T 59400 75500 8 10 1 0 0 0
entity=BJT_transistor_simple_top
T 59400 75300 8 10 1 0 0 0
architecture=simple_arc
N 64600 73300 64600 74200 4
C 62800 73700 1 0 0 capacitor.sym
{
T 63400 74500 5 4 0 0 0 0
refdes=CAP1
T 63300 74400 5 2 0 0 0 0
c=?10e-12
T 63600 74400 5 2 0 0 0 0
v_init=?0.0
}
C 61600 72100 1 90 0 capacitor.sym
{
T 60800 72700 5 4 0 0 90 0
refdes=CAP2
T 60900 72600 5 2 0 0 90 0
c=?10e-12
T 60900 72900 5 2 0 0 90 0
v_init=?0.0
}
N 64600 71900 64600 72700 4
N 64600 72700 64500 72700 4
N 64600 73300 64500 73300 4
N 61400 72500 61400 72300 4
N 61400 72300 62200 72300 4
N 62200 72300 62200 72500 4
N 64100 73900 64600 73900 4
N 64600 73900 65300 73900 4
N 65300 73600 65300 73900 4
N 63200 73900 60700 73900 4
N 63000 73300 62900 73300 4
N 62200 72300 64600 72300 4
N 61400 73400 61400 73900 4
C 63000 72600 1 0 0 spice-cs.sym
{
T 63400 73900 5 7 0 0 0 0
refdes=CS2
T 62700 73600 5 4 0 0 0 0
ISS=ISS
T 63400 73600 5 4 0 0 0 0
VT=VT
T 64200 73600 5 4 0 0 0 0
N=BF
T 63200 73800 5 4 0 0 0 0
architecture=current_controlled
}
C 62000 73800 1 270 0 sp_diode.sym
{
T 63200 73100 5 4 0 0 270 0
refdes=SP1
T 63100 72900 5 3 0 0 270 0
source=sp_diode.sch
T 62900 72730 5 3 0 0 270 0
ISS=ISS
T 62900 73330 5 3 0 0 270 0
N=?1.0
T 62800 73330 5 3 0 0 270 0
CJ0=CJE
T 62900 73030 5 3 0 0 270 0
TT=TF
T 62970 72330 5 3 0 0 270 0
PB=PE
T 62840 72330 5 3 0 0 270 1
M=ME
T 62900 72330 5 3 0 0 270 0
EG=EG
T 63000 72730 5 3 0 0 270 0
PT=PT
T 63000 73030 5 3 0 0 270 0
KF=KF
T 62800 73030 5 3 0 0 270 0
AF=AF
T 62800 72800 5 3 0 0 270 0
VT=VT
T 63100 73400 5 3 0 0 270 0
architecture=?SPICE_Diode_Model
T 62700 72730 5 3 0 0 270 0
RS=?1.0
}
N 62900 73300 62900 73900 4
N 63000 72700 62700 72700 4
N 62700 72700 62700 73500 4
N 62700 73500 62200 73500 4
N 62200 73500 62200 73400 4
