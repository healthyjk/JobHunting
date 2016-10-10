// Work1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include <fstream>

using namespace std;

int getContineousZero(string& str) {
  int n = str.size();
  int start = 0;
  int max_count = 0;
  int temp;
  for (int i = 0; i < n;) {
    if (str[i] == '0') {
      start = i+1;
      temp = 1;
      while (start < n && str[start++] == '0') {
        temp++;
      }
      if (temp > max_count) {
        max_count = temp;
      }
      i = start;
    } else {
      i++;
    }
  }

  return max_count;
}

int Solution(string& str, int k) {
  int n = str.size();
  if (n <= 0) return 0;
  if (k == 0) {
    return getContineousZero(str);
  }
  int max_count = 0;
  for (int i = 0; i <= n-k; ++i) {
    string temp(str);
    for (int j = i; j < (k+i); ++j) {
      temp[j] = (temp[j] == '0') ? '1' : '0';
    }
    int temp_count = getContineousZero(temp);
    if (max_count < temp_count) {
      max_count = temp_count;
    }
  }

  return max_count;
}

int main()
{
  ifstream cin("input.txt");
  int s;
  cin >> s;
  while (s--) {
    int k;
    string str;
    cin >> k >> str;



    int result = Solution(str, k);


    cout << result << endl;
  }

	return 0;
}

