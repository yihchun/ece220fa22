#include <stdio.h>

int dotproduct(int a[], int b[], unsigned int n) {
  int sum = 0;
  int i;
  
  for (i=0; i<n; i++) {
    sum += a[i]*b[i];
  }

  return sum;
}

int main() {
  int x[3] = {10, 3, 40};
  int y[3] = {21, 32, 85};

  printf("%d\n", dotproduct(x,y,128));
}
