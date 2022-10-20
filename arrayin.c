#include <stdio.h>
#include <stdlib.h>

/* gets an array of length size from the user
 * PRE: size >= 0
 * POST: returns a pointer to a dynamically allocated array of integers
 *       of length least size, filled with values taken from user input.
 *       the caller is responsible for free()ing the returned pointer.
 */
int *get_array_from_user(long size) {
  int i;
  int *array;
  printf("Please give me %ld values:\n", size);
  array = malloc(sizeof(int) * size);
  if (array == NULL) return NULL;
  for (i=0; i<size; i++) {
    scanf("%d", array+i);
  }
  return array;
}

int main() {
  long size, i;
  int *tmp;
  printf("How many values do you have for me?\n");
  scanf("%ld", &size);
  tmp = get_array_from_user(size);
  if (tmp == NULL) {
    fprintf(stderr, "Sorry, I couldn't get space from the malloc-beast\n");
    return 1;
  }
  for (i=0; i<size; i++)
    printf("%d ", tmp[i]);
  printf("\n");
  free(tmp);
  return 0;
}
