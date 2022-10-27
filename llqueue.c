#include <stdio.h>
#include <stdlib.h>

typedef struct llnode_s {
  int val;
  struct llnode_s *next;
} llnode;

typedef struct linkedlist_t {
  struct llnode_s *head;
  struct llnode_s *tail;
} ll;

void queue_insert(ll *q, int v) {
  llnode *n = malloc(sizeof(llnode));
  n->val = v;
  n->next = NULL;
  if (q->tail) {
    q->tail->next = n;
  } else {
    q->head = n;
  }
  q->tail = n;
}

int queue_dequeue(ll *q) {
  llnode *tmp = q->head;
  int ret;
  if (!tmp) return 0;
  q->head = tmp->next;
  if (!q->head) {
    q->tail = NULL;
  }
  ret = tmp->val;
  free(tmp);
  return ret;
}

int main() {
  ll q = {NULL, NULL};

  queue_insert(&q, 1);
  queue_insert(&q, 2);
  queue_insert(&q, 3);
  printf("%d\n", queue_dequeue(&q));
  printf("%d\n", queue_dequeue(&q));
  printf("%d\n", queue_dequeue(&q));
  queue_insert(&q, 4);
  queue_insert(&q, 5);
  queue_insert(&q, 6);
  printf("%d\n", queue_dequeue(&q));
  printf("%d\n", queue_dequeue(&q));
  printf("%d\n", queue_dequeue(&q));
  return 0;
}
