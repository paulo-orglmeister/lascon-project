TITLE awc.mod   C. Elegans leak and NaLCN currents
 
COMMENT

This current is part of a model for the AWC and RMD neurons in C. Elegans, following the treatment in Nicoletti et al. (2019).
with five voltage-gated potassium currents (Kv4, Kir, Kvs1, Kv7, Kv10), two voltage-gated calcium currents (Cav1, Cav2),
NaLCN and leak channels

Membrane voltage is in absolute mV 

ENDCOMMENT
 
UNITS {
        (mA) = (milliamp)
        (mV) = (millivolt)
	(S) = (siemens)
}

? interface
NEURON {
        SUFFIX Kvs1
        :REPRESENTS NCIT:C17145   : sodium channel
        REPRESENTS NCIT:C17008   : potassium channel
        NONSPECIFIC_CURRENT iNalcn
        NONSPECIFIC_CURRENT il
        RANGE g_Nalcn, gl, el, eNa
        
	THREADSAFE : assigned GLOBALs will be per thread
}
 
PARAMETER {
                
        gl = .0027 (S/cm2)	<0,1e9> 
        el = -90.0 (mV) :value for AWC neuro
        g_Nalcn = .0006 (S/cm2)	<0,1e9> 
        eNa = 30 (mV) :value for AWC neuro
}
 
STATE {
       }
 
ASSIGNED {
        v (mV)
        il (mA/cm2)
        iNalcn (mA/cm2)
        }
 
? currents
BREAKPOINT {
        SOLVE states METHOD cnexp
        il = gl*(v - el)
        iNalcn = g_Nalcn *(v-eNa)
}
 
 
INITIAL {
	    }

? states

FUNCTION vtrap(x,y) {  :Traps for 0 in denominator of rate eqns.
        if (fabs(x/y) < 1e-6) {
                vtrap = y*(1 - x/y/2)
        }else{
                vtrap = x/(exp(x/y) - 1)
        }
}
 
UNITSON
