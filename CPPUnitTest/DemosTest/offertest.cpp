#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：代码测试模版用于拷贝
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/

SUITE(OfferTest)
{
    class Solution {
    public:
        /**/
        int NumberOf1Between1AndN_Solution(int n)
        {
            int lowNumber = 0;
            int curentNum = 0;
            int hightNumber = 0;
            int count = 0;
            int k = 1;

            while (n >= k) {

                lowNumber = n - (n / k * k);
                hightNumber = n / (k * 10);
                curentNum = (n / k) % 10;
                switch(curentNum) {
                case 0:
                    count += hightNumber * k;
                    break;
                case 1:
                    count += hightNumber * k + lowNumber + 1;
                    break;
                default:
                    count += (hightNumber + 1) * k;
                    break;
                }
                k *= 10;
            }

            return count;
        }
    };

    TEST_FIXTURE(Solution, Normal1)
    {
        int result = NumberOf1Between1AndN_Solution(6);
        CHECK_EQUAL(result, 1);
        result = NumberOf1Between1AndN_Solution(13);
        CHECK_EQUAL(result, 6);
        result = NumberOf1Between1AndN_Solution(1213);
        CHECK_EQUAL(result, 660);
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
