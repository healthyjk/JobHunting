#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include "Singleton.hpp"

using namespace std;

/**
  * 测试用例：代码测试模版用于拷贝
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/

SUITE(SingleTonTest)
{

    TEST(SingleTonTest1)
    {
        string test("hello");
        string* single1 = TemplateSingleTon<string>::instance(test);
        string* single2 = TemplateSingleTon<string>::getInstance();
        CHECK_EQUAL(single1, single2);
        TemplateSingleTon<string>::destoryInstance();
        single1 = TemplateSingleTon<string>::getInstance();
        return;
    }

    TEST(SingleTonTest2)
    {
        SingleTon_Lazy1* single1 = SingleTon_Lazy1::getInstance();
        SingleTon_Lazy1* single2 = SingleTon_Lazy1::getInstance();
        CHECK_EQUAL(single1, single2);
        //SingleTon_Lazy1::destoryInstance();
    }

    TEST(SingleTonTest3)
    {
        SingleTon_Lazy2* single1 = SingleTon_Lazy2::getInstance();
        SingleTon_Lazy2* single2 = SingleTon_Lazy2::getInstance();
        CHECK_EQUAL(single1, single2);
    }

    TEST(SingleTonTest4)
    {
        const SingleTon_Hungry* single1 = SingleTon_Hungry::getInstance();
        const SingleTon_Hungry* single2 = SingleTon_Hungry::getInstance();
        CHECK_EQUAL(single1, single2);
        SingleTon_Hungry::destoryInstance();
    }
}
