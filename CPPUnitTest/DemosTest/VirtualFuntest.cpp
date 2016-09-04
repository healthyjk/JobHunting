#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：测试虚函数的特性
  * 作者：yanjiankang
  * 时间：2016年9月3日
  **/

SUITE(VirtualFunTest)
{

    /*测试析构函数是否为虚函数的影响*/
    class A1 {
    public:
        virtual ~A1() { LOG(INFO) << "deconstructe A1"; }
        virtual void doSomething() { LOG(INFO) << "do something of A1..." ; }
    };

    class B1 : public A1 {
    public:
        ~B1() { LOG(INFO) << "deconstructe B1"; }  /*不声明为虚函数时，父类指针指向子类对象时delete父类指针不会调用*/
        virtual void doSomething() { LOG(INFO) << "do something of B1..." ; }
    };

    TEST(Normal1)
    {
        A1* a1 = new B1();
        a1->doSomething();
        delete a1;
        return;
    }
}
