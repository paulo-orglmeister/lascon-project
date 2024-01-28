TITLE Kv3.mod   C. Elegans Kv3 current (egl-36)

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
        SUFFIX Kv3
        REPRESENTS NCIT:C17008   : potassium channel
        NONSPECIFIC_CURRENT i_Kv3
        GLOBAL m1inf_Kv3, m2inf_Kv3, m3inf_Kv3, m1tau_Kv3,  m2tau_Kv3,  m3tau_Kv3

	THREADSAFE : assigned GLOBALs will be per thread
}
 
PARAMETER {       
        g_Kv3_bar = .04138029 (S/cm2)	<0,1e9>
        ek = -80 (mV)
}
 
STATE {
        m1_Kv3 m2_Kv3 m3_Kv3   
}
 
ASSIGNED {
        v (mV)
        :-----------------------------------Kv3 channels-----------------------------------------
        g_Kv3 (S/cm2)
        i_Kv3 (mA/cm2)
        m1inf_Kv3 m2inf_Kv3 m3inf_Kv3 
	    m1tau_Kv3 (ms) m2tau_Kv3 (ms) m3tau_Kv3 (ms)
}
 
? currents
BREAKPOINT {
        SOLVE states METHOD cnexp
        g_Kv3 = g_Kv3_bar*(0.31*m1_Kv3+0.36*m2_Kv3+0.39*m3_Kv3)
	    i_Kv3 = g_Kv3*(v - ek)
        }
 
 
INITIAL {
	    rates(v)
        m1_Kv3 = 0.0
        m2_Kv3 = 0.0
        m3_Kv3 = 0.0
	}

? states
DERIVATIVE states {  
        rates(v)
        m1_Kv3' =  (m1inf_Kv3-m1_Kv3)/m1tau_Kv3
        m2_Kv3' =  (m2inf_Kv3-m2_Kv3)/m2tau_Kv3
        m3_Kv3' =  (m3inf_Kv3-m3_Kv3)/m3tau_Kv3
    }
 



? rates
PROCEDURE rates(v(mV)) {  :Computes rate and other constants at current v.
                      :Call once from HOC to initialize inf at resting v.
        
        
UNITSOFF :Calculates activation / inactivation variables
        m1inf_Kv3 = 1/(1+exp(-(v-63+18)/(28.5)))
        m1tau_Kv3 = 355
        m2inf_Kv3 = 1/(1+exp(-(v-63+18)/(28.5)))
        m2tau_Kv3 = 63
        m3inf_Kv3 = 1/(1+exp(-(v-63+18)/(28.5)))
        m3tau_Kv3 = 13
       
}
 
FUNCTION vtrap(x,y) {  :Traps for 0 in denominator of rate eqns.
        if (fabs(x/y) < 1e-6) {
                vtrap = y*(1 - x/y/2)
        }else{
                vtrap = x/(exp(x/y) - 1)
        }
}
 
UNITSON 