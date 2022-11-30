#include <iostream>

template <class T>
class Set {
protected:
  unsigned int count;
public:
  Set() { count = 0; }
  Set(unsigned int x) { count = x; }
  virtual void insert(const T &x) = 0;
};

template <class T>
class LinkedList : public Set<T> {
  class LLNode {
  public:
    LLNode(const T &a) : val(a) { next = NULL; }
    LLNode(const T &a, LLNode *n) : val(a), next(n) { }
    T val;
    LLNode *next;
  };
  class LLIterator : public std::iterator<std::forward_iterator_tag, T> {
    LLNode *node;
  public:
    LLIterator() : node(NULL) { } /* default constructor */
    LLIterator(LLNode *x) : node(x) {} /* constructor used by LinkedList*/
    LLIterator(const LLIterator &x) { node = x.node; } /* copy constructor */
    T &operator*() { return node->val; } /* dereference */
    LLIterator &operator++() { node = node->next; return *this; } /* preincr */
    LLIterator &operator++(int) { /* postincr */
      LLIterator tmp(node);
      node = node->next;
      return tmp;
    }
    /* comparison operators */
    int operator!=(const LLIterator &x) const { return node != x.node; }
    int operator==(const LLIterator &x) const { return node == x.node; }
  };
  LLNode *head;

  void deleteall() {
    LLNode *tmp;
    for (LLNode *walk = head; walk; walk = tmp) {
      tmp = walk->next;
      delete walk;
    }
  }
  void copyfrom(const LinkedList &x) {
    /* copy the linked list from x.head to head */
    LLNode **local = &head;
    for (LLNode *walk = x.head; walk; walk = walk->next) {
      *local = new LLNode(walk->val);
      local = &((*local)->next);
    }
  }
public:
  LinkedList() : Set<T>(0) { head = NULL; }
  LinkedList(const LinkedList &x) : Set<T>(x.count) { copyfrom(x); }
  ~LinkedList() { deleteall(); }
  LinkedList &operator=(const LinkedList &x) {
    this->count = x.count;
    deleteall();
    copyfrom(x);
    return *this;
  }
  void insert(const T &x) {
    this->count++;
    head = new LLNode(x, head);
  }
  LLIterator begin() const {
    LLIterator a(head);
    return a;
  }
  LLIterator end() const {
    LLIterator a;
    return a;
  }
};

template<class T>
std::ostream &operator<<(std::ostream &os, const LinkedList<T> &l);

int main() {
  LinkedList<int> a;
  a.insert(5);
  a.insert(8);
  for (auto it = a.begin(); it != a.end(); ++it) {
    std::cout << *it << std::endl;
  }
}
