#include <stdio.h>
#include <math.h>

double f(double x) {
  return sin(x);
}

int main() {
  double a, b, dx, x, sum;

  scanf("%lf%lf%lf", &a, &b, &dx);
  printf("%lf %lf %lf\n", a, b, dx);

  sum = 0;
  for (x=a; x<b; x+=dx) {
    if (x+dx > b) {
      /* calculate the area of the rectangle with x from x to b */
      sum += f(x)*(b-x);      
    } else {
      /* calculate the area of the rectangle with x from x to x+dx */
      sum += f(x)*dx;
    }
  }
  printf("The integral is approximately %lf\n", sum);
  return 0;
}



