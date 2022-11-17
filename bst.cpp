#include <iostream>

class BST<class T> {
  class Node {
  public:
    T val;
    BST *left;
    BST *right;
    Node(const T &x) { val = x; left = right = NULL; }
  };
}
