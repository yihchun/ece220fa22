#include <iostream>
#include <cmath>

using namespace std;

class Point {
  float x, y;
public:
  /* constructors */
  Point() { cout << "Default constructor Point " << this << endl; x = y = 0; }
  //Point() { x = y = 0; }
  Point(float x_, float y_) { x = x_; y = y_; }
  ~Point() { cout << "Destroying " << this << endl; }
  /* methods */
  Point &setPointPolar(float r, float theta) {
    x = r*cos(theta); y = r*sin(theta);
    return *this;
  }
  Point &setPointCartesian(float x_, float y_) {
    x = x_; y = y_;
    return *this;
  }
  Point &operator=(const Point &a) {
    x = a.x; y = a.y; return *this;
  }
  void show(ostream &os) const {
    os << "(" << x << ", " << y << ")" << endl;
  }
  float getX() const { return x; }
  float getY() const { return y; }
};

class Shape {
public:
  Shape() {}
  virtual float area() const { cout << "This is a random shape, how am I supposed to know the area?\n"; return 0; }
};

class Rectangle : public Shape {
  Point ll, ur;
public:
  Rectangle(Point ll_, Point ur_) {  ll = ll_; ur = ur_; }
  Rectangle() : ll(), ur() {}
  float area() const { return (ur.getX()-ll.getX())*(ur.getY()-ll.getY()); }
};


void areaPrinter(const Shape &s) {
  cout << "The area of " << &s << " is " << s.area() << endl;
}
/* ostream &operator<<(ostream &os, const char *); */

int main() {
  Point a(1,1);
  Point b(2,3);
  Rectangle r(a,b);
  Point *arr = new Point[5];

  delete [] arr;
  arr = new Point(3,4);
  cout << "Created point " << arr << endl;
  delete arr;
  
  cout << r.area() << endl;
  areaPrinter(r);
  /*
  Point x;
  Point y, z;
  x.setPointPolar(1,0);
  y = (z = x);
  y.show(cout);
  */
  return 0;
}
