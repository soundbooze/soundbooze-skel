#include <stdio.h>
#include <math.h>

int
main(int argc, char *argv[])
{
  double c, s;
  double r = 30 * M_PI / 180;

  __asm__ __volatile__ ("fsincos" : "=t" (c), "=u" (s) : "0" (r));
  printf("%.4f %.4f\n", c, s); 
  
  return 0;
}
