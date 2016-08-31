#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/**
  * 测试用例：排列组合问题求解
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/
SUITE(CombinationTest)
{
    class Solution {
    public:
        /*没有重复元素的字符串全排列*/
        vector<string> getCombinationList_NoRepeat(string str) {
            vector<string> result;
            int n = str.size();
            if (n <= 0) return result;
            permutation_NoRepeat(str, n, 0, result);
            return result;
        }

        void permutation_NoRepeat(string str, int n, int begin, vector<string>& result) {
            if (begin == n) {
                result.push_back(str);
                cout << str << endl;
            }

            for (int i = begin; i < n; ++i) {
                swap(str[begin], str[i]);
                permutation_NoRepeat(str, n, begin + 1, result);
                swap(str[i], str[begin]);
            }
        }

        vector<string> getCombinationList_WithRepeat(string str) {
            vector<string> result;
            int n = str.size();
            if (n <= 0) return result;
            permutation_WithRepeat(str, n, 0, result);
            return result;
        }

        bool isSwap(string& str, int begin, int end) {
            for (int i = begin; i < end; ++i) {
                if (str[i] == str[end]) {
                    return false;
                }
            }
            return true;
        }

        void permutation_WithRepeat(string str, int n, int begin, vector<string>& result) {
            if (begin == n) {
                result.push_back(str);
                cout << str << endl;
            }

            for (int i = begin; i < n; ++i) {
                if (isSwap(str, begin, i)) {
                    swap(str[begin], str[i]);
                    permutation_WithRepeat(str, n, begin + 1, result);
                    swap(str[i], str[begin]);
                }
            }
        }
    };

    TEST_FIXTURE(Solution, Normal1)
    {
        string test("abc");
        getCombinationList_NoRepeat(test);
        return;
    }

    TEST_FIXTURE(Solution, Normal2)
    {
        string test("aabc");
        getCombinationList_WithRepeat(test);
        return;
    }

    TEST_FIXTURE(Solution, Normal3)
    {
        return;
    }
}
