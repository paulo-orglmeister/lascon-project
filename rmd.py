#C. elegans RMDR neuron
    
from neuron import h, gui
import matplotlib.pyplot as plt

class RMDCell: 
    def __init__(self):
        self.create_sections()
        self.build_topology()
        self.define_geometry()
        self.define_biophysics()

    def create_sections(self):
        """Create the sections of the cell."""
        self.soma = h.Section(name='soma')
        self.dend = h.Section(name='dend')
    
    def build_topology(self):
        """Connect the sections of the cell"""
        self.dend.connect(self.soma(1.0))
    
    def define_geometry(self):
        """Set the 3D geometry of the cell."""
        self.soma.L = self.soma.diam = 4.84 # microns (estimate)
        self.dend.L = 42  # microns                   
        self.dend.diam = 0.3 # microns                    
        self.dend.nseg = 11
    
    def define_biophysics(self):
        """Assign the membrane properties across the cell."""

        self.soma.cm = 1.63 # (uF/cm2) (Nicoletti et. al)
        #Insert custom currents defined in .mod files
        self.soma.insert('Kv3') 
        self.soma.insert('Kv4')  
        self.soma.insert('Kir')  
        self.soma.insert('Cav1') 
        self.soma.insert('Cav2')  
        self.soma.insert('Cav3')

        self.soma.g_Kv3_bar_Kv3   = .00176646 #S/cm2 (egl-36)
        self.soma.gl_Kv4          = .00054352 #S/cm2 (leak) 
        self.soma.g_Nalcn_Kv4     = .00006794 #S/cm2 (nca)
        self.soma.g_Kv4_bar_Kv4   = .00339703 #S/cm2 (shl-1)  
        self.soma.g_Kir_bar_Kir   = .00027176 #S/cm2 (irkl-3) 
        self.soma.g_Cav1_bar_Cav1 = .00134522 #S/cm2 (elg-19) 
        self.soma.g_Cav2_bar_Cav2 = .00122293 #S/cm2 (unc-2) 
        self.soma.g_Cav3_bar_Cav3 = .00421232 #S/cm2 (cca-1)

        # Insert passive current in the dendrite
        self.dend.insert('pas')
        self.dend.g_pas = 10**(-5) # Passive conductance in S/cm2  - estimated at 100 kOhm*cm2, from data in Palyanov et al.
        self.dend.e_pas = -80      # Leak reversal potential mV
        self.dend.Ra = 100         # Axial resistivity in Ohm*cm, from data in Palyanov et al.
        self.dend.cm = 1           # uF/cm2
                
    def add_current_stim1(self, delay,curr):
        self.stim1 = h.IClamp(self.soma(0.5)) #1.0 is the distal end of the dendrite
        self.stim1.amp = curr*0.001 # input current in nA
        self.stim1.delay = delay  # turn on after this time in ms
        self.stim1.dur = 25  # duration of 1 ms
    
    def add_current_stim2(self, delay,curr):
        self.stim2 = h.IClamp(self.soma(0.5)) #1.0 is the distal end of the dendrite
        self.stim2.amp = curr*0.001 # input current in nA
        self.stim2.delay = delay  # turn on after this time in ms
        self.stim2.dur = 25  # duration in ms
    
    
    def set_recording(self):
        """Set soma, dendrite, and time recording vectors on the cell. """
        self.soma_v_vec = h.Vector()   # Membrane potential vector at soma
        #self.dend_v_vec = h.Vector()   # Membrane potential vector at dendrite
        self.t_vec = h.Vector()        # Time stamp vector
        self.soma_v_vec.record(self.soma(0.5)._ref_v)
       # self.dend_v_vec.record(self.dend(0.5)._ref_v)
        self.t_vec.record(h._ref_t)

    def plot_voltage(self, title='Cell voltage', ylim=None, show=True):
        """Plot the recorded traces"""
        fig = plt.figure(figsize=(8,4)) # Default figsize is (8,6)
        plt.plot(self.t_vec, self.soma_v_vec, color='black', label='soma(0.5)')
        #plt.plot(self.t_vec, self.dend_v_vec, color='red', label='dend(0.5)')
        plt.legend()
        plt.xlabel('time (ms)')
        plt.ylabel('mV')
        plt.ylim(ylim)
        plt.title(title)
        if show:
            plt.show()
        return fig

rmdCell = RMDCell()
rmdCell.set_recording()

rmdCell.add_current_stim1(900,5)


rmdCell.add_current_stim2(1400,-10)


h.tstop = 2000  # (ms) set simulation duration
h.init()
h.run()  # run simulation

rmdCell.plot_voltage()  # plot voltage
