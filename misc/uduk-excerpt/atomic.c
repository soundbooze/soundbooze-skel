/**
  * UDUK
  * iherlambang@gmail.com
  *
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main (int argc, char *argv[])
{
  
  double a = 0.1111;
  double *x = &a;
  double *z = __atomic_load_n (&x, __ATOMIC_RELAXED);
  double *w;

  __atomic_store_n (&w, z, __ATOMIC_RELAXED);

  printf("%.4f %.4f \n", *z, *w);

  return 0;
}

