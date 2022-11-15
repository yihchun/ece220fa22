#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode node;

struct TreeNode{
	int data;
	node * left;
	node * right;
};

node * newnode(int newData);

void insert(node ** root, int data);

node *search(node *root, int data);
node *searchIter(node *root, int data);
void delete(node **root, int data);

void inOrder(node * root);
void preOrder(node * root);

int main(){
	node * root = NULL;
	insert(&root, 50);
	insert(&root, 5);
	insert(&root, 115);
	insert(&root, 75);
	insert(&root, 85);
	insert(&root, 20);

	printf("\n In order traversal\n");
	inOrder(root);
	printf("\n pre-order traversal\n");
	preOrder(root);

	printf("\n");
	printf("Search for 50: %p %d\n", search(root, 50), search(root, 50)->data);
	printf("Search for 20: %p %d\n", search(root, 20), search(root, 20)->data);
	printf("Search for  0: %p\n", searchIter(root, 0));

	delete(&root, 5);
	delete(&root, 50);
	delete(&root, 0);
	printf("\n In order traversal\n");
	inOrder(root);
	printf("\n");
	return 0;
}

node * newnode(int newData){
	node *new = (node*)malloc(sizeof(node));
	new->data = newData;
	new->left = new->right = NULL;
	return new;
}

void insert(node ** root, int data){
	if (*root == NULL)
	{
		*root = newnode(data);
		return;
	}
	else
	{
		if (data <= (*root)->data)
			insert(&(*root)->left, data);
		else
			insert(&(*root)->right, data);
	}
}

void inOrder(node * root)
{
	if (root == NULL)
		return;
	else
	{
		inOrder(root->left);
		printf(" %d ", root->data);
		inOrder(root->right);
	}
}

void preOrder(node * root)
{
	if (root == NULL)
		return;
	else
	{
		printf(" %d ", root->data);
		preOrder(root->left);
		preOrder(root->right);
	}
}

/* Return a node that has data equal to the data value passed,
 * if it exists in the tree. Otherwise, return NULL.
 */
node *search(node *root, int data) {
  if (root == NULL) return NULL;
  if (root->data == data) return root;
  if (root->data < data)
    return search(root->right, data);
  return search(root->left, data);
}

node *searchIter(node *root, int data) {
  while (root != NULL && root->data != data) {
    if (root->data > data)
      root = root->left;
    else
      root = root->right;
  }
  return root;
}

void delete(node **root, int data) {
  node **walk;
  node *tmp;
  /* search for the node to delete */
  while (*root != NULL && (*root)->data != data) {
    if ((*root)->data > data)
      root = &((*root)->left);
    else
      root = &((*root)->right);
  }
  /* node not found */
  if (*root == NULL)
    return;
  /* delete *root */
  /* 2 children case */
  if ((*root)->left && (*root)->right) {
    for (walk = &((*root)->left); (*walk)->right; walk = &((*walk)->right))
      ;
    (*root)->data = (*walk)->data;
    root = walk;
  }
  /* delete root and it has at most one child */
  tmp = *root;
  if ((*root)->left) {
    /* one child case, left child present */
    *root = (*root)->left;
  } else {
    /* either no children, or only right child present */
    *root = (*root)->right; 
  }
  free(tmp);
}

    
