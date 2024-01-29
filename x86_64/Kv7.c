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
 
#define nrn_init _nrn_init__Kv7
#define _nrn_initial _nrn_initial__Kv7
#define nrn_cur _nrn_cur__Kv7
#define _nrn_current _nrn_current__Kv7
#define nrn_jacob _nrn_jacob__Kv7
#define nrn_state _nrn_state__Kv7
#define _net_receive _net_receive__Kv7 
#define rates rates__Kv7 
#define states states__Kv7 
 
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
#define g_Kv7_bar _p[0]
#define g_Kv7_bar_columnindex 0
#define ek _p[1]
#define ek_columnindex 1
#define g_Kv7 _p[2]
#define g_Kv7_columnindex 2
#define i_Kv7 _p[3]
#define i_Kv7_columnindex 3
#define ms_Kv7 _p[4]
#define ms_Kv7_columnindex 4
#define mf_Kv7 _p[5]
#define mf_Kv7_columnindex 5
#define w_Kv7 _p[6]
#define w_Kv7_columnindex 6
#define s_Kv7 _p[7]
#define s_Kv7_columnindex 7
#define Dms_Kv7 _p[8]
#define Dms_Kv7_columnindex 8
#define Dmf_Kv7 _p[9]
#define Dmf_Kv7_columnindex 9
#define Dw_Kv7 _p[10]
#define Dw_Kv7_columnindex 10
#define Ds_Kv7 _p[11]
#define Ds_Kv7_columnindex 11
#define v _p[12]
#define v_columnindex 12
#define _g _p[13]
#define _g_columnindex 13
 
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
 "setdata_Kv7", _hoc_setdata,
 "rates_Kv7", _hoc_rates,
 "vtrap_Kv7", _hoc_vtrap,
 0, 0
};
#define vtrap vtrap_Kv7
 extern double vtrap( _threadargsprotocomma_ double , double );
 /* declare global and static user variables */
 static int _thread1data_inuse = 0;
