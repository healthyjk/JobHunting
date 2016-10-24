// LongestSubString.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <fstream>

#define INT_MIN     (-2147483647 - 1) /* minimum (signed) int value */
#define INT_MAX       2147483647    /* maximum (signed) int value */
#define UINT_MAX      0xffffffff    /* maximum unsigned int value */
#define LONG_MIN    (-2147483647L - 1) /* minimum (signed) long value */
#define LONG_MAX      2147483647L   /* maximum (signed) long value */
#define ULONG_MAX     0xffffffffUL  /* maximum unsigned long value */
#define LLONG_MAX     9223372036854775807i64       /* maximum signed long long int value */
#define LLONG_MIN   (-9223372036854775807i64 - 1)  /* minimum signed long long int value */
#define ULLONG_MAX    0xffffffffffffffffui64       /* maximum unsigned long long int value */

using namespace std;

int LongestSubString(string& str1, string& str2) {
  int n = str1.size();
  int m = str2.size();

  vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
  int max_len = 0;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
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

int main() {
  ifstream cin("input.txt");
  string str1 = "abcabced";
  string str2 = "ubcadefer";
  int len = LongestSubString(str1, str2) ;
  cout << "Max Longest Substr len:" << len << endl;
  return 0;
}


