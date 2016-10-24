// Work1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <fstream>

using namespace std;

int minDistance(const string &word1, const string &word2) {
  const size_t n = word1.size();
  const size_t m = word2.size();
  vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
  for (size_t i = 0; i <= n; i++) {
    dp[i][0] = i;
  }
  for (size_t j = 0; j <= m; j++) {
    dp[0][j] = j;
  }

  for (size_t i = 1; i <= n; i++) {
    for (size_t j = 1; j <= m; j++) {
      if (word1[i - 1] == word2[j - 1])
        dp[i][j] = dp[i - 1][j - 1];
      else {
        int mn = min(dp[i - 1][j], dp[i][j - 1]);
        dp[i][j] = 1 + min(dp[i - 1][j - 1], mn);
      }
    }
  }
  return dp[n][m];
}

int main() {
  ifstream cin("input.txt");
  string word1, word2;
  int result;
  while (cin >> word1 >> word2) {
    result = minDistance(word1, word2);
    cout << result << endl;
  }
  return 0;
}






