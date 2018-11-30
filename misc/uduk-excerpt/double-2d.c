#include <stdio.h>
#include <stdlib.h>

int
main(void)
{

  double **b;
  b = (double **) calloc(10, sizeof(double *));

  for (register int i = 0; i < 10; i++) {
    b[i] = (double *) calloc(2, sizeof(double));
    b[i][0] = 0.1;
    b[i][1] = 0.2;
  }

  for (register int i = 0; i < 10; i++) {
    for (register int j = 0; j < 2; j++) {
      printf("%.2f\n", b[i][j]);
    }
  }

  for (register int i = 0; i < 10; i++) {
    free(b[i]);
  }

  free(b);

  return 0;
}
