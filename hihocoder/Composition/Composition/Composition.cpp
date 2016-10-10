// Composition.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <fstream>

using namespace std;

int LongestRemainLegalStringLength1(vector<vector<bool>>& legal, int n, string& s) {
  vector<int> dp(n, 1);
  int max_remain = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i-1; j >= 0; j--) {
      int index1 = s[j] - 'a';
      int index2 = s[i] - 'a';
      if (legal[index1][index2]) {
        dp[i] = max(dp[i], dp[j]+1);
      }
    }
    if (max_remain < dp[i]) {
      max_remain = dp[i];
    }
  }
  return max_remain;
}

int LongestRemainLegalStringLength2(vector<vector<bool>>& legal, int n, string& s) {
  vector<int> dp(n, 1);
  vector<int> table(26, 0);
  int max_remain = 0;

  for (int i = 0; i < n; ++i) {
    int index = s[i] - 'a';
    for (int j = 0; j < 26; ++j) {
      if (legal[j][index]) {
        dp[i] = max(dp[i], table[j]+1);
      }
    }
    table[index] = dp[i];
    if (max_remain < dp[i]) {
      max_remain = dp[i];
    }
  }
  return max_remain;
}

int LongestRemainLegalStringLength3(vector<vector<bool>>& legal, int n, string& s) {
  vector<int> table(26, 0);
  int max_remain = 0;
  int temp = 1;
  for (int i = 0; i < n; ++i) {
    int index = s[i] - 'a';
    for (int j = 0; j < 26; ++j) {
      if (legal[j][index]) {
        temp = max(temp, table[j]+1);
      }
    }
    table[index] = temp;
    if (max_remain < temp) {
      max_remain = temp;
    }
  }
  return max_remain;
}

int main() {
  ifstream cin("input.txt");
  int n, m;

  while (cin >> n) {
    string s;
    cin >> s;
    cin >> m;

    vector<vector<bool>> legal(26, vector<bool>(26, true));

    for (int i = 0; i < m; ++i) {
      char c1, c2;
      cin >> c1 >> c2;
      legal[c1-'a'][c2-'a'] = false;
      legal[c2-'a'][c1-'a'] = false;
    }

    int result = n - LongestRemainLegalStringLength1(legal, n, s);
    cout << result << endl;

    result = n - LongestRemainLegalStringLength2(legal, n, s);
    cout << result << endl;

    result = n - LongestRemainLegalStringLength3(legal, n, s);
    cout << result << endl;
  }

  return 0;
}


