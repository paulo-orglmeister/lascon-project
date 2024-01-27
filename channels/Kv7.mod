TITLE Kv7.mod   C. Elegans Kv7 current (kqt-3)
 
COMMENT

This current is a model for the AWC and RMD neurons in C. Elegans, following the treatment in Nicoletti et al. (2019).

Membrane voltage is in absolute mV 

ENDCOMMENT
 
UNITS {
        (mA) = (milliamp)
        (mV) = (millivolt)
	(S) = (siemens)
}   

? interface
NEURON {
        SUFFIX Kv7
        NONSPECIFIC_CURRENT i_Kv7
        RANGE g_Kv7_bar, g_Kv7
        GLOBAL minf_Kv7, winf_Kv7, sinf_Kv7, mstau_Kv7, mftau_Kv7, wtau_Kv7, stau_Kv7
        
	THREADSAFE : assigned GLOBALs will be per thread
}
 
PARAMETER {       
        g_Kv7_bar = .000486307 (S/cm2)	<0,1e9>
        ek = -80 (mV)
}
 
STATE {
  
        ms_Kv7 mf_Kv7 w_Kv7 s_Kv7  
}
 
ASSIGNED {
        v (mV)
        :-----------------------------------Kv7 channels-----------------------------------------
        g_Kv7 (S/cm2)
        i_Kv7 (mA/cm2)
        minf_Kv7 sinf_Kv7 winf_Kv7 
	mstau_Kv7 (ms) 
        mftau_Kv7 (ms) 
        stau_Kv7 (ms) 
        wtau_Kv7 (ms)
}
 
? currents
BREAKPOINT {
        SOLVE states METHOD cnexp
        g_Kv7 = g_Kv7_bar*(0.3*mf_Kv7 + 0.7*ms_Kv7)*w_Kv7*s_Kv7
	i_Kv7 = g_Kv7*(v - ek) 
        }
 
 
INITIAL {
	rates(v)
        ms_Kv7 = 0.0 :the steady state activation variables are equal for fast and slow m
        mf_Kv7 = 0.0
        s_Kv7 = sinf_Kv7
        w_Kv7 = winf_Kv7
}

? states
DERIVATIVE states {  
        rates(v)
        mf_Kv7' =  (minf_Kv7-mf_Kv7)/mftau_Kv7
        ms_Kv7' =  (minf_Kv7-ms_Kv7)/mstau_Kv7
        s_Kv7' = (sinf_Kv7-s_Kv7)/stau_Kv7
        w_Kv7' = (winf_Kv7-w_Kv7)/wtau_Kv7
}
 

? rates
PROCEDURE rates(v(mV)) {  :Computes rate and other constants at current v.
                      :Call once from HOC to initialize inf at resting v.
        
        
UNITSOFF :Calculates activation / inactivation variables
        minf_Kv7 = 1/(1+exp(-(v-(-12.6726)+10)/15.8008))
        mftau_Kv7= (395.3/(1+((v+38.1)/33.59)^2))*0.1
        mstau_Kv7= (5503-5345.4/(1+10^((-0.02827)*((-23.9)-v)))-4590.6/(1+10^((-0.0357)*(v+14.15))))*0.1
        sinf_Kv7 = 0.34+(0.66/(1+exp((v+45.3)/12.3)))
        stau_Kv7 = 5000*0.1
        winf_Kv7 = 0.49+(0.51/(1+exp((v+1.084)/28.78)))
        wtau_Kv7 = (5.44+(29.2/(1+((v+48.09)/48.83)^2)))*0.1
                }
 
FUNCTION vtrap(x,y) {  :Traps for 0 in denominator of rate eqns.
        if (fabs(x/y) < 1e-6) {
                vtrap = y*(1 - x/y/2)
        }else{
                vtrap = x/(exp(x/y) - 1)
        }
}
 
UNITSON
