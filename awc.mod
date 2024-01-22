TITLE awc.mod   C. Elegans AWC sensory neuron
 
COMMENT

This is a model for the AWC neuron in C. Elegans, following the treatment in Nicoletti et al. (2019),
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
        SUFFIX awc
        :REPRESENTS NCIT:C17145   : sodium channel
        REPRESENTS NCIT:C17008   : potassium channel
        :NONSPECIFIC_CURRENT Cav1
        NONSPECIFIC_CURRENT ik_Kvs1
        NONSPECIFIC_CURRENT il
        RANGE gkbar_Kvs1, gl, el, gna, gk_Kvs1
        GLOBAL minf_Kvs1, hinf_Kvs1, mtau_Kvs1, htau_Kvs1
        
	THREADSAFE : assigned GLOBALs will be per thread
}
 
PARAMETER {
                
        gkbar_Kvs1 = .008 (S/cm2)	<0,1e9>

        gl = .0027 (S/cm2)	<0,1e9> 
        el = -90.0 (mV) :value for AWC neuron
}
 
STATE {


        :=========================================================================================
                                        :Voltage gated potassium channels
        :=========================================================================================     
        m_Kvs1 h_Kvs1 

        :=========================================================================================
                                        :Voltage gated calcium channels
        :=========================================================================================     
}
 
ASSIGNED {
        v (mV)
        
        :ena (mV)
        ek (mV)

        :gna (S/cm2)
        :ina (mA/cm2)
        il (mA/cm2)
        :=========================================================================================
                                        :Voltage gated potassium channels
        :=========================================================================================

        :-----------------------------------Kvs1 channels-----------------------------------------
	
	gk_Kvs1 (S/cm2)
        ik_Kvs1 (mA/cm2)
        minf_Kvs1 hinf_Kvs1 ninf_Kvs1
	mtau_Kvs1 (ms) htau_Kvs1 (ms) ntau_Kvs1 (ms)
}
 
? currents
BREAKPOINT {
        SOLVE states METHOD cnexp
        
        gk_Kvs1 = gkbar_Kvs1*m_Kvs1*h_Kvs1
	ik_Kvs1 = gk_Kvs1*(v - ek)
        il = gl*(v - el)
}
 
 
INITIAL {
	rates(v)
	m_Kvs1 = minf_Kvs1
	h_Kvs1 = hinf_Kvs1
	:n = ninf
}

? states
DERIVATIVE states {  
        rates(v)
        :=========================================================================================
                                        :Voltage gated potassium channels
        :=========================================================================================
        m_Kvs1' =  (minf_Kvs1-m_Kvs1)/mtau_Kvs1
        h_Kvs1' = (hinf_Kvs1-h_Kvs1)/htau_Kvs1
        :n' = (ninf-n)/ntau
}
 



? rates
PROCEDURE rates(v(mV)) {  :Computes rate and other constants at current v.
                      :Call once from HOC to initialize inf at resting v.
        
        TABLE minf_Kvs1, mtau_Kvs1, hinf_Kvs1, htau_Kvs1 DEPEND celsius FROM -100 TO 100 WITH 200

UNITSOFF :Calculates activation / inactivation variables

        :=========================================================================================
                                        :Voltage gated potassium channels
        :=========================================================================================
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
