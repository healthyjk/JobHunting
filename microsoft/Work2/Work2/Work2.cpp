// Work2.cpp : 定义控制台应用程序的入口点。
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

/*
int getMinDelete(string& str, int n, vector<vector<bool>>& illegal) {
  vector<int> dp(n,1);
  int remain = 0;

  vector<int> letter(26, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 26; ++j) {
      if (illegal[j][str[i]-'a']) {
        dp[i] = max(dp[i], letter[j] + 1);
        //cout << dp[i];
      }
    }
    letter[str[i]-'a'] = dp[i];
    if (dp[i] > remain) remain = dp[i];
  }

  return (n-remain);
} */

int getMinDelete(string& str, int n, vector<vector<bool>>& illegal) {
  vector<int> dp(n,1);
  int remain = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = i-1; j >= 0; j--) {
      if (illegal[str[j]-'a'][str[i]-'a']) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
    cout << "i=" << i << "," << "dp[i]=" << dp[i] << endl;
    if (dp[i] > remain) remain = dp[i];
  }
  return (n-remain);
}


int main() {
  ifstream cin("input.txt");
  int n, m;
  while (cin >> n) {
    string str;
    cin >> str;
    cin >> m;

    vector<vector<bool>> illegal(26, vector<bool>(26, true));

    for(int i = 0; i < m; ++i) {
      char a, b;
      cin >> a >> b;
      illegal[a-'a'][b-'a'] = false;
      illegal[b-'a'][a-'a'] = false;
    }
    int result = getMinDelete(str, n, illegal);
    cout << result << endl;
  }

  return 0;
}







