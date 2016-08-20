#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

/**
  * 测试用例：hihocoder 20160807 编程挑战赛 练习题解答
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/
SUITE(HihoCoder0807Test)
{
    class Solution {
    public:
        int DiscountMoney(int n, int x, vector<int> prices) {
            int current = 0;
            for (int i = 0; i < n; ++i) {
                current += prices[i];
            }
            if (current < x) {
                return -1;
            }
            int result = INT_MAX;
            int MaxKind = 1 << n;
            for (int i = 0; i < MaxKind; ++i) {
                current = 0;
                //将i看成20位的二进制数字，i的每一位代表第j个数是否选中
                for (int j = 0; j < n; ++j) {
                    if (((1 << j) & i) != 0) {
                        current += prices[j];
                        if (current >= x) {
                            break;
                        }
                    }
                }

                if (current >= x && current < result) {
                    result = current;
                }
            }
            return result;
        }
    };

    TEST_FIXTURE(Solution, DiscountMoney_cin)
    {
        ifstream cin("input_hihocoder0807.txt");
        int n, x;
        cin >> n >> x;
        vector<int> prices(n);

        for (int i = 0; i < n; ++i) {
            cin >> prices[i];
        }
        int result = DiscountMoney(n, x, prices);
        CHECK_EQUAL(53, result);
    }

    TEST_FIXTURE(Solution, DiscountMoney_scanf)
    {
        //使用freopen 在文件不存在时会提示异常
        freopen("input_hihocoder0807.txt", "r", stdin);

        int n, x;
        scanf("%d%d", &n, &x);
        vector<int> prices(n);

        for (int i = 0; i < n; ++i) {
            scanf("%d", &prices[i]);
        }
        int result = DiscountMoney(n, x, prices);
        fclose(stdin);
        CHECK_EQUAL(53, result);
        return;
    }

    TEST_FIXTURE(Solution, Normal3)
    {
        return;
    }
}
