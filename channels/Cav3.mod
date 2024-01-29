TITLE Cav3.mod   C. Elegans Cav3 (cca-1) current
 
COMMENT

This current is part of a model for the AWC and RMD neurons in C. Elegans, following the treatment in Nicoletti et al. (2019).

Membrane voltage is in absolute mV 

ENDCOMMENT
 
UNITS {
        (mA) = (milliamp)
        (mV) = (millivolt)
	    (S) = (siemens)
}   

? interface
NEURON {
        SUFFIX Cav3
        REPRESENTS NCIT:C17008   : potassium channel
        NONSPECIFIC_CURRENT i_Cav3
        RANGE g_Cav3_bar, eca
        GLOBAL minf_Cav3, hinf_Cav3, mtau_Cav3, htau_Cav3
        
	THREADSAFE : assigned GLOBALs will be per thread
}
 
PARAMETER {       
        g_Cav3_bar = .0 (S/cm2)	<0,1e9> :assigned in python script
        eca = 60 
}
 
STATE {
        m_Cav3 h_Cav3  
}
 
ASSIGNED {
        v (mV) 
        :-----------------------------------Cav3 channels-----------------------------------------
        g_Cav3 (S/cm2)
        i_Cav3 (mA/cm2)
        minf_Cav3 hinf_Cav3 
	mtau_Cav3 (ms) htau_Cav3 (ms)
}
 
? currents
BREAKPOINT {
        SOLVE states METHOD cnexp
        g_Cav3 = g_Cav3_bar*(m_Cav3^2)*h_Cav3
	    i_Cav3 = g_Cav3*(v - eca)
        }
 
 
INITIAL {
	rates(v)
        m_Cav3 = 0.0
	h_Cav3 = 1.0
}

? states
DERIVATIVE states {  
        rates(v)
        m_Cav3' = (minf_Cav3-m_Cav3)/mtau_Cav3
        h_Cav3' = (hinf_Cav3-h_Cav3)/htau_Cav3
}
 



? rates
PROCEDURE rates(v(mV)) {  :Computes rate and other constants at current v.
                      :Call once from HOC to initialize inf at resting v.
        
        :TABLE minf_Kvs1, mtau_Kvs1, hinf_Kvs1, htau_Kvs1 DEPEND celsius FROM -100 TO 100 WITH 200

UNITSOFF :Calculates activation / inactivation variables
        minf_Cav3 = 1/(1+exp(-(v-(-42.65)+15)/(1.7*1.4))) 
        mtau_Cav3 = ((40/(1+exp(-(v-(-62.5393)+15)/((-12.4758)*1.7))))+0.6947)*0.5
        hinf_Cav3 = 1/(1+exp((v-(-58)+15)/(7*1.15)))
        htau_Cav3 = ((280/(1+exp((v-(-60.7312)+15)/(8.5224*1.1))))+19.7456)*0.08
}
 
FUNCTION vtrap(x,y) {  :Traps for 0 in denominator of rate eqns.
        if (fabs(x/y) < 1e-6) {
                vtrap = y*(1 - x/y/2)
        }else{
                vtrap = x/(exp(x/y) - 1)
        }
}
 
UNITSON
