#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：回文串算法测试
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/

SUITE(PalinDromeTest)
{
    class Solution {
    public:
        /*直接遍历每个中心轴，考虑奇偶两种回文情况，计算最大值*/
        int LongestPalinDrome(string str) {
            int n = str.size();
            if (n <= 1) return n;

            int i, j;
            int temp = 0;
            int maxLen = 0;
            int axis = 0;

            for (i = 0; i < n; ++i) {
                temp = 0;
                for (j = 0; (i-j) >= 0 && (i+j) < n; j++) {
                    if (str[i-j] != str[i+j]) {
                        break;
                    }
                    temp = (j << 1) + 1;
                }

                if (temp > maxLen) {
                    maxLen = temp;
                    axis = i;
                }

                temp = 0;
                for (j = 0; (i-j) >= 0 && (i+j+1) < n; ++j) {
                    if (str[i-j] != str[i+j+1]) {
                        break;
                    }
                    temp = j * 2 + 2;
                }
                if (temp > maxLen) {
                    axis = i;
                    maxLen = temp;
                }
            }

            if (maxLen % 2 == 0) {
                string pal_str = str.substr(axis - maxLen/2 + 1, maxLen);
                //cout << pal_str << endl;
            } else {
                string pal_str = str.substr(axis - maxLen/2, maxLen);
                //cout << pal_str << endl;
            }

            return maxLen;
        }


        /* Manacher算法计算回文串；
         * Manacher算法首先对字符串做一个预处理，在所有的空隙位置(包括首尾)插入同样的符号，要求这个符号是不会在原串中出现的。这样会使得所有的串都是奇数长度的。*/
        int LongestPalinDrome_Manacher(string str) {
            int n = str.size();
            if (n < 2) return n;
            string temp(n*2+1,'#');
            for (int i = 0; i < n; ++i) {
                temp[i*2+1] = str[i];
            }

            n = n*2+1;

            int maxRight = 0;
            int pos = 0;
            int i, j;
            vector<int> rl(n, 0);
            int maxLen = 0;
            int axis;

            for (i = 0; i < n; ++i) {
                if (i < maxRight) {
                    j = pos * 2 - i;
                    rl[i] = min(rl[j], maxRight - i);
                } else {
                    rl[i] = 1;
                }

                while ((i-rl[i]) >= 0 && (i+rl[i] < n) && (temp[i-rl[i]] == temp[i+rl[i]])) {
                    rl[i]++;
                }

                if ((i+rl[i]) > maxRight) {
                    maxRight = i + rl[i];
                    pos = i;
                }

                if (rl[i] > maxLen) {
                    maxLen = rl[i];
                    axis = i;
                }
            }

            maxLen--; //(RL[i] - 1才是实际的回文串长度)
            if (maxLen % 2 != 0) {
            // 形如aba形式
                axis = axis/2;
                string pal_str = str.substr(axis - maxLen/2, maxLen);
                //cout << pal_str << endl;
            } else {
            // 形如abba形式
                axis = axis/2 - 1;
                string pal_str = str.substr(axis - maxLen/2 + 1, maxLen);
                //cout << pal_str << endl;
            }

            return maxLen;
        }
    };

    TEST_FIXTURE(Solution, Normal1)
    {
        string str = "aba";
        int result = LongestPalinDrome(str);
        CHECK_EQUAL(result, 3);

        str = "sadda";
        result = LongestPalinDrome(str);
        CHECK_EQUAL(result, 4);

        str = "addadduty";
        result = LongestPalinDrome(str);
        CHECK_EQUAL(result, 5);
        return;
    }

    TEST_FIXTURE(Solution, Normal2)
    {
        string str = "aba";
        int result = LongestPalinDrome_Manacher(str);
        CHECK_EQUAL(result, 3);

        str = "sadda";
        result = LongestPalinDrome_Manacher(str);
        CHECK_EQUAL(result, 4);

        str = "addadduty";
        result = LongestPalinDrome_Manacher(str);
        CHECK_EQUAL(result, 5);
        return;
    }

    TEST_FIXTURE(Solution, Normal3)
    {
        return;
    }
}
