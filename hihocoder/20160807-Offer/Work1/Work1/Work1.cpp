// Work1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#define INT_MIN     (-2147483647 - 1) /* minimum (signed) int value */
#define INT_MAX       2147483647      /* maximum (signed) int value */

using namespace std;

/* 经验教训： 第一题永远是暴力解就能过的。。。SX。。。
   想不出好的解就用暴力解； */
int main()
{
  ifstream cin("input.txt");

  int n, x;
  cin >> n >> x;
  vector<int> nums(n);

  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }

  int result = INT_MAX;
  int current = 0;

  for (int i = 0; i < n; ++i) {
    current += nums[i];
  }
  if (current < x) {
    cout << "-1" << endl;
    return;
  }

  int MaxKind = 1 << n;
  for (int i = 0; i < MaxKind; ++i) {
    current = 0;
    //将i看成20位的二进制数字，i的每一位代表第j个数是否选中
    for (int j = 0; j < n; ++j) {
      if (((1 << j) & i) != 0) {
        current += nums[j];
        if (current >= x) {
          break;
        }
      }
    }

    if (current >= x && current < result) {
      result = current;
    }
  }

  cout << result << endl;
  return 0;
}

