#include <stdio.h>
#include <stdlib.h>

typedef struct twodvec_t {
  int x, y;
} twodvec;

twodvec twodvec_add(twodvec a, twodvec b) {
  twodvec name = {a.x + b.x, a.y + b.y};
  return name;
}

int main() {
  struct twodvec_t a = {1,0};
  struct twodvec_t b = {0,1};
  struct twodvec_t c = twodvec_add(a,b);
  printf("%d %d\n", c.x, c.y);
}
