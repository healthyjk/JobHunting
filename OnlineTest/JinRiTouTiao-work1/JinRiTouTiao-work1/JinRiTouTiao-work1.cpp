// JinRiTouTiao-work1.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

bool canFormPolygon(const vector<int>& nums, int size) {
  if (size < 3) return false;
  long long max = -1;
  long long sum = 0;
  for (int i = 0; i < size; ++i) {
    sum += nums[i];
    if (nums[i] > max) {
      max = nums[i];
    }
  }
  //cout << max << "," << sum << endl;
  if ((max << 1) >= sum) return false;
  return true;
}

int main()
{
  ifstream cin("input.txt");
  int n;
  while (cin >> n) {
    vector<int> nums(n, 0);
    int size = 0;
    int op, len;
    while (n--) {
      cin >> op >> len;
      if (op == 1) {
        nums[size++] = len;
      } else if (op == 2) {
        for (int i = size-1; i >= 0; i--) {
          if (nums[i] == len) {
            //这么简单的地方也搞错？
            for (int j = i; j < size-1; j++) {
              nums[j] = nums[j+1];
            }
            size--;
            break;
          }
          
        } 
      }

      /*for (int i = 0; i < size; ++i) {
        cout << nums[i] << " ";
      }
      cout << endl;*/

      //考试中应该输出No和Yes， 真是SB。。。
      if (canFormPolygon(nums, size)) {
        cout << "YES" << endl;
      } else {
        cout << "NO" << endl;
      }
    }
  }

  return 0;
}

