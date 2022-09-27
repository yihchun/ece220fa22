#include <stdio.h>

void swap(int *a, int *b) {
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

int main() {
  int a, b;
  scanf("%d%d", &a, &b);
  printf("%d %d\n", a, b);
  swap(&a,&b);
  printf("%d %d\n", a, b);
  return 0;
}  
