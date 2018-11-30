/**
 * UDUK
 * iherlambang@gmail.com
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define FRAME  1024

typedef double v2df __attribute__ (( vector_size( FRAME * sizeof(double)) ));

int
main (int argc, char *argv[])
{
  v2df a, b, c, d, e;

  for (long i = 0; i < FRAME; i++) {
    a[i] = __builtin_sin(drand48());
    b[i] = __builtin_cos(drand48());
  }

  // Horse
  c = a * b;

  // Turtle
  for (long i = 0; i < FRAME; i++) {
      d[i] = a[i] * b[i];
  }

  e = c > d;

  for (long i = 0; i < FRAME; i++) {
    printf("%.4f\n", e[i]);
  }

  return 0;
}
