from neuron import h, gui

#C. elegans AWCR neuron

soma = h.Section(name='soma')
dend = h.Section(name='dend')

dend.connect(soma(1))

soma.L = soma.diam = 3 #um
dend.L = 50 #um
dend.diam = 0.2 #um

print("Surface area of soma = {}".format(soma(0.5).area()))

for sec in h.allsec():
    sec.Ra = #Ohm/cm
    sec.cm = 1 #uF/cm²

dend.insert('pas')
for seg in dend:
    seg.pas.g = # S/cm2
    seg.pas.e = -65 #mV ?

 
#how to define our own ion channels in neuron?
    
