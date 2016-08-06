// StrToInt.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool isDigit(char ch) {
    	return (ch >= '0' && ch <= '9');    
    }
    
    int StrToInt(string str) {
        str.erase(0, str.find_first_not_of(' '));
        str.erase(str.find_last_not_of(' ') + 1);
        
        int n = str.size();
        if (n <= 0) return 0;
        
        int result = 0;
        int flag = false;
        int index = 0;
        if (str[index] == '+') {
            index++;
        } else if (str[index] == '-') {
            flag = true;
            index++;
        }
        
        while (index < n) {
            if (isDigit(str[index])) {
                int ch = str[index] - '0';
                if (result > (INT_MAX / 10) 
                    || ((result == (INT_MAX / 10)) && (ch >= ((INT_MAX % 10) + (flag ? 1 : 0))))) {
                    return (flag ? INT_MIN : INT_MAX);
                }
                result = result * 10 + ch;
            } else {
                break;
            }
            index++;
        }
        
        return flag ? (-result) : result;
    }
};

int main()
{
  string str;
  Solution solution;
  while (cin >> str) {
    int num = solution.StrToInt(str);
    cout << "num:" << num << endl;
  }
	return 0;
}

