TITLE Cav2.mod   C. Elegans Cav2 current
 
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
        SUFFIX Cav2
        REPRESENTS NCIT:C17008   : potassium channel
        NONSPECIFIC_CURRENT i_Cav2
        RANGE g_Cav2_bar, g_Cav2
        GLOBAL minf_Cav2, hinf_Cav2, mtau_Cav2, htau_Cav2
        
	THREADSAFE : assigned GLOBALs will be per thread
}
 
PARAMETER {       
        g_Cav2_bar = .00088419 (S/cm2)	<0,1e9>
        eca = 60 (mv)
}
 
STATE {
  
        m_Cav2 h_Cav2  
}
 
ASSIGNED {
        v (mV)
        :-----------------------------------Cav2 channels-----------------------------------------
        g_Cav2 (S/cm2)
        i_Cav2 (mA/cm2)
        minf_Cav2 
        hinf_Cav2 
	mtau_Cav2 (ms) 
        htau_Cav2 (ms)
}
 
? currents
BREAKPOINT {
        SOLVE states METHOD cnexp
                g_Cav2 = g_Cav2_bar*m_Cav2*h_Cav2
	    i_Cav2 = g_Cav2*(v - eca)
        }
 
 
INITIAL {
	rates(v)
            m_Cav2 = 0.0
	    h_Cav2 = 1.0
}

? states
DERIVATIVE states {  
        rates(v)
        m_Cav2' =  (minf_Cav2-m_Cav2)/mtau_Cav2
        h_Cav2' = (hinf_Cav2-h_Cav2)/htau_Cav2
}
 



? rates
PROCEDURE rates(v(mV)) {  :Computes rate and other constants at current v.
                      :Call once from HOC to initialize inf at resting v.
        
        :TABLE minf_Kvs1, mtau_Kvs1, hinf_Kvs1, htau_Kvs1 DEPEND celsius FROM -100 TO 100 WITH 200

UNITSOFF :Calculates activation / inactivation variables
        minf_Cav2 = 1/(1+exp(-(v-(-12.17)+25)/(3.97))) 
        mtau_Cav2 = ((1.4969/(exp(-(v-(-8.1761))+30)/(9.0753))+exp((v-(-8.1761)+30)/(15.3456))) + 0.1029)*3    
        hinf_Cav2 = 1/(1+exp((v-(-52.47)+25)/(5.6)))
        htau_Cav2 = (83.8037/(1+exp((v-52.8997+30)/(3.4557)))+72.0995/(1+exp(-(v-23.9009+30)/(3.5903))))*1.7
}
 
FUNCTION vtrap(x,y) {  :Traps for 0 in denominator of rate eqns.
        if (fabs(x/y) < 1e-6) {
                vtrap = y*(1 - x/y/2)
        }else{
                vtrap = x/(exp(x/y) - 1)
        }
}
 
UNITSON
