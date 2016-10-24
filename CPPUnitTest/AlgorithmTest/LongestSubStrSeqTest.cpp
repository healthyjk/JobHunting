#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：最长公共子序列用例测试 && 最长公共子串
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

        int LongestSubString(string& str1, string& str2) {
            int n = str1.size();
            int m = str2.size();

            vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
            int max_len = 0;

            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    //cout << str1[i-1] << str2[j-1] << endl;
                    if (str1[i-1] == str2[j-1]) {
                        dp[i][j] = dp[i-1][j-1] + 1;
                        if (max_len < dp[i][j]) {
                            max_len = dp[i][j];
                        }
                    } else {
                        dp[i][j] = 0;
                    }
                }
            }
            return max_len;
        }

        int LongestSubString2(string& str1, string& str2) {
            int n = str1.size();
            int m = str2.size();

            int max_len = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    int s = i;
                    int t = j;
                    int length = 0;

                    while (s < n && t < m && str1[s-1] == str2[t-1]) {
                        s++;
                        t++;
                        length++;
                    }

                    if (length > max_len) {
                        max_len = length;
                    }
                }
            }
            return max_len;
        }

        int LongestSubString3(string& str1, string& str2) {
            int n = str1.size();
            int m = str2.size();

            vector<int> dp(m+1, 0);
            int max_len = 0;

            for (int i = 1; i <= n; ++i) {
                for (int j = m; j >= 1; --j) {
                    //cout << str1[i-1] << str2[j-1] << endl;
                    if (str1[i-1] == str2[j-1]) {
                        dp[j] = dp[j-1] + 1;
                        if (max_len < dp[j]) {
                            max_len = dp[j];
                        }
                    } else {
                        dp[j] = 0;
                    }
                }
            }
            return max_len;
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
        string str1 = "abcabced";
        string str2 = "ubcadefer";
        int len = LongestSubString3(str1, str2) ;
        cout << "Max Longest Substr len:" << len << endl;

        str1 = "YXXXXXY";
        str2 = "YXYXXYYYYXXYYYYXYYXXYYXXYXYYYYYYXYXYYXYXYYYXXXXXX";
        len = LongestSubString3(str1, str2) ;
        cout << "Max Longest Substr len:" << len << endl;
        return;
    }

    TEST_FIXTURE(Solution, Normal3)
    {
        return;
    }
}
