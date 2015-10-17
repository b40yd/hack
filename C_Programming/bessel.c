#include <math.h>
#include <libguile.h>
SCM j0_wrapper(SCM x){
  return scm_make_real(j0 (scm_num2dbl (x,"j0")));
}

void init_bessel(){
  scm_c_define_gsubr("j0",1,0,0,j0_wrapper);
}
