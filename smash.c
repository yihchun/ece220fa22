#include <stdio.h>
#include <string.h>

int stringanalysis(const char *s) {
  char buf[128] = {0};
  int i, sum = 0;
  strcpy(buf, s);
  for (i=1; i<128; i++)
    buf[i-1] -= buf[i];
  for (i=0; i<128; i++)
    sum += buf[i];
  return sum;
}

int main() {
  char *s = "hello worldfdashjh3oi4hiuewailury2lhuiafdslhiuadsfhiludfsahluadfslhuasdfhjkldsafjkbadfshjkldsafhjkladsfhjdfsahjdsafhjhuerwyy79rhlquw3hjkdsabhkcdsghighiluadshilufdhluadsfhlufasdhluasdfhusadfhhjlkdsafjkhlfsadlhasdf";
  
  printf("%d\n", stringanalysis(s));
}
