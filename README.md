Compartmental models of AWC(on) and RMD neurons in C. Elegans based on Nicoletti et al. (2019) using NEURON simulator.
Implements the following ion channels in .mod files:
	- Kv4 (shl-1)
	- Kv1 (shk-1)
	- Kvs1 (ksvs-1)
	- Kv7 (kqt-3)
	- Kv10 (egl-2)
	- Kv3 (egl-36)
	- Kir (irk)
	- Cav1 (egl-19)
	- Cav2 (unc-2)
	- Cav3 (cca-1)
	- Na leak
	- Leak

To compile .mod files install NEURON and use nrnivmodl <your_file.mod>. This will create a folder with a ./special executable.
Python scripts which make use of these ion channels are run using ./special <your_script.py>.
