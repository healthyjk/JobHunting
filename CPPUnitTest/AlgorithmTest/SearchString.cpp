#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：KMP字符串搜索算法
  * 作者：yanjiankang
  * 时间：2016年9月7日
  **/

SUITE(SearchStringTest)
{
    class Solution {
    public:
        int kmpSearch(string& str, string& pattern) {
            int n = str.size();
            int m = pattern.size();
            vector<int> next(m, 0);
            computeNext(pattern, next);
            cout << "next";
            for (int i = 0; i < m; ++i) {
                cout << next[i] << "\t";
            }
            cout << endl;
            int i = 0;
            int j = 0;
            while (i < n && j < m) {
                if (j == -1 || str[i] == pattern[j]) {
                    i++;
                    j++;
                } else {
                    j = next[j];
                }
            }
            if (j == m) {
                return (i-j); //返回匹配上的起始位置
            }
            return -1;
        }

        void computeNext(string& p, vector<int>& next) {
            if (p.size() <= 0 || next.size() != p.size()) return;
            next[0] = -1;
            int i = 0;
            int j = -1;
            int n = p.size();
            while (i < n-1) {
                if (j == -1 || p[i] == p[j]) {
                    i++;
                    j++;
                    if (p[i] != p[j]) {
                        next[i] = j;
                    } else {
                        next[i] = next[j];
                    }
                } else {
                    j = next[j];
                }
            }
        }
    };

    TEST_FIXTURE(Solution, Normal1)
    {
        string str1= "acaabc";
        string str2= "aab";
        int result = kmpSearch(str1, str2);
        LOG(INFO) << result;
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
