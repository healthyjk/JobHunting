// Work1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <fstream>
#include <cstdio>
#include <memory>
#include <cmath>

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

int main() {
  //ifstream cin("input.txt");
  freopen("input.txt","r",stdin);
  int n;

  while (cin >> n) {
    vector<int> nums(n);

    int a = 0;
    int b = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &nums[i]);
      if ((nums[i] & 0x01) != 0) {
        a++;
      } else {
        b++;
      }
    }

    cout << abs(a-b) << endl;
  }

  return 0;
}

/*
int main() {
  //ifstream cin("input.txt");
  freopen("input.txt","r",stdin);
  int n;

  while (cin >> n) {
    vector<int> nums(n);

    for (int i = 0; i < n; ++i) {
      scanf("%d", &nums[i]);
    }

    vector<int> next;
    int m;

    int count = INT_MAX;
    int start = 0;

    while (count > 0) {
      count = 0;
      m = nums.size();
      auto it = nums.begin();

      for (int i = start; i < m-1; ++i) {
        if ((nums[i] + nums[i+1]) & 0x01 != 0) {
          start = (i-1) >= 0 ? i : 0;
          count++;
          next.insert(next.end(), it+i+2, nums.end());
          break;
        } else {
          next.push_back(nums[i]);
        }
      }
      if (count > 0) {
        swap(nums, next);
        next.clear();
      }
    }

    cout << nums.size() << endl;
  }

  return 0;
}


*/


