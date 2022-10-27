#include <stdio.h>
#include <stdlib.h>

typedef struct llnode_s {
  int val;
  struct llnode_s *next;
} llnode;

/* insert a value v at the head of a linked list */
void queue_insert(llnode **head, int v) {
  llnode *n = malloc(sizeof(llnode));
  n->val = v;
  n->next = *head;
  *head = n;
}

int dequeue(llnode **head) {
  llnode *tmp;
  int ret;
  if (!*head) return 0; /* queue is empty */
  while ((*head)->next)
    head = &((*head)->next);
  tmp = *head;
  *head = NULL;
  ret = tmp->val;
  free(tmp);
  return ret;
}

int main() {
  llnode *head = NULL;

  queue_insert(&head, 1);
  queue_insert(&head, 2);
  queue_insert(&head, 3);
  printf("%d\n", dequeue(&head));
  printf("%d\n", dequeue(&head));
  printf("%d\n", dequeue(&head));
  return 0;
}
