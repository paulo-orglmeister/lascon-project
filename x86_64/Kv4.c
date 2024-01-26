/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mech_api.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__Kv4
#define _nrn_initial _nrn_initial__Kv4
#define nrn_cur _nrn_cur__Kv4
#define _nrn_current _nrn_current__Kv4
#define nrn_jacob _nrn_jacob__Kv4
#define nrn_state _nrn_state__Kv4
#define _net_receive _net_receive__Kv4 
#define rates rates__Kv4 
#define states states__Kv4 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define g_Kv4_bar _p[0]
#define g_Kv4_bar_columnindex 0
#define ek _p[1]
#define ek_columnindex 1
#define gl _p[2]
#define gl_columnindex 2
#define el _p[3]
#define el_columnindex 3
#define g_Nalcn _p[4]
#define g_Nalcn_columnindex 4
#define eNa _p[5]
#define eNa_columnindex 5
#define il _p[6]
#define il_columnindex 6
#define iNalcn _p[7]
#define iNalcn_columnindex 7
#define g_Kv4 _p[8]
#define g_Kv4_columnindex 8
#define i_Kv4 _p[9]
#define i_Kv4_columnindex 9
#define m_Kv4 _p[10]
#define m_Kv4_columnindex 10
#define hf_Kv4 _p[11]
#define hf_Kv4_columnindex 11
#define hs_Kv4 _p[12]
#define hs_Kv4_columnindex 12
#define Dm_Kv4 _p[13]
#define Dm_Kv4_columnindex 13
#define Dhf_Kv4 _p[14]
#define Dhf_Kv4_columnindex 14
#define Dhs_Kv4 _p[15]
#define Dhs_Kv4_columnindex 15
#define v _p[16]
#define v_columnindex 16
#define _g _p[17]
#define _g_columnindex 17
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 /* declaration of user functions */
 static void _hoc_rates(void);
 static void _hoc_vtrap(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_Kv4", _hoc_setdata,
 "rates_Kv4", _hoc_rates,
 "vtrap_Kv4", _hoc_vtrap,
 0, 0
};
#define vtrap vtrap_Kv4
 extern double vtrap( _threadargsprotocomma_ double , double );
 /* declare global and static user variables */
 static int _thread1data_inuse = 0;
static double _thread1data[5];
#define _gth 0
#define hftau_Kv4_Kv4 _thread1data[0]
#define hftau_Kv4 _thread[_gth]._pval[0]
#define hstau_Kv4_Kv4 _thread1data[1]
#define hstau_Kv4 _thread[_gth]._pval[1]
#define hinf_Kv4_Kv4 _thread1data[2]
#define hinf_Kv4 _thread[_gth]._pval[2]
#define mtau_Kv4_Kv4 _thread1data[3]
#define mtau_Kv4 _thread[_gth]._pval[3]
#define minf_Kv4_Kv4 _thread1data[4]
#define minf_Kv4 _thread[_gth]._pval[4]
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "gl_Kv4", 0, 1e+09,
 "g_Nalcn_Kv4", 0, 1e+09,
 "g_Kv4_bar_Kv4", 0, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "mtau_Kv4_Kv4", "ms",
 "hstau_Kv4_Kv4", "ms",
 "g_Kv4_bar_Kv4", "S/cm2",
 "ek_Kv4", "mV",
 "gl_Kv4", "S/cm2",
 "el_Kv4", "mV",
 "g_Nalcn_Kv4", "S/cm2",
 "eNa_Kv4", "mV",
 "il_Kv4", "mA/cm2",
 "iNalcn_Kv4", "mA/cm2",
 "g_Kv4_Kv4", "S/cm2",
 "i_Kv4_Kv4", "mA/cm2",
 0,0
};
 static double delta_t = 0.01;
 static double hs_Kv40 = 0;
 static double hf_Kv40 = 0;
 static double m_Kv40 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "minf_Kv4_Kv4", &minf_Kv4_Kv4,
 "hinf_Kv4_Kv4", &hinf_Kv4_Kv4,
 "mtau_Kv4_Kv4", &mtau_Kv4_Kv4,
 "hftau_Kv4_Kv4", &hftau_Kv4_Kv4,
 "hstau_Kv4_Kv4", &hstau_Kv4_Kv4,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(NrnThread*, _Memb_list*, int);
