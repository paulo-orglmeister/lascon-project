TITLE Kv4.mod   C. Elegans Kv4 current (shl-1), NaLCN current and leak current
 
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
        SUFFIX Kv4
        REPRESENTS NCIT:C17008   : potassium channel
        NONSPECIFIC_CURRENT i_Kv4
        NONSPECIFIC_CURRENT iNalcn
        NONSPECIFIC_CURRENT il
        RANGE g_Kv4_bar, g_Nalcn, gl, el, eNa, ek
        GLOBAL minf_Kv4, hinf_Kv4, mtau_Kv4, hstau_Kv4, hftau_Kv4
        
	THREADSAFE : assigned GLOBALs will be per thread
}
 
PARAMETER {       
        g_Kv4_bar = .0 (S/cm2)	<0,1e9> :assigned in python script
        ek = -80 (mV)
        gl = .0 (S/cm2)	<0,1e9> :assigned in python script
        el = -80.0 (mV) :value for AWC neuro
        g_Nalcn = .0 (S/cm2)	<0,1e9> :assigned in python script
        eNa = 30 (mV) :value for AWC neuro
}
 
STATE {
        m_Kv4 hf_Kv4 hs_Kv4  
}
 
ASSIGNED {
        v (mV)
        :-----------------------------------leak and Nalcn channels------------------------------
        il (mA/cm2)
        iNalcn (mA/cm2) 
        :-----------------------------------Kv4 channels-----------------------------------------
        g_Kv4 (S/cm2)
        i_Kv4 (mA/cm2)
        minf_Kv4 hinf_Kv4 
	mtau_Kv4 (ms) hftau_Kv4 hstau_Kv4 (ms)
}
 
? currents
BREAKPOINT {
        SOLVE states METHOD cnexp
        g_Kv4 = g_Kv4_bar*(m_Kv4^3)*(0.7*hf_Kv4 + 0.3*hs_Kv4)
	i_Kv4 = g_Kv4*(v - ek)
        il = gl*(v - el)
        iNalcn = g_Nalcn *(v - eNa)
        }
 
 
INITIAL {
	rates(v)
        m_Kv4 = 0.0
	hf_Kv4 = 1.0 :the steady-state voltages are equal for fast and slow inactivation variables (h)
        hs_Kv4 = 1.0
}

? states
DERIVATIVE states {  
        rates(v)
        m_Kv4' =  (minf_Kv4-m_Kv4)/mtau_Kv4
        hs_Kv4' = (hinf_Kv4-hs_Kv4)/hstau_Kv4
        hf_Kv4' = (hinf_Kv4-hf_Kv4)/hftau_Kv4
}
 



? rates
PROCEDURE rates(v(mV)) {  :Computes rate and other constants at current v.
                      :Call once from HOC to initialize inf at resting v.
        
        
UNITSOFF :Calculates activation / inactivation variables
        minf_Kv4 = 1/(1+exp(-(v-11.2+18)/(14.1)))
        mtau_Kv4 = (13.8/(exp(-(v-(-17.5165))/12.9213)+exp((v-(-3.7082))/6.4876))+ 1.8849)*0.1
        hinf_Kv4 = 1/(1+exp((v-(-33.1)+18)/(8.3)))
        hstau_Kv4 = (8422/(1+exp((v+37.7391)/6.3785))+118.8983)*0.1 :slow inactivation time constant
        hftau_Kv4 = (539.1584/(1+exp((v+28.1990)/4.9199))+27.2811)*0.1  :fast inactivation time constant

}
 
FUNCTION vtrap(x,y) {  :Traps for 0 in denominator of rate eqns.
        if (fabs(x/y) < 1e-6) {
                vtrap = y*(1 - x/y/2)
        }else{
                vtrap = x/(exp(x/y) - 1)
        }
}
 
UNITSON 