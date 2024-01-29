#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;
#if defined(__cplusplus)
extern "C" {
#endif

extern void _Kv3_reg(void);
extern void _Kv4_reg(void);
extern void _Kir_reg(void);
extern void _Kvs1_reg(void);
extern void _Kv7_reg(void);
extern void _Kv10_reg(void);
extern void _Cav1_reg(void);
extern void _Cav2_reg(void);
extern void _Cav3_reg(void);

void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"Kv3.mod\"");
    fprintf(stderr, " \"Kv4.mod\"");
    fprintf(stderr, " \"Kir.mod\"");
    fprintf(stderr, " \"Kvs1.mod\"");
    fprintf(stderr, " \"Kv7.mod\"");
    fprintf(stderr, " \"Kv10.mod\"");
    fprintf(stderr, " \"Cav1.mod\"");
    fprintf(stderr, " \"Cav2.mod\"");
    fprintf(stderr, " \"Cav3.mod\"");
    fprintf(stderr, "\n");
  }
  _Kv3_reg();
  _Kv4_reg();
  _Kir_reg();
  _Kvs1_reg();
  _Kv7_reg();
  _Kv10_reg();
  _Cav1_reg();
  _Cav2_reg();
  _Cav3_reg();
}

#if defined(__cplusplus)
}
#endif
