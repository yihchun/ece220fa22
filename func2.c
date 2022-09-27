#include <stdio.h>

int multiply(int a, int b) {
  int tmp = a*b;
  return tmp;
}

int factorial(int n) {
  int i, accum = 1;
  for (i=1; i<=n; i++) {
    accum = multiply(accum, i);
  }
  return accum;
}

int main() {
  int x;
  scanf("%d", &x);
  printf("%d! = %d\n", x, factorial(x));
  return 0;
}
