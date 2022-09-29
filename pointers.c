#include <stdio.h>

/* C's type system adds a pointer type for every existing type:
 * e.g., for int type, pointer to integer is called int *
 * e.g., for char type, pointer to char is called char *
 * e.g., for int * type, pointer to an int* is called int **
 *
 * Two unary (one operand) operators:
 *   unary * takes a pointer and turns it into that value (can be lvalue)
 *   unary & takes a locator-value and turns it into a pointer
 * e.g., &2 is not a legal expression, because 2 is not an lvalue.
 *
 * Special name: NULL pointer to the address 0
 * has a "special meaning" because things don't normally have address 0
 * used to convey "i don't care" or error conditions or other special cases
 * Note: do not confuse NULL, the pointer, with nul or \0, the null terminator
 * for strings
 * NULL is a void * <- pointer to nothing
 * \0 is char
 */

/* inputs to sort3 are signed integers,
 * and sort3 permutes them such that *a <= *b <= *c
 */
void sort3(int *a, int *b, int *c) {
  int tmp;
  if (*a > *b) {
    tmp = *a;
    *a = *b;
    *b = tmp;
  }
  /* We now know that *a <= *b */
  if (*b > *c) {
    tmp = *b;
    *b = *c;
    *c = tmp;
  }
  /* We know that *a <= *c and *b <= *c. IOW *c is correct */
  if (*a > *b) {
    tmp = *a;
    *a = *b;
    *b = tmp;
  }
}

/* provide 3-5 pointers to integers, those will be sorted, and if you don't
 * have 5 pointers to pass, make e (and possibly d) NULL to indicate that
 * you don't want those values sorted
 */
void sort5(int *a, int *b, int *c, int *d, int *e) {
}

int main() {
  int a, b, c;
  while (1) {
    scanf("%d %d %d", &a,&b,&c);
    printf("%d %d %d\n", a,b,c);
    sort3(&a,&b,&c);
    printf("%d %d %d\n", a,b,c);
  }
  return 0;
}
