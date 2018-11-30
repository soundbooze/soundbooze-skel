#include <stdio.h>
#include <math.h>

#define min(x, y) ({        \
    typeof(x) _min1 = (x);      \
    typeof(y) _min2 = (y);      \
    (void) (&_min1 == &_min2);    \
    _min1 < _min2 ? _min1 : _min2; })

#define max(a,b) \
  ({ typeof (a) _a = (a); \
   typeof (b) _b = (b); \
   _a > _b ? _a : _b; })
int
main()
{
  double a = 4.001;
  double b = 3.002;

  printf("%.4f %.4f\n", max(a, b), min(a, b));
}