static void nrn_state(NrnThread*, _Memb_list*, int);
 static void nrn_cur(NrnThread*, _Memb_list*, int);
static void  nrn_jacob(NrnThread*, _Memb_list*, int);
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(NrnThread*, _Memb_list*, int);
static void _ode_matsol(NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[0]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"Kv4",
 "g_Kv4_bar_Kv4",
 "ek_Kv4",
 "gl_Kv4",
 "el_Kv4",
 "g_Nalcn_Kv4",
 "eNa_Kv4",
 0,
 "il_Kv4",
 "iNalcn_Kv4",
 "g_Kv4_Kv4",
 "i_Kv4_Kv4",
 0,
 "m_Kv4_Kv4",
 "hf_Kv4_Kv4",
 "hs_Kv4_Kv4",
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 18, _prop);
 	/*initialize range parameters*/
 	g_Kv4_bar = 0.00082;
 	ek = -80;
 	gl = 8e-05;
 	el = -80;
 	g_Nalcn = 2e-05;
 	eNa = 30;
 	_prop->param = _p;
 	_prop->param_size = 18;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 1, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _thread_mem_init(Datum*);
 static void _thread_cleanup(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _Kv4_reg() {
	int _vectorized = 1;
  _initlists();
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 2);
  _extcall_thread = (Datum*)ecalloc(1, sizeof(Datum));
  _thread_mem_init(_extcall_thread);
  _thread1data_inuse = 0;
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 1, _thread_mem_init);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 18, 1);
  hoc_register_dparam_semantics(_mechtype, 0, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Kv4 /home/paulo/Documents/Estudos/Ciências/Ciências Naturais/Biologia/Neurociência/LASCON/lascon-project/channels/Kv4.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "Kv4.mod   C. Elegans Kv4 current (shl-1), NaLCN current and leak current";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_threadargsprotocomma_ double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[3], _dlist1[3];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   rates ( _threadargscomma_ v ) ;
   Dm_Kv4 = ( minf_Kv4 - m_Kv4 ) / mtau_Kv4 ;
   Dhs_Kv4 = ( hinf_Kv4 - hs_Kv4 ) / hstau_Kv4 ;
   Dhf_Kv4 = ( hinf_Kv4 - hf_Kv4 ) / hftau_Kv4 ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 rates ( _threadargscomma_ v ) ;
 Dm_Kv4 = Dm_Kv4  / (1. - dt*( ( ( ( - 1.0 ) ) ) / mtau_Kv4 )) ;
 Dhs_Kv4 = Dhs_Kv4  / (1. - dt*( ( ( ( - 1.0 ) ) ) / hstau_Kv4 )) ;
 Dhf_Kv4 = Dhf_Kv4  / (1. - dt*( ( ( ( - 1.0 ) ) ) / hftau_Kv4 )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) { {
   rates ( _threadargscomma_ v ) ;
    m_Kv4 = m_Kv4 + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / mtau_Kv4)))*(- ( ( ( minf_Kv4 ) ) / mtau_Kv4 ) / ( ( ( ( - 1.0 ) ) ) / mtau_Kv4 ) - m_Kv4) ;
    hs_Kv4 = hs_Kv4 + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / hstau_Kv4)))*(- ( ( ( hinf_Kv4 ) ) / hstau_Kv4 ) / ( ( ( ( - 1.0 ) ) ) / hstau_Kv4 ) - hs_Kv4) ;
    hf_Kv4 = hf_Kv4 + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / hftau_Kv4)))*(- ( ( ( hinf_Kv4 ) ) / hftau_Kv4 ) / ( ( ( ( - 1.0 ) ) ) / hftau_Kv4 ) - hf_Kv4) ;
   }
  return 0;
}
 
static int  rates ( _threadargsprotocomma_ double _lv ) {
    minf_Kv4 = 1.0 / ( 1.0 + exp ( - ( _lv - 11.2 + 18.0 ) / ( 14.1 ) ) ) ;
   mtau_Kv4 = ( ( 13.8 / ( exp ( - ( _lv - ( - 17.5165 ) ) / 12.9213 ) + exp ( ( _lv - ( - 3.7082 ) ) ) / 6.4876 ) ) + 1.8849 ) * 0.1 ;
   hinf_Kv4 = 1.0 / ( 1.0 + exp ( ( _lv - ( - 33.1 ) + 18.0 ) / ( 8.3 ) ) ) ;
   hstau_Kv4 = ( 8422.0 / ( 1.0 + exp ( ( _lv + 37.7391 ) / 6.3785 ) ) + 118.8983 ) * 0.1 ;
   hftau_Kv4 = ( 539.1584 / ( 1.0 + exp ( ( _lv + 28.1990 ) / 4.9199 ) ) + 27.2811 ) * 0.1 ;
    return 0; }
 
