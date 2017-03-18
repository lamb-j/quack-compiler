#include <iostream>

class A {
  public:
  int tmp(int x)
  {
    x = 56;

    return x;
  }

};

int main() {

  A a;

  std::cout << a.tmp(3);
}
