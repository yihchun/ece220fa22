#include <iostream>

using namespace std;

class Foo {
public:
  virtual void func() const { cout << "I'm a foo\n"; }
};

class Bar : public Foo {
public:
  virtual void func() const { cout << "I'm a bar\n"; }
};

class Baz : public Foo {
public:
  virtual void func() const { cout << "I'm a baz\n"; }
};

class Pear {
public:
  virtual void zzz() const { }
};

class Hello : public Foo, public Pear {
public:
  void zzz() const { cout << "Hello Pear\n"; }
  void func() const { cout << "I'm a Pear\n"; }
};



void showType(const Foo &a) {
  a.func();
}

Baz x;
int main() {
  showType(x);
}
