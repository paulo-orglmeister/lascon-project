TITLE Kv10.mod   C. Elegans Kv10 current (egl-2)
 
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
        SUFFIX Kv10
        REPRESENTS NCIT:C17008   : potassium channel
        NONSPECIFIC_CURRENT i_Kv10
        RANGE g_Kv10_bar, g_Kv10
        GLOBAL minf_Kv10, mtau_Kv10
        
	THREADSAFE : assigned GLOBALs will be per thread
}
 
PARAMETER {       
        g_Kv10_bar = 0.0085 (S/cm2)	<0,1e9>
        ek = -80 (mV)
}
 
STATE {
        m_Kv10   
}
 
ASSIGNED {
        v (mV) 
        :-----------------------------------Kv10 channels-----------------------------------------
        g_Kv10 (S/cm2)
        i_Kv10 (mA/cm2)
        minf_Kv10 
	    mtau_Kv10 (ms) }
 
? currents
BREAKPOINT {
        SOLVE states METHOD cnexp
        g_Kv10 = g_Kv10_bar*m_Kv10
	    i_Kv10 = g_Kv10*(v - ek)
        }
 
 
INITIAL {
	rates(v)
        m_Kv10 = minf_Kv10
	}

? states
DERIVATIVE states {  
        rates(v)
        m_Kv10' =  (minf_Kv10-m_Kv10)/mtau_Kv10
}
 



? rates
PROCEDURE rates(v(mV)) {  :Computes rate and other constants at current v.
                      :Call once from HOC to initialize inf at resting v.
        
        
UNITSOFF :Calculates activation / inactivation variables
        minf_Kv10 = 1/(1+exp(-(v-(-6.8594)+0)/(14.9131)))
        mtau_Kv10 = (16.7800/(exp(-(v-(-17.5165))/13.7976))+ 8.0969) * 0.5   
}
 
FUNCTION vtrap(x,y) {  :Traps for 0 in denominator of rate eqns.
        if (fabs(x/y) < 1e-6) {
                vtrap = y*(1 - x/y/2)
        }else{
                vtrap = x/(exp(x/y) - 1)
        }
}
 
UNITSON 