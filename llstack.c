#include <stdio.h>
#include <stdlib.h>

typedef struct llnode_s {
  int val;
  struct llnode_s *next;
} llnode;

typedef llnode *llstack;
#define INITIAL_LLSTACK_VALUE NULL

void push(llstack *s, int v) {
  llnode *n = malloc(sizeof(llnode));
  n->val = v;
  n->next = *s;
  *s = n;
}

int pop(llstack *s) {
  llnode *n = *s;
  int v;
  if (!n) return 0;
  *s = n->next;
  v = n->val;
  free(n);
  return v;
}

int stack_calculate(const char *s) {
  llstack stack = INITIAL_LLSTACK_VALUE;
  int tmp, tmp2;

  while (*s) {
    if (*s >= '0' && *s <= '9') {
      tmp = 0;
      while (*s >= '0' && *s <= '9') {
	tmp = tmp*10 + *s - '0';
	s++;
      }
      push(&stack, tmp);
    } else if (*s == '+') {
      tmp = pop(&stack);
      tmp2 = pop(&stack);
      push(&stack, tmp+tmp2);
      s++;
    } else if (*s == '-') {
      tmp = pop(&stack);
      tmp2 = pop(&stack);
      push(&stack, tmp2-tmp);
      s++;
    } else if (*s == '*') {
      tmp = pop(&stack);
      tmp2 = pop(&stack);
      push(&stack, tmp*tmp2);
      s++;
    } else if (*s == '/') {
      tmp = pop(&stack);
      tmp2 = pop(&stack);
      push(&stack, tmp2/tmp);
      s++;
    } else if (*s == '%') {
      tmp = pop(&stack);
      tmp2 = pop(&stack);
      push(&stack, tmp2%tmp);
      s++;
    } else if (*s == ' ') {
      s++;
    }
  }
  return pop(&stack);
}


int main() {
  llstack s = INITIAL_LLSTACK_VALUE;
  push(&s, 3);
  push(&s, 5);
  printf("%d\n", pop(&s));
  printf("%d\n", pop(&s));
  printf("%d\n", pop(&s));
  printf("%d\n", stack_calculate("10 1 2 + -"));
}
