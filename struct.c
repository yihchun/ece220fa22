#include <stdio.h>

enum student_type { UNDERGRADUATE, GRADUATE, NONPROGRAM };
enum bad_variable_names { FOO = 3, BAR, BAZ };
typedef struct student_s {
  char name[128];
  enum student_type type;
  int UIN;
  int lowest_grade;
  int highest_grade;
  int exam_scores[3];
} student;

typedef union data_representation {
  int i;
  float f;
  void *p;
  char c;
} data_rep;

int main() {
  student me = {"Yih-Chun Hu", FOO, 12345678, 0, 1, {0,0,1}};
  data_rep pi;
  pi.f = 3.14159;
  switch (me.type) {
  case UNDERGRADUATE: printf("We found an undergrad\n"); break;
  case GRADUATE: printf("Why are you still in school?\n"); break;
  case NONPROGRAM: printf("You're not even getting a degree?!\n"); break;
  default: printf("This seems to be an invalid type\n");
  }
    
  printf("Test: %s %d %d %d %d\n", me.name, me.type, me.UIN, me.lowest_grade, me.highest_grade);
  printf("%d %f %p %c\n", pi.i, pi.f, pi.p, pi.c);
  return 0;
}
