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
        /*小于n的数中1出现的个数*/
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

        /*题目描述：把只包含因子2、3和5的数称作丑数（Ugly Number）。例如6、8都是丑数，但14不是，
         * 因为它包含因子7。 习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。*/
        /*主要解题思想：在数组中必定有一个丑数M2， 在它之前的数 * 2 都小于当前最大丑数， 在它之后的数 * 2都大于当前最大丑数， 同样有M3, M5；
         * 显然，当前位置的下一个数肯定是之前某个位置的数*2、*3、*5的结果，这3个数要比当前位置的数大才能候选，选的时候选3个数里面最小的那个，
         * 有人说这还用比吗，一定是*2最小，如果是同一个数*2*3*5肯定是*2的最小，但是这个“某个位置的数”是不同的，*5的数可能因为更靠前而比*2的数小。
         * 现在要做的就是把“某个位置”记住，对于*2、*3、*5分别有一个位置满足各自位置的数*2、*3、*5刚好大于当前位置的数，
         * 所谓“刚好”的意思就是各自“某个位置”前一个位置的数*2、*3、*5小于当前数。*/
        int GetUglyNumber_Solution(int index) {
                if (index < 7) return index;
                vector<int> num(index);
                num[0] = 1;
                int t2 = 0;
                int t3 = 0;
                int t5 = 0;
                for (int i = 1; i < index; ++i) {
                    //LOG(INFO) << "t2 = " << t2 << ", t3 = " << t3 << ", t5 = " << t5;
                    //LOG(INFO) << "min(" << (num[t2] * 2) << ", " << (num[t3] * 3) << ", " << (num[t5] * 5) << ")";
                    num[i] = std::min(num[t2] * 2, num[t3] * 3);
                    num[i] = std::min(num[i], num[t5] * 5);
                    if (num[i] == num[t2] * 2) t2++;
                    if (num[i] == num[t3] * 3) t3++;
                    if (num[i] == num[t5] * 5) t5++;
                    //LOG(INFO) << "i = " << i << ", num = " << num[i];
                }
                return num[index - 1];
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
        GetUglyNumber_Solution(20);
        return;
    }

    TEST_FIXTURE(Solution, Normal3)
    {
        return;
    }
}
