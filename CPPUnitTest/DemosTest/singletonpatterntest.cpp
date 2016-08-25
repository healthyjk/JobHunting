#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include "singleton.hpp"

using namespace std;

/**
  * 测试用例：代码测试模版用于拷贝
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/

SUITE(SingleTonTest)
{
    class Solution {
    public:
        int test() {
            a = 1;
            return a;
        }
    private:
        int a ;
    };

    TEST(SingleTonTest1)
    {
        SingleTon<Solution, int>* single1 = SingleTon<Solution, int>::getInstance();
        SingleTon<Solution, int>* single2 = SingleTon<Solution, int>::getInstance();
        CHECK_EQUAL(single1, single2);
        return;
    }

    TEST(SingleTonTest2)
    {

        return;
    }

    TEST(SingleTonTest3)
    {

        return;
    }
}
