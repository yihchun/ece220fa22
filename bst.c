#include <stdio.h>
#include <stdlib.h>

typedef struct bstnode_t {
  int val;
  struct bstnode_t *left;
  struct bstnode_t *right;
} bstnode;

/* searches the bstnode specified in root for the value v.
 * returns a pointer to a node with value v if such a node exists.
 * otherwise, returns NULL
 * PRE: root and all descedents follow the binary search tree property
 *      [1. no loops] [2. <= goes left, >= goes right]
 */
bstnode *bst_search(bstnode *root, int v) {
  if (!root) return NULL; /* Base Case: nothing to search for */
  if (root->val == v) return root; /* Other base case: found it */
  if (root->val > v)
    return bst_search(root->left, v);
  return bst_search(root->right, v);
}

bstnode *bst_search_iter(bstnode *root, int v) {
  while (root && root->val != v) {
    if (root->val > v)
      root = root->left;
    else
      root = root->right;
  }
  return root;
}

void bst_insert(bstnode **root, int v) {
  if (*root == NULL) { /* base case */
    *root = malloc(sizeof(bstnode));
    (*root)->val = v;
    (*root)->left = (*root)->right = NULL;
    return;
  }
  if ((*root)->val > v)
    return bst_insert(&((*root)->left), v);
  return bst_insert(&((*root)->right), v);
}

void bst_insert_iter(bstnode **root, int v) {
  while (*root != NULL) {
    if ((*root)->val > v)
      root = &((*root)->left);
    else
      root = &((*root)->right);
  }
  *root = malloc(sizeof(bstnode));
  (*root)->val = v;
  (*root)->left = (*root)->right = NULL;
}

/* PRE: root has a right child */
bstnode **bst_next(bstnode *root) {
  bstnode **walk;
  for (walk = &root->right; (*walk)->left; walk = &((*walk)->left))
    ;
  return walk;
}

void bst_delete_iter(bstnode **root, int v) {
  bstnode *tmp;
  bstnode **walk;
  while (*root != NULL && (*root)->val != v) {
    if ((*root)->val > v)
      root = &((*root)->left);
    else
      root = &((*root)->right);
  }
  if (*root == NULL)
    return;
  
  if ((*root)->left && (*root)->right) {
    for (walk = &((*root)->right); (*walk)->left; walk = &((*walk)->left))
      ;
    (*root)->val = (*walk)->val;
    root = walk;
  }
  tmp = *root;
  if ((*root)->left)
    *root = (*root)->left;
  else
    *root = (*root)->right;
  free(tmp);
  
  /*
  tmp = *root;
  if ((*root)->left == NULL) {
    *root = (*root)->right;
    free(tmp);
    return;
  }
  if ((*root)->right == NULL) {
    *root = (*root)->left;
    free(tmp);
    return;
  }
  for (walk = &((*root)->right); (*walk)->left; walk = &((*walk)->left))
    ;
  (*root)->val = (*walk)->val;
  tmp = *walk;
  *walk = (*walk)->right;
  free(tmp);
  */
}
  
void bst_delete(bstnode **root, int v) {
  bstnode *tmp;
  bstnode **walk;
  if (!*root) return;
  if ((*root)->val == v) {
    /* if there are no children, just free it */
    if ((*root)->left == NULL &&
	(*root)->right == NULL) {
      free(*root);
      *root = NULL;
      return;
    }
    /* if there is only a left child */
    if ((*root)->right == NULL) {
      tmp = (*root)->left;
      free(*root);
      *root = tmp;
      return;
    }
    /* if there is only a right child */
    if ((*root)->left == NULL) {
      tmp = (*root)->right;
      free(*root);
      *root = tmp;
      return;
    }
    /* get the in-order next node from our current node */
    walk = bst_next(*root);
    /* swap the values in root and walk */
    (*root)->val = (*walk)->val;
    /* delete *walk */
    tmp = (*walk)->right;
    free(*walk);
    *walk = tmp;
    return;
  }
  if ((*root)->val > v)
    return bst_delete(&((*root)->left), v);
  bst_delete(&((*root)->right), v);
}

/* traverse the list in-order and print the elements */
void bst_traverse(const bstnode *root) {
  if (!root) return;
  bst_traverse(root->left);
  printf("%d %p %p %p\n", root->val, root, root->left, root->right);
  bst_traverse(root->right);
}

int main() {
  bstnode *root = NULL;
  bst_insert(&root, 5);
  bst_insert(&root, 2);
  bst_insert(&root, 1);
  bst_insert(&root, 3);
  bst_insert(&root, 7);
  bst_insert(&root, 6);
  bst_insert(&root, 8);
  bst_insert(&root, 0);
  bst_traverse(root);
  bst_delete_iter(&root, 1);
  bst_traverse(root);
  
}
