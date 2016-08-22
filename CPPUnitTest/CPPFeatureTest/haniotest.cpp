#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include <string>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：汉诺塔游戏
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/
SUITE(HanioTest)
{
    class Solution {
    public:
        int move(int n, const string& from, const string& to) {
            //LOG(INFO) << "move " << n << " from " << from << " to " << to << endl;
            return 1;
        }

        //普通的汉诺塔，三根柱子
        int hanio_normal(int n, const string& left, const string& mid, const string& right) {
            if (n == 1) {
                return move(n, left, right);
            } else {
                int step1 = hanio_normal(n-1, left, right, mid);
                int step2 = move(n, left, right);
                int step3 = hanio_normal(n-1, mid, left, right);
                return step1 + step2 + step3;
            }
        }

        //汉诺塔规则修改：不允许直接从最左边移动到最右边或者从最右边移动到最左边，必须经过中间
        int hanio_special_1(int n, const string& left, const string& mid, const string& right) {

            return 0;
        }
    };

    TEST_FIXTURE(Solution, Normal1)
    {
        int result = hanio_normal(3, "left", "mid", "right");
        CHECK_EQUAL(7, result);
        return;
    }

    TEST_FIXTURE(Solution, Normal2)
    {

        return;
    }
}
