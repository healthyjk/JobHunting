#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：最长公共子序列用例测试
  * 作者：yanjiankang
  * 时间：2016年9月6日
  **/

SUITE(LongestSubStrSeqTest)
{
    class Solution {
    public:
        /*使用动态规划求解最长公共子序列的问题，返回最大长度，暂未打印最长序列*/
        int LongestSubSequence(string& str1, string& str2) {
            int n = str1.size();
            int m = str2.size();
            vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    if (str1[i-1] == str2[j-1]) {
                        dp[i][j] = dp[i-1][j-1] + 1;
                    } else {
                        dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                    }
                }
            }

            string result;
            for (int i = n, j = m; i >= 1 && j >= 1;) {
                if (str1[i-1] == str2[j-1]) {
                    result.push_back(str1[i-1]);
                    i--;
                    j--;
                } else {
                    if(dp[i][j -1] > dp[i - 1][j])
                    {
                        j--;
                    }
                    else
                    {
                        i--;
                    }
                }
            }
            reverse(result.begin(), result.end());
            LOG(INFO) << result;
            return dp[n][m];
        }
    };

    TEST_FIXTURE(Solution, Normal1)
    {
        string str1 = "abcbdab";
        string str2 = "bdcaba";
        int result = LongestSubSequence(str1, str2);
        CHECK_EQUAL(result, 4);
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
