TITLE awc.mod   C. Elegans Kvs1 current
 
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
        NONSPECIFIC_CURRENT i_Kvs1
        NONSPECIFIC_CURRENT il
        RANGE g_Kvs1_bar, gl, el, g_Kvs1
        GLOBAL minf_Kvs1, hinf_Kvs1, mtau_Kvs1, htau_Kvs1
        
	THREADSAFE : assigned GLOBALs will be per thread
}
 
PARAMETER {
                
        g_Kvs1_bar = .008 (S/cm2)	<0,1e9>
        gl = .0027 (S/cm2)	<0,1e9> 
        el = -90.0 (mV) :value for AWC neuron
}
 
STATE {
        m_Kvs1 h_Kvs1 
       }
 
ASSIGNED {
        v (mV)
        ek (mV)
        il (mA/cm2)
        :-----------------------------------Kvs1 channels-----------------------------------------
	g_Kvs1 (S/cm2)
        i_Kvs1 (mA/cm2)
        minf_Kvs1 hinf_Kvs1 
	mtau_Kvs1 (ms) htau_Kvs1 (ms)
        }
 
? currents
BREAKPOINT {
        SOLVE states METHOD cnexp
        g_Kvs1 = g_Kvs1_bar*m_Kvs1*h_Kvs1
	i_Kvs1 = g_Kvs1*(v - ek)
        :----------------------------------------------------------------------------------------:
        il = gl*(v - el)
}
 
 
INITIAL {
	rates(v)
        m_Kvs1 = minf_Kvs1
	h_Kvs1 = hinf_Kvs1
        }

? states
DERIVATIVE states {  
        rates(v) m_Kvs1' =  (minf_Kvs1-m_Kvs1)/mtau_Kvs1
        h_Kvs1' = (hinf_Kvs1-h_Kvs1)/htau_Kvs1
}
 



? rates
PROCEDURE rates(v(mV)) {  :Computes rate and other constants at current v.
                      :Call once from HOC to initialize inf at resting v.
        
        TABLE minf_Kvs1, mtau_Kvs1, hinf_Kvs1, htau_Kvs1 DEPEND celsius FROM -100 TO 100 WITH 200

UNITSOFF :Calculates activation / inactivation variables
        minf_Kvs1 = 1/(1+exp(-(v-57.1)/25.0)) 
        mtau_Kvs1 = 30.0/(1+exp(-(v-18.1)/(-20.0))) + 1.0 
        hinf_Kvs1 = 1/(1+exp((v-47.3)/11.1))
        htau_Kvs1 = 88.5/(1+exp(-(v-50.0)/(-15.0))) + 53.4
}
 
FUNCTION vtrap(x,y) {  :Traps for 0 in denominator of rate eqns.
        if (fabs(x/y) < 1e-6) {
                vtrap = y*(1 - x/y/2)
        }else{
                vtrap = x/(exp(x/y) - 1)
        }
}
 
UNITSON
