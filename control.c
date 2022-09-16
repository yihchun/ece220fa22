#include <stdio.h>

int add3(int a, int b, int c) {
  return a+b+c;
}

int main() {
  int x;
  float y;
  int a, b, c;
  int valid;

  a = 3.1415f;
  valid = scanf("%d %d %d", &a, &b, &c);
  if (valid == 3)
    printf("%d+%d+%d=%d\n", a,b,c, add3(a,b,c));
  else
    printf("Sorry, you're supposed to give me three decimal integers separated by spaces.\n");
  return 0;

  scanf("%f", &y);
  printf("You told us %.20f\n", y);
  return 0;

  for (x=1; x<=10; x++) {
    printf("%d\n", x);
  }

  x=1;
  while (x<=10) {
    printf("%d\n", x++);
  }

  x=1;
  do {
    printf("%d\n", x++);
  } while (x<11);
  return 0;
}
  
  