static void _hoc_rates(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 rates ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double vtrap ( _threadargsprotocomma_ double _lx , double _ly ) {
   double _lvtrap;
 if ( fabs ( _lx / _ly ) < 1e-6 ) {
     _lvtrap = _ly * ( 1.0 - _lx / _ly / 2.0 ) ;
     }
   else {
     _lvtrap = _lx / ( exp ( _lx / _ly ) - 1.0 ) ;
     }
   
return _lvtrap;
 }
 
static void _hoc_vtrap(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  vtrap ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 3;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 (_p, _ppvar, _thread, _nt);
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 3; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }
 
static void _ode_matsol(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
 _ode_matsol_instance1(_threadargs_);
 }}
 
static void _thread_mem_init(Datum* _thread) {
  if (_thread1data_inuse) {_thread[_gth]._pval = (double*)ecalloc(5, sizeof(double));
 }else{
 _thread[_gth]._pval = _thread1data; _thread1data_inuse = 1;
 }
 }
 
static void _thread_cleanup(Datum* _thread) {
  if (_thread[_gth]._pval == _thread1data) {
   _thread1data_inuse = 0;
  }else{
   free((void*)_thread[_gth]._pval);
  }
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  hs_Kv4 = hs_Kv40;
  hf_Kv4 = hf_Kv40;
  m_Kv4 = m_Kv40;
 {
   rates ( _threadargscomma_ v ) ;
   m_Kv4 = minf_Kv4 ;
   hf_Kv4 = hinf_Kv4 ;
   hs_Kv4 = hinf_Kv4 ;
   }
 
}
}

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
 initmodel(_p, _ppvar, _thread, _nt);
}
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   g_Kv4 = g_Kv4_bar * ( pow( m_Kv4 , 3.0 ) ) * ( 0.7 * hf_Kv4 + 0.3 * hs_Kv4 ) ;
   i_Kv4 = g_Kv4 * ( v - ek ) ;
   il = gl * ( v - el ) ;
   iNalcn = g_Nalcn * ( v - eNa ) ;
   }
 _current += i_Kv4;
 _current += iNalcn;
 _current += il;

} return _current;
}

static void nrn_cur(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
 	}
 _g = (_g - _rhs)/.001;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}
 
}

static void nrn_jacob(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}
 
}

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
 {   states(_p, _ppvar, _thread, _nt);
  }}}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = m_Kv4_columnindex;  _dlist1[0] = Dm_Kv4_columnindex;
 _slist1[1] = hs_Kv4_columnindex;  _dlist1[1] = Dhs_Kv4_columnindex;
 _slist1[2] = hf_Kv4_columnindex;  _dlist1[2] = Dhf_Kv4_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/paulo/Documents/Estudos/Ciências/Ciências Naturais/Biologia/Neurociência/LASCON/lascon-project/channels/Kv4.mod";
