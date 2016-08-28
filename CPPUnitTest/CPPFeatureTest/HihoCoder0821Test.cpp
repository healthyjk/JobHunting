#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：代码测试模版用于拷贝
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/
SUITE(HiHocoder0821Test)
{
    class Solution {
    public:
        /* 题目描述：一只木桶能盛多少水，并不取决于桶壁上最高的那块木板，而恰恰取决于桶壁上最短的那块。
         * 已知一个木桶的桶壁由N块木板组成，第i块木板的长度为Ai。
         * 现在小Hi有一个快捷修补工具，每次可以使用修补工具将连续的不超过L块木板提高至任意高度。
         * 已知修补工具一共可以使用M次(M*L<N)，如何修补才能使最短的那块木板最高呢？
         * 注意: 木板是环形排列的，第N-1块、第N块和第1块也被视为连续的。
         * 解题思路: 二分枚举法；
         * 收获的经验： 有时候遇到问题要反向思考，看看能不能从结果来推导原因；*/
        int RepairBucket(int n, int m, int l, vector<int>& height) {

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