static double _thread1data[7];
#define _gth 0
#define mftau_Kv7_Kv7 _thread1data[0]
#define mftau_Kv7 _thread[_gth]._pval[0]
#define mstau_Kv7_Kv7 _thread1data[1]
#define mstau_Kv7 _thread[_gth]._pval[1]
#define minf_Kv7_Kv7 _thread1data[2]
#define minf_Kv7 _thread[_gth]._pval[2]
#define stau_Kv7_Kv7 _thread1data[3]
#define stau_Kv7 _thread[_gth]._pval[3]
#define sinf_Kv7_Kv7 _thread1data[4]
#define sinf_Kv7 _thread[_gth]._pval[4]
#define wtau_Kv7_Kv7 _thread1data[5]
#define wtau_Kv7 _thread[_gth]._pval[5]
#define winf_Kv7_Kv7 _thread1data[6]
#define winf_Kv7 _thread[_gth]._pval[6]
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "g_Kv7_bar_Kv7", 0, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "mstau_Kv7_Kv7", "ms",
 "mftau_Kv7_Kv7", "ms",
 "stau_Kv7_Kv7", "ms",
 "wtau_Kv7_Kv7", "ms",
 "g_Kv7_bar_Kv7", "S/cm2",
 "ek_Kv7", "mV",
 "g_Kv7_Kv7", "S/cm2",
 "i_Kv7_Kv7", "mA/cm2",
 0,0
};
 static double delta_t = 0.01;
 static double mf_Kv70 = 0;
 static double ms_Kv70 = 0;
 static double s_Kv70 = 0;
 static double w_Kv70 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "minf_Kv7_Kv7", &minf_Kv7_Kv7,
 "sinf_Kv7_Kv7", &sinf_Kv7_Kv7,
 "winf_Kv7_Kv7", &winf_Kv7_Kv7,
 "mstau_Kv7_Kv7", &mstau_Kv7_Kv7,
 "mftau_Kv7_Kv7", &mftau_Kv7_Kv7,
 "stau_Kv7_Kv7", &stau_Kv7_Kv7,
 "wtau_Kv7_Kv7", &wtau_Kv7_Kv7,
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
"Kv7",
 "g_Kv7_bar_Kv7",
 "ek_Kv7",
 0,
 "g_Kv7_Kv7",
 "i_Kv7_Kv7",
 0,
 "ms_Kv7_Kv7",
 "mf_Kv7_Kv7",
 "w_Kv7_Kv7",
 "s_Kv7_Kv7",
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 14, _prop);
 	/*initialize range parameters*/
 	g_Kv7_bar = 0.000486307;
 	ek = -80;
 	_prop->param = _p;
 	_prop->param_size = 14;
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

 void _Kv7_reg() {
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
  hoc_register_prop_size(_mechtype, 14, 1);
  hoc_register_dparam_semantics(_mechtype, 0, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Kv7 /home/paulo/Documents/Estudos/Ciências/Ciências Naturais/Biologia/Neurociência/LASCON/lascon-project/channels/Kv7.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "Kv7.mod   C. Elegans Kv7 current (kqt-3)";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_threadargsprotocomma_ double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[4], _dlist1[4];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   rates ( _threadargscomma_ v ) ;
   Dmf_Kv7 = ( minf_Kv7 - mf_Kv7 ) / mftau_Kv7 ;
   Dms_Kv7 = ( minf_Kv7 - ms_Kv7 ) / mstau_Kv7 ;
   Ds_Kv7 = ( sinf_Kv7 - s_Kv7 ) / stau_Kv7 ;
   Dw_Kv7 = ( winf_Kv7 - w_Kv7 ) / wtau_Kv7 ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 rates ( _threadargscomma_ v ) ;
 Dmf_Kv7 = Dmf_Kv7  / (1. - dt*( ( ( ( - 1.0 ) ) ) / mftau_Kv7 )) ;
 Dms_Kv7 = Dms_Kv7  / (1. - dt*( ( ( ( - 1.0 ) ) ) / mstau_Kv7 )) ;
 Ds_Kv7 = Ds_Kv7  / (1. - dt*( ( ( ( - 1.0 ) ) ) / stau_Kv7 )) ;
 Dw_Kv7 = Dw_Kv7  / (1. - dt*( ( ( ( - 1.0 ) ) ) / wtau_Kv7 )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) { {
   rates ( _threadargscomma_ v ) ;
    mf_Kv7 = mf_Kv7 + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / mftau_Kv7)))*(- ( ( ( minf_Kv7 ) ) / mftau_Kv7 ) / ( ( ( ( - 1.0 ) ) ) / mftau_Kv7 ) - mf_Kv7) ;
    ms_Kv7 = ms_Kv7 + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / mstau_Kv7)))*(- ( ( ( minf_Kv7 ) ) / mstau_Kv7 ) / ( ( ( ( - 1.0 ) ) ) / mstau_Kv7 ) - ms_Kv7) ;
    s_Kv7 = s_Kv7 + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / stau_Kv7)))*(- ( ( ( sinf_Kv7 ) ) / stau_Kv7 ) / ( ( ( ( - 1.0 ) ) ) / stau_Kv7 ) - s_Kv7) ;
    w_Kv7 = w_Kv7 + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / wtau_Kv7)))*(- ( ( ( winf_Kv7 ) ) / wtau_Kv7 ) / ( ( ( ( - 1.0 ) ) ) / wtau_Kv7 ) - w_Kv7) ;
   }
  return 0;
}
 