static const char* nmodl_file_text = 
  "TITLE Kv4.mod   C. Elegans Kv4 current (shl-1), NaLCN current and leak current\n"
  " \n"
  "COMMENT\n"
  "\n"
  "This current is part of a model for the AWC and RMD neurons in C. Elegans, following the treatment in Nicoletti et al. (2019).\n"
  "\n"
  "Membrane voltage is in absolute mV \n"
  "\n"
  "ENDCOMMENT\n"
  " \n"
  "UNITS {\n"
  "        (mA) = (milliamp)\n"
  "        (mV) = (millivolt)\n"
  "	    (S) = (siemens)\n"
  "}   \n"
  "\n"
  "? interface\n"
  "NEURON {\n"
  "        SUFFIX Kv4\n"
  "        REPRESENTS NCIT:C17008   : potassium channel\n"
  "        NONSPECIFIC_CURRENT i_Kv4\n"
  "        NONSPECIFIC_CURRENT iNalcn\n"
  "        NONSPECIFIC_CURRENT il\n"
  "        RANGE g_Kv4_bar, g_Kv4, g_Nalcn, gl, el, eNa, ek\n"
  "        GLOBAL minf_Kv4, hinf_Kv4, mtau_Kv4, hstau_Kv4, hftau_Kv4\n"
  "        \n"
  "	THREADSAFE : assigned GLOBALs will be per thread\n"
  "}\n"
  " \n"
  "PARAMETER {       \n"
  "        g_Kv4_bar = 0.00082 (S/cm2)	<0,1e9>\n"
  "        ek = -80 (mV)\n"
  "        gl = .00008 (S/cm2)	<0,1e9> \n"
  "        el = -80.0 (mV) :value for AWC neuro\n"
  "        g_Nalcn = .00002 (S/cm2)	<0,1e9> \n"
  "        eNa = 30 (mV) :value for AWC neuro\n"
  "}\n"
  " \n"
  "STATE {\n"
  "        m_Kv4 hf_Kv4 hs_Kv4  \n"
  "}\n"
  " \n"
  "ASSIGNED {\n"
  "        v (mV)\n"
  "        :-----------------------------------leak and Nalcn channels------------------------------\n"
  "        il (mA/cm2)\n"
  "        iNalcn (mA/cm2) \n"
  "        :-----------------------------------Kv4 channels-----------------------------------------\n"
  "        g_Kv4 (S/cm2)\n"
  "        i_Kv4 (mA/cm2)\n"
  "        minf_Kv4 hinf_Kv4 \n"
  "	mtau_Kv4 (ms) hftau_Kv4 hstau_Kv4 (ms)\n"
  "}\n"
  " \n"
  "? currents\n"
  "BREAKPOINT {\n"
  "        SOLVE states METHOD cnexp\n"
  "        g_Kv4 = g_Kv4_bar*(m_Kv4^3)*(0.7*hf_Kv4 + 0.3*hs_Kv4)\n"
  "	i_Kv4 = g_Kv4*(v - ek)\n"
  "        il = gl*(v - el)\n"
  "        iNalcn = g_Nalcn *(v - eNa)\n"
  "        }\n"
  " \n"
  " \n"
  "INITIAL {\n"
  "	rates(v)\n"
  "        m_Kv4 = minf_Kv4\n"
  "	hf_Kv4 = hinf_Kv4 :the steady-state voltages are equal for fast and slow inactivation variables (h)\n"
  "        hs_Kv4 = hinf_Kv4\n"
  "}\n"
  "\n"
  "? states\n"
  "DERIVATIVE states {  \n"
  "        rates(v)\n"
  "        m_Kv4' =  (minf_Kv4-m_Kv4)/mtau_Kv4\n"
  "        hs_Kv4' = (hinf_Kv4-hs_Kv4)/hstau_Kv4\n"
  "        hf_Kv4' = (hinf_Kv4-hf_Kv4)/hftau_Kv4\n"
  "}\n"
  " \n"
  "\n"
  "\n"
  "\n"
  "? rates\n"
  "PROCEDURE rates(v(mV)) {  :Computes rate and other constants at current v.\n"
  "                      :Call once from HOC to initialize inf at resting v.\n"
  "        \n"
  "        \n"
  "UNITSOFF :Calculates activation / inactivation variables\n"
  "        minf_Kv4 = 1/(1+exp(-(v-11.2+18)/(14.1)))\n"
  "        mtau_Kv4 = ((13.8/(exp(-(v-(-17.5165))/12.9213)+exp((v-(-3.7082)))/6.4876))+ 1.8849)*0.1\n"
  "        hinf_Kv4 = 1/(1+exp((v-(-33.1)+18)/(8.3)))\n"
  "        hstau_Kv4 = (8422/(1+exp((v+37.7391)/6.3785))+118.8983)*0.1 :slow inactivation time constant\n"
  "        hftau_Kv4 = (539.1584/(1+exp((v+28.1990)/4.9199))+27.2811)*0.1  :fast inactivation time constant\n"
  "\n"
  "}\n"
  " \n"
  "FUNCTION vtrap(x,y) {  :Traps for 0 in denominator of rate eqns.\n"
  "        if (fabs(x/y) < 1e-6) {\n"
  "                vtrap = y*(1 - x/y/2)\n"
  "        }else{\n"
  "                vtrap = x/(exp(x/y) - 1)\n"
  "        }\n"
  "}\n"
  " \n"
  "UNITSON \n"
  ;
#endif
