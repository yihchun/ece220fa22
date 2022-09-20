#include <stdio.h>

int sumton(int n) {
  int tmp;
  if (n <= 1) return n;
  tmp = sumton(n-1);
  return n + tmp;
}

int main() {
  int x;
  scanf("%d", &x);
  printf("Sum to %d is %d\n", x, sumton(x));
}
