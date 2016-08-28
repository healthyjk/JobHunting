#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>

using namespace std;

/**
  * 测试用例：代码测试模版用于拷贝
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/

SUITE(StringUtilsTest)
{
    class Solution {
    public:
        /*字符串分割函数*/
        void split(string& s, string& delim, vector<string>& ret)
        {
          size_t last = 0;
          size_t index=s.find_first_of(delim,last);
          ret.clear();
          while (index!=std::string::npos)
          {
            ret.push_back(s.substr(last,index-last));
            last=index+1;
            index=s.find_first_of(delim,last);
          }
          if (index-last>0)
          {
            ret.push_back(s.substr(last,index-last));
          }
        }

        /*二进制字符串转十进制整数*/
        int bin2dec(const string& bin) {
            int n = bin.size();
            int result = 0;
            for (int i = n-1; i >= 0; --i) {
                result += (bin[i] == '0' ? 0 : (1 << (n-1-i)));
            }
            return result;
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
