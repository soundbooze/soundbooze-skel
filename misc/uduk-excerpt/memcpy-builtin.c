/**
  * UDUK
  * iherlambang@gmail.com
  *
  */
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(void)
{
  double a[6] = {2.001, 4.00, 2.001, 4.00, 112.001, 4.001};
  double *b = calloc(sizeof(a) / sizeof(double), sizeof(double));

  __builtin_memcpy(b, &a[4], 2 * sizeof(double));

  for (int i = 0; i < 6; i++) {
    printf("%.4f\n", b[i]);
  }

  free(b);

  return 0;
}
