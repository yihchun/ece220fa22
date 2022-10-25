#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENT_NAME_LENGTH 1024

enum student_type { UNDERGRADUATE, GRADUATE, NONPROGRAM };

typedef struct student_s {
  char *name;
  enum student_type type;
  int UIN;
  int exam_scores[3];
} student;

/* reads student information from a file
 * order of input from the file is
 * name\nUIN\nscore1 score2 score3\n
 */
void read_student(student *dest, FILE *fp) {
  int i;
  char bob[MAX_STUDENT_NAME_LENGTH+2];
  /* handle the name */
  fgets(bob, MAX_STUDENT_NAME_LENGTH+2, fp);
  for (i=0; bob[i] && bob[i] != '\n'; i++)
    ;
  bob[i] = '\0';
  dest->name = malloc(i+1);
  for (i=0; (dest->name[i] = bob[i]); i++)
    ;
  /* handle the UIN */
  fscanf(fp, "%d", &dest->UIN);
  while (fgetc(fp) != '\n')
    ;
  
  /* handle the exam scores */
  fscanf(fp, "%d %d %d", &dest->exam_scores[0],
	 &dest->exam_scores[1], &dest->exam_scores[2]);
  while (fgetc(fp) != '\n')
    ;
}

int main() {
  unsigned int arr_sz = 1;
  student *students = malloc(sizeof(student) * arr_sz);
  int i;
  /* read students until the uin is 0 */
  for (i=0; ; i++) {
    /* check if array size is big enough */
    if (i >= arr_sz) {
      arr_sz *= 2;
      students = realloc(students, sizeof(student) * arr_sz);
    }
    /* read student using helper function */
    read_student(students+i, stdin);
    /* debug: show the student we just read */
    printf("%s %d %d %d %d\n", students[i].name, students[i].UIN, students[i].exam_scores[0], students[i].exam_scores[1], students[i].exam_scores[2]);
    /* stop when a UIN of 0 is entered */
    if (!students[i].UIN)
      break;
  }
  return 0;
}
