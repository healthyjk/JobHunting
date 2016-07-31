// VIrtualTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

using namespace std;

class A {
public:
  int a;
  virtual void test() {}
};

class B  {
public:
  int a;
  virtual void test() {}
};

class C : public  B, public A {
public:
  int c;
  virtual void test() {}
};


int main()
{
  C *c = new C;
  B* a = dynamic_cast<B*>(c);
  cout << c << " " << a << endl;
  system("pause");
	return 0;
}

