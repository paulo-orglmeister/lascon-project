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
        #self.dend = h.Section(name='dend')
    
    def build_topology(self):
        """Connect the sections of the cell"""
        #self.dend.connect(self.soma(1))
    
    def define_geometry(self):
        """Set the 3D geometry of the cell."""
        self.soma.L = self.soma.diam = 1.0 # microns (estimate)
        #self.dend.L = 41.92  # microns                   
        #self.dend.diam = 0.2979 # microns                    
        #self.dend.nseg = 11
    
    def define_biophysics(self):
        """Assign the membrane properties across the cell."""
        '''
        for sec in [self.soma, self.dend]: # 
            sec.Ra = 100    # Axial resistance in Ohm * cm
            sec.cm = 1      # Membrane capacitance in micro Farads / cm^2
        '''

        self.soma.cm = 38.19718634 # (uF/cm2) (Nicoletti et. al)
        #Insert custom currents defined in .mod files
        #self.soma.insert('Kv3')
        #self.soma.insert('Kv4')
        #self.soma.insert('Kir')
        #self.soma.insert('Cav1') 
        #self.soma.insert('Cav2')
        #self.soma.insert('Cav3')

        #self.soma.g_Kv3_bar_Kv3    = .04138029 #S/cm2 (egl-36)
        #self.soma.gl_Kv4          = .07957747 #S/cm2 (leak) 
        #self.g_Nalcn_Kv4          =  #S/cm2 (leak)
        #self.soma.g_Kv4_bar_Kv4   =  #S/cm2 (shl-1)  
        #self.soma.g_Kvs1_bar_Kvs1 =  #S/cm2 (kvs-1)   
        #self.soma.g_Kir_bar_Kir   = 0.00636620  #S/cm2 (irkl-3) 
        #self.soma.g_Kv7_bar_Kv7   =  #S/cm2 (kqt-3) 
        #self.soma.g_Kv10_bar_Kv10 =  #S/cm2 (egl-2)  
        #self.soma.g_Cav1_bar_Cav1 =  #S/cm2 (elg-19) 
        #self.soma.g_Cav2_bar_Cav2 =  #S/cm2 (unc-2) 
        
        # Insert passive current in the dendrite
        #self.dend.insert('pas')
        #self.dend.g_pas = 0.001  # Passive conductance in S/cm2
        #self.dend.e_pas = -80    # Leak reversal potential mV
                
    def add_current_stim(self, delay):
        self.stim = h.IClamp(self.soma(0.5)) #1.0 is the distal end of the dendrite
        self.stim.amp = 0.004 # input current in nA
        self.stim.delay = delay  # turn on after this time in ms
        self.stim.dur = 500  # duration of 1 ms
    
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

rmdCell.add_current_stim(900)

h.tstop = 1500  # (ms) set simulation duration
h.init()
h.run()  # run simulation

rmdCell.plot_voltage()  # plot voltage
