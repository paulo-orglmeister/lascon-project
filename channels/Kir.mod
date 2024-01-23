TITLE Kir.mod   C. Elegans Kir current (irk)
 
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
        SUFFIX Kir
        REPRESENTS NCIT:C17008   : potassium channel
        NONSPECIFIC_CURRENT i_Kir
        RANGE g_Kir_bar, g_Kir
        GLOBAL minf_Kir, mtau_Kir
        
	THREADSAFE : assigned GLOBALs will be per thread
}
 
PARAMETER {       
        g_Kir_bar = 0.0025 (S/cm2)	<0,1e9>
        ek = -80 (mV)
}
 
STATE {
        m_Kir   
}
 
ASSIGNED {
        v (mV) 
        :-----------------------------------Kir channels-----------------------------------------
        g_Kir (S/cm2)
        i_Kir (mA/cm2)
        minf_Kir 
	    mtau_Kir (ms) }
 
? currents
BREAKPOINT {
        SOLVE states METHOD cnexp
        g_Kir = g_Kir_bar*m_Kir
	    i_Kir = g_Kir*(v - ek)
        }
 
 
INITIAL {
	rates(v)
        m_Kir = minf_Kir
	}

? states
DERIVATIVE states {  
        rates(v)
        m_Kir' =  (minf_Kir-m_Kir)/mtau_Kir
}
 



? rates
PROCEDURE rates(v(mV)) {  :Computes rate and other constants at current v.
                      :Call once from HOC to initialize inf at resting v.
        
        
UNITSOFF :Calculates activation / inactivation variables
        minf_Kir = 1/(1+exp(-(v-(-52)+30)/13))
        mtau_Kir = 17.0752/(exp(-(v-(-17.8528))/20.3154)+exp((v-(-43.4414)))/11.1691)+3.8329
}
 
FUNCTION vtrap(x,y) {  :Traps for 0 in denominator of rate eqns.
        if (fabs(x/y) < 1e-6) {
                vtrap = y*(1 - x/y/2)
        }else{
                vtrap = x/(exp(x/y) - 1)
        }
}
 
UNITSON 