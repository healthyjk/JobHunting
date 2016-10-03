#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：代码测试模版用于拷贝
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/

SUITE(TempTest)
{
    class Solution {
    public:
        int combinationSum4(vector<int>& nums, int target) {
            int n = nums.size();
            if (n <= 0) return 0;
            sort(nums.begin(), nums.end());
            int count = 0;
            dfs(nums, n, target, 0, 0, count);
            return count;
        }

        void dfs(vector<int>& nums, int n, int target, int cur, int sum, int& count) {
            if (cur >= n || sum >= target) {
                if (sum == target) {
                    count++;
                }
                return;
            }
            int k = nums[cur];
            int limit = target / k;
            for (int i = 0; i <= limit; ++i) {
                dfs(nums, n, target, cur+1, sum + i * k, count);
            }
        }
    };

    TEST_FIXTURE(Solution, Normal1)
    {
        vector<int> nums = {1,2,3};
        int target = 4;
        int result = combinationSum4(nums, target);
        LOG(INFO) << "combination result:" << result;
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
