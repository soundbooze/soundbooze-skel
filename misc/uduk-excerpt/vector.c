/**
 * UDUK
 * iherlambang@gmail.com
 *
 */

#include <stdio.h>

typedef double v2df __attribute__ (( vector_size( 16 * sizeof(double)) ));

int
main (int argc, char *argv[])
{
   v2df a, b, c;

   for (long i = 0; i < 16; i++) {
     a[i] = i;
     b[i] = i;
   }
 
   c = a * b;

   for (long i = 0; i < 16; i++) {
     printf("%.4f\n", __builtin_powi(c[i], 3));
    }

   return 0;
}


