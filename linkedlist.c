#include <stdio.h>
#include <stdlib.h>

typedef struct llnode_s {
  int val;
  struct llnode_s *next;
} llnode;

/* insert a value v at the head of a linked list */
void insert_head(llnode **head, int v) {
  llnode *n = malloc(sizeof(llnode));
  n->val = v;
  n->next = *head;
  *head = n;
}

void insert_tail(llnode **head, int v) {
  /* Recursive form:
  if (!*head)
    insert_head(head, v);
  else
    insert_tail(&((*head)->next), v);
  */
  while (*head)
    head = &((*head)->next);
  insert_head(head, v);
}

/* Insert v into the list in sorted order
 * PRE: the list is in increasing order
 * POST: the list is still in increasing order,
 *       but contains the value v one more time
 */
void insert_sorted(llnode **head, int v) {
  while (*head && (*head)->val < v)
    head = &((*head)->next);
  insert_head(head, v);
}

/* removes the first instance of v from the linked list
 * if v is not in the list, returns 0, else returns 1
 */
int delete_from(llnode **head, int v) {
  if (!*head) /* base case #1 */
    return 0;
  if ((*head)->val == v) { /* base case #2 */
    llnode *tmp = *head;
    *head = tmp->next;
    free(tmp);
    return 1;
  }
  return delete_from(&((*head)->next), v);
}

int search(const llnode *head, int v) {
  if (!head) return 0;
  if (head->val == v) return 1;
  return search(head->next, v);
}

void print_list(const llnode *head) {
  if (head == NULL) {
    printf("\n");
  } else {
    printf("%d ", head->val);
    print_list(head->next);
  }
  /*
  for (; head; head = head->next)
    printf("%d ", head->val);
  printf("\n");
  */
}

int main() {
  llnode *head = NULL;
  insert_tail(&head, 5);
  insert_tail(&head, 8);
  insert_tail(&head, 13);
  insert_head(&head, 2);
  print_list(head);
  insert_sorted(&head, 15);
  print_list(head);
  delete_from(&head, 2);
  print_list(head);
  delete_from(&head, 15);
  print_list(head);
  delete_from(&head, 8);
  print_list(head);
}

