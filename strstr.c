#include <stdio.h>

char *strstrx(const char *haystack, const char *needle) {
  int i, j;
  for (i=0; haystack[i]; i++) {
    for (j=0; needle[j]; j++) {
      if (haystack[i+j] != needle[j]) break;
    }
    if (needle[j] == '\0')
      return &haystack[i]; /* aka haystack+i */
  }
  return NULL;
}

char *strstry(const char *haystack, const char *needle) {
  int i, j;
  for (i=0; haystack[i]; i++) {
    for (j=0; needle[j] && (haystack[i+j] == needle[j]); j++)
      ;
    if (needle[j] == '\0')
      return &haystack[i]; /* aka haystack+i */
  }
  return NULL;
}

int main() {
  const char *h = "Hello World";
  const char *n = "o W";
  printf("%p %p %p\n", strstrx(h,n), h, &h);
  return 0;
}
    