static int  rates ( _threadargsprotocomma_ double _lv ) {
    minf_Kv7 = 1.0 / ( 1.0 + exp ( - ( _lv - ( - 12.6726 ) + 10.0 ) / 15.8008 ) ) ;
   mftau_Kv7 = ( 395.3 / ( 1.0 + pow( ( ( _lv + 38.1 ) / 33.59 ) , 2.0 ) ) ) * 0.1 ;
   mstau_Kv7 = ( 5503.0 - 5345.4 / ( 1.0 + pow( 10.0 , ( ( - 0.02827 ) * ( ( - 23.9 ) - _lv ) ) ) ) - 4590.6 / ( 1.0 + pow( 10.0 , ( ( - 0.0357 ) * ( _lv + 14.15 ) ) ) ) ) * 0.1 ;
   sinf_Kv7 = 0.34 + ( 0.66 / ( 1.0 + exp ( ( _lv + 45.3 ) / 12.3 ) ) ) ;
   stau_Kv7 = 5000.0 * 0.1 ;
   winf_Kv7 = 0.49 + ( 0.51 / ( 1.0 + exp ( ( _lv + 1.084 ) / 28.78 ) ) ) ;
   wtau_Kv7 = ( 5.44 + ( 29.2 / ( 1.0 + pow( ( ( _lv + 48.09 ) / 48.83 ) , 2.0 ) ) ) ) * 0.1 ;
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
 
static int _ode_count(int _type){ return 4;}
 
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
	for (_i=0; _i < 4; ++_i) {
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
  if (_thread1data_inuse) {_thread[_gth]._pval = (double*)ecalloc(7, sizeof(double));
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
  mf_Kv7 = mf_Kv70;
  ms_Kv7 = ms_Kv70;
  s_Kv7 = s_Kv70;
  w_Kv7 = w_Kv70;
 {
   rates ( _threadargscomma_ v ) ;
   ms_Kv7 = 0.0 ;
   mf_Kv7 = 0.0 ;
   s_Kv7 = sinf_Kv7 ;
   w_Kv7 = winf_Kv7 ;
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
   g_Kv7 = g_Kv7_bar * ( 0.3 * mf_Kv7 + 0.7 * ms_Kv7 ) * w_Kv7 * s_Kv7 ;
   i_Kv7 = g_Kv7 * ( v - ek ) ;
   }
 _current += i_Kv7;

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
 _slist1[0] = mf_Kv7_columnindex;  _dlist1[0] = Dmf_Kv7_columnindex;
 _slist1[1] = ms_Kv7_columnindex;  _dlist1[1] = Dms_Kv7_columnindex;
 _slist1[2] = s_Kv7_columnindex;  _dlist1[2] = Ds_Kv7_columnindex;
 _slist1[3] = w_Kv7_columnindex;  _dlist1[3] = Dw_Kv7_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/paulo/Documents/Estudos/Ciências/Ciências Naturais/Biologia/Neurociência/LASCON/lascon-project/channels/Kv7.mod";
static const char* nmodl_file_text = 
  "TITLE Kv7.mod   C. Elegans Kv7 current (kqt-3)\n"
  " \n"
  "COMMENT\n"
  "\n"
  "This current is a model for the AWC and RMD neurons in C. Elegans, following the treatment in Nicoletti et al. (2019).\n"
  "\n"
  "Membrane voltage is in absolute mV \n"
  "\n"
  "ENDCOMMENT\n"
  " \n"
  "UNITS {\n"
  "        (mA) = (milliamp)\n"
  "        (mV) = (millivolt)\n"
  "	(S) = (siemens)\n"
  "}   \n"
  "\n"
  "? interface\n"
  "NEURON {\n"
  "        SUFFIX Kv7\n"
  "        NONSPECIFIC_CURRENT i_Kv7\n"
  "        RANGE g_Kv7_bar, g_Kv7, ek\n"
  "        GLOBAL minf_Kv7, winf_Kv7, sinf_Kv7, mstau_Kv7, mftau_Kv7, wtau_Kv7, stau_Kv7\n"
  "        \n"
  "	THREADSAFE : assigned GLOBALs will be per thread\n"
  "}\n"
  " \n"
  "PARAMETER {       \n"
  "        g_Kv7_bar = .000486307 (S/cm2)	<0,1e9>\n"
  "        ek = -80 (mV)\n"
  "}\n"
  " \n"
  "STATE {\n"
  "  \n"
  "        ms_Kv7 mf_Kv7 w_Kv7 s_Kv7  \n"
  "}\n"
  " \n"
  "ASSIGNED {\n"
  "        v (mV)\n"
  "        :-----------------------------------Kv7 channels-----------------------------------------\n"
  "        g_Kv7 (S/cm2)\n"
  "        i_Kv7 (mA/cm2)\n"
  "        minf_Kv7 sinf_Kv7 winf_Kv7 \n"
  "	mstau_Kv7 (ms) \n"
  "        mftau_Kv7 (ms) \n"
  "        stau_Kv7 (ms) \n"
  "        wtau_Kv7 (ms)\n"
  "}\n"
  " \n"
  "? currents\n"
  "BREAKPOINT {\n"
  "        SOLVE states METHOD cnexp\n"
  "        g_Kv7 = g_Kv7_bar*(0.3*mf_Kv7 + 0.7*ms_Kv7)*w_Kv7*s_Kv7\n"
  "	i_Kv7 = g_Kv7*(v - ek) \n"
  "        }\n"
  " \n"
  " \n"
  "INITIAL {\n"
  "	rates(v)\n"
  "        ms_Kv7 = 0.0 :the steady state activation variables are equal for fast and slow m\n"
  "        mf_Kv7 = 0.0\n"
  "        s_Kv7 = sinf_Kv7\n"
  "        w_Kv7 = winf_Kv7\n"
  "}\n"
  "\n"
  "? states\n"
  "DERIVATIVE states {  \n"
  "        rates(v)\n"
  "        mf_Kv7' =  (minf_Kv7-mf_Kv7)/mftau_Kv7\n"
  "        ms_Kv7' =  (minf_Kv7-ms_Kv7)/mstau_Kv7\n"
  "        s_Kv7' = (sinf_Kv7-s_Kv7)/stau_Kv7\n"
  "        w_Kv7' = (winf_Kv7-w_Kv7)/wtau_Kv7\n"
  "}\n"
  " \n"
  "\n"
  "? rates\n"
  "PROCEDURE rates(v(mV)) {  :Computes rate and other constants at current v.\n"
  "                      :Call once from HOC to initialize inf at resting v.\n"
  "        \n"
  "        \n"
  "UNITSOFF :Calculates activation / inactivation variables\n"
  "        minf_Kv7 = 1/(1+exp(-(v-(-12.6726)+10)/15.8008))\n"
  "        mftau_Kv7= (395.3/(1+((v+38.1)/33.59)^2))*0.1\n"
  "        mstau_Kv7= (5503-5345.4/(1+10^((-0.02827)*((-23.9)-v)))-4590.6/(1+10^((-0.0357)*(v+14.15))))*0.1\n"
  "\n"
  "        sinf_Kv7 = 0.34+(0.66/(1+exp((v+45.3)/12.3)))\n"
  "        stau_Kv7 = 5000*0.1\n"
  "        winf_Kv7 = 0.49+(0.51/(1+exp((v+1.084)/28.78)))\n"
  "        wtau_Kv7 = (5.44+(29.2/(1+((v+48.09)/48.83)^2)))*0.1\n"
  "                }\n"
  " \n"
  "FUNCTION vtrap(x,y) {  :Traps for 0 in denominator of rate eqns.\n"
  "        if (fabs(x/y) < 1e-6) {\n"
  "                vtrap = y*(1 - x/y/2)\n"
  "        }else{\n"
  "                vtrap = x/(exp(x/y) - 1)\n"
  "        }\n"
  "}\n"
  " \n"
  "UNITSON\n"
  ;
#endif
