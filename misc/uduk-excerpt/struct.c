/**
  * UDUK
  * iherlambang@gmail.com
  *
  */

#include <stdio.h>

typedef double v2df __attribute__ (( vector_size(1*sizeof(double)) ));

typedef struct {
  int a;
  double d;
} foo;

int
main (int argc, char *argv[])
{
   v2df i = {3.01235123413};
   v2df a;

   int c = 0b000110;

   foo delay;
   delay.a = c;
   delay.d = i[0];

   printf("%d %.16f %.4f\n", delay.a, delay.d, __builtin_fabs (i[0]));

   return 0;
}
