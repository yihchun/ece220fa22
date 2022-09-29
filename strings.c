#include <stdio.h>

/* a string is an array of characters with a null terminator.
 * a literal string ("some stuff") is supposed to be constant
 *    (implementation defined if you try to change the values inside of it)
 *    of type const char *
 * const qualifier means that the thing doesn't change
 * two possible meanings for const pointer:
 *   either pointer doesn't change or contents don't change
 * const type * <- means that contents don't change
 * type * const <- means that the pointer doesn't change
 * const type * const <- means that neither the pointer nor the contents change
 */

int mystrlen(const char *s) {
  int len = 0;
  for (;*s;s++) {
    len++;
  }
  return len;
}

/* look for first instance of character c in string s
 * returns a pointer to the first instance
 * if no instance, returns NULL
 */
const char *mystrchr(const char *s, char c) {
  for (;*s;s++) {
    if (*s == c)
      return s;
  }
  return NULL;
}

int main() {
  const char *str = "hello world\n";
  printf("%s", str);
  printf("%d\n", mystrlen(str));
  printf("%s", mystrchr(str, 'w'));
  const char *x = mystrchr(str, 'z');
  printf("%p\n", x);
  return 0;
}
