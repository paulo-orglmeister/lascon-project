#C. elegans AWCR neuron
    
from neuron import h, gui
import matplotlib.pyplot as plt

class AWCCell: 
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
        self.soma.L = self.soma.diam = 2.0 # microns
       # self.dend.L = 200                      # microns
       # self.dend.diam = 1                     # microns
       # self.dend.nseg = 10
    
    def define_biophysics(self):
        """Assign the membrane properties across the cell."""
        '''
        for sec in [self.soma, self.dend]: # 
            sec.Ra = 100    # Axial resistance in Ohm * cm
            sec.cm = 1      # Membrane capacitance in micro Farads / cm^2
        '''

        self.soma.Ra = 100
        self.soma.cm = 1
        self.soma.insert('awc') #Inserts custom current defined in awc.mod 
        # Insert passive current in the dendrite
        #self.dend.insert('pas')
        #self.dend.g_pas = 0.001  # Passive conductance in S/cm2
        #self.dend.e_pas = -65    # Leak reversal potential mV
                
    def add_current_stim(self, delay):
        self.stim = h.IClamp(self.soma(1.0))
        self.stim.amp = 0.04  # input current in nA
        self.stim.delay = delay  # turn on after this time in ms
        self.stim.dur = 10  # duration of 1 ms
    
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

awcCell = AWCCell()
awcCell.set_recording()

awcCell.add_current_stim(20)

#postSyn1 = h.ExpSyn(postCell.dend(0.5)) #exponential synapse
#postSyn1.e = 0 #mV
#postSyn1.tau = 2 #ms

h.tstop = 60 # set simulation duration
h.init()
h.run()  # run simulation

awcCell.plot_voltage()  # plot voltage
