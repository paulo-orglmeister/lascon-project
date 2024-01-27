TITLE Cav1.mod   C. Elegans Cav1 (egl-19) current
 
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
        SUFFIX Cav1
        REPRESENTS NCIT:C17008   : potassium channel
        NONSPECIFIC_CURRENT i_Cav1
        RANGE g_Cav1_bar, g_Cav1
        GLOBAL minf_Cav1, hinf_Cav1, mtau_Cav1, htau_Cav1
        
	THREADSAFE : assigned GLOBALs will be per thread
}
 
PARAMETER {       
        g_Cav1_bar = .00137050 (S/cm2)	<0,1e9>
        eca = 60 
}
 
STATE {
        m_Cav1 h_Cav1  
}
 
ASSIGNED {
        v (mV) 
        :-----------------------------------Cav1 channels-----------------------------------------
        g_Cav1 (S/cm2)
        i_Cav1 (mA/cm2)
        minf_Cav1 hinf_Cav1 
	mtau_Cav1 (ms) htau_Cav1 (ms)
}
 
? currents
BREAKPOINT {
        SOLVE states METHOD cnexp
        g_Cav1 = g_Cav1_bar*m_Cav1*h_Cav1
	    i_Cav1 = g_Cav1*(v - eca)
        }
 
 
INITIAL {
	rates(v)
        m_Cav1 = 0.0
	h_Cav1 = 1.0
}

? states
DERIVATIVE states {  
        rates(v)
        m_Cav1' = (minf_Cav1-m_Cav1)/mtau_Cav1
        h_Cav1' = (hinf_Cav1-h_Cav1)/htau_Cav1
}
 



? rates
PROCEDURE rates(v(mV)) {  :Computes rate and other constants at current v.
                      :Call once from HOC to initialize inf at resting v.
        
        :TABLE minf_Kvs1, mtau_Kvs1, hinf_Kvs1, htau_Kvs1 DEPEND celsius FROM -100 TO 100 WITH 200

UNITSOFF :Calculates activation / inactivation variables
        minf_Cav1 = 1/(1+exp(-(v-5.6+10)/7.50)) 
        mtau_Cav1 = 2.3359+(2.9324*exp(-(v-5.2357+10)^2/(6.0)^2))+(1.8739*exp(-(v-1.3930+10)^2/(30.0)^2))
        hinf_Cav1 = (1.4314/(1+exp(-(v-24.8573+10)/11.9541))+0.1427)*(5.9589/(1+exp((v-(-10.5428)+10)/8.0552))+0.6038)
        htau_Cav1 = 0.4*(((0.55*81.1179)/(1+exp((v-(-22.9723)+10)/5)))+43.0937+((0.9*40.4885)/(1+exp((v-28.7251+10)/3.7125)))+0)
}
 
FUNCTION vtrap(x,y) {  :Traps for 0 in denominator of rate eqns.
        if (fabs(x/y) < 1e-6) {
                vtrap = y*(1 - x/y/2)
        }else{
                vtrap = x/(exp(x/y) - 1)
        }
}
 
UNITSON
