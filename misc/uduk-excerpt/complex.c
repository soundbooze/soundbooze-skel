#include <stdio.h>
#include <complex.h>
#include <math.h>

int
main (int argc, char *argv[])
{
  double complex z1 = 1.00923 + 3.0 * I;
  double complex z2 = 2.001 - 3.0 * I;

  printf("Z1 = %.2f + %.2fi\tZ2 = %.2f %+.2fi\n", creal(z1), cimag(z1), creal(z2), cimag(z2));

  double complex sum = z1 + z2;
  printf("Z1 + Z2 = %.2f %+.2fi\n", creal(sum), cimag(sum));

  double complex conjugate = conj(z1);
  printf("conjugate of Z1 = %.2f %+.2fi\n", creal(conjugate), cimag(conjugate));

  return 0;
}
