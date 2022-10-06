#include <stdio.h>

#define TYPE int
void matrixmult2(TYPE **d, const TYPE **x, const TYPE **y, int xw, int xh, int yw) {
    int i,j,k;
  TYPE sum;
  /* d is of size xh x yw */
  for (i=0; i<xh; i++) {
    for (j=0; j<yw; j++) {
      sum = 0;
      for (k=0; k<xw; k++) {
	sum += x[i][k] * y[k][j];
      }
      d[i][j] = sum; /* d[i][j] -> d[i*yw + j] */
    }
  }
}

  
void matrixmult(TYPE *d, const TYPE *x, const TYPE *y, int xw, int xh, int yw) {
  int i,j,k;
  TYPE sum;
  /* d is of size xh x yw */
  for (i=0; i<xh; i++) {
    for (j=0; j<yw; j++) {
      sum = 0;
      for (k=0; k<xw; k++) {
	sum += x[i*xw + k] * y[k*yw + j]; /* multiply x[i][k] * y[k][j] */
	printf("Multiplying %d(%d,%d) and %d(%d,%d)\n", x[i*xw+k], i, k, y[k*yw+j], k, j);
      }
      d[i*yw+j] = sum; /* d[i][j] -> d[i*yw + j] */
    }
  }
}

int main() {
  TYPE a[2][3] = {{1,2,3},{4,5,6}};
  TYPE b[3][2] = {{7,8},{9,10},{11,12}};
  TYPE d[2][2] = {0};
  int i;
  matrixmult(&d[0][0], &a[0][0], &b[0][0], 3, 2, 2);
  matrixmult2(d,a,b,3,2,2);
  for (i=0; i<4; i++)
    printf("%d\n", d[0][i]); /* <- don't do this unless we tell you to in the MP */
  return 0;
}
