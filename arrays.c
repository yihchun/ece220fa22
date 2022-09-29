#include <stdio.h>

/* arrays are contiguous allocations of homogenous data types
 * another extension to the type system: int -> int[303]
 * operator[] takes an array and gives you the ith element of that array
 *  arrays are zero indexed so scores[0] is the first element
 */

/* pointer-array duality
 * if a function takes a pointer, you can also pass an array identifier
 * in general, you can use an array name like a pointer (with limitations)
 * also, you can index a pointer as if it were an array
 *   a+i (where a is a pointer type) === &a[i]
 *   *(a+i)  (where a is a pointer type) === a[i]
 * Limitations: array identifier cannot change
 *   int *x; x++ is perfectly valid
 *   int x[5]; x++ is not valid
 */
#define NUM_STUDENTS 303

int sumarray(int s[10], int n) {
  int i, sum;
  for (sum=i=0; i<n; i++)
    sum += s[i]; /* pointer used like an array */
  s[0]++;
  return sum;
}

int main() {
  int scores[NUM_STUDENTS] = { 99, 94, 90, 92, 81, 85, 25 };
  int sum;
  int i;
  /*
  sum = 0;
  for (i=0; i<NUM_STUDENTS; i++)
    sum += scores[i];
  */
  printf("The sum of scores is %d\n", sumarray(scores, 10)); /* array as a pointer */
  printf("The sum of scores is %d\n", sumarray(scores, 10)); /* array as a pointer */
  return 0;
}
