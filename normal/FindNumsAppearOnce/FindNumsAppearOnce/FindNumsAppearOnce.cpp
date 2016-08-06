#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
  // 用map的方法不好
  void FindNumsAppearOnce_1(vector<int> data,int* num1,int *num2) {
    int n = data.size();
    if (n <= 1) return;

    map<int, int> num_count;
    for (int i = 0; i < n; ++i) {
      num_count[data[i]]++;
    }

    int k = 0;
    for (auto iter = num_count.begin(); iter != num_count.end(); ++iter) {
      if (iter->second == 1) {
        if (k == 0) {
          *num1 = iter->first;
          k++;
        } else {
          *num2 = iter->first;
          break;
        }
      }
    }

    return;
  }

  //正确解法应该用异或来实现
  void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
    int n = data.size();
    if (n <= 0) return;

    int temp = data[0];
    for (int i = 1; i < n; ++i) {
      temp ^= data[i];
    }

    if (temp == 0) return;

    int seq = 1;
    while ((temp & 1) != 1) {
      seq <<= 1;
      temp >>= 1;
    }

    *num1 = *num2 = 0;

    for (int i = 0; i < n; ++i) {
      if ((data[i] & seq) != 0) {
        *num1 ^= data[i];
      } else {
        *num2 ^= data[i];
      }
    }

    return;
  }
};

int main()
{

  int a[] = {2,4,3,6,3,2,5,5};
  vector<int> va(a, a+sizeof(a)/sizeof(int));
  Solution solution;
  int num1, num2;
  solution.FindNumsAppearOnce(va, &num1, &num2);
  cout << num1 << "," << num2 << endl;
  return 0;
}

