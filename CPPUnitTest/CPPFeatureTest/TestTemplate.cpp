#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>

using namespace std;

/**
  * 测试用例：代码测试模版用于拷贝
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/
SUITE(TemplateTest)
{
    class Solution {
    public:
        int test() {
            return 0;
        }
    };

    TEST_FIXTURE(Solution, Normal1)
    {
        return;
    }

    TEST_FIXTURE(Solution, Normal2)
    {
        return;
    }

    TEST_FIXTURE(Solution, Normal3)
    {
        return;
    }
}
