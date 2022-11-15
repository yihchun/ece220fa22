#include <iostream>

//using namespace std;

class twodvec {
  int x, y;
public:
  twodvec(int _x, int _y) { x = _x; y = _y; }
  twodvec() { x = y = 0; }
  ~twodvec() { std::cout << "cleaning up " << this << std::endl; }
  twodvec operator+(const twodvec &b) {
    twodvec ret(x + b.x, y + b.y);
    return ret;
  }
  int getX() { return x; }
  int getY() { return y; }
};

int main() {
  twodvec a(1,0);
  twodvec b(0,1);
  twodvec c = a+b;
  std::cout << c.getX() << " " << c.getY() << std::endl;
}
