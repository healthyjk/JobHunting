// JinRiTouTiao-work3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

int main() {
  ifstream cin("input.txt");
  int x, k;
  cin >> x >> k;
  long long a = 1;

  int count = 0;
  vector<int> bits(32, -1);
  for (int i = 0; i < 31; ++i) {
    if ((x & a) == 0) {
      bits[i] = 1;
      count++;
    } else {
      bits[i] = 0;
    }
    a <<= 1;
  }
  bits[31] = 1;

  int index = 0;
  a = 1;
  for (; ; ++index) {
     if ((a << index) >= k) {
       break;
     }
  }
  
  if (index > count) {
    for (int i = count; i < index; ++i) {
      bits.push_back(1);
      count++;
    } 
  }

  long long result = 0;
  long long temp;
  for (int i = bits.size()-1; i >= 0; --i) {
    if (bits[i] == 1) {
      temp = (a << count);
      if (k >= temp) {
        result |= (a << i);       
        k -= temp;
        if (k == 0) {
          break;
        }
      }
      count--;
    }
  }

  cout << result << endl;
  return 0;
}