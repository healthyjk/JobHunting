// Work1.cpp : �������̨Ӧ�ó������ڵ㡣
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

/* �����ѵ�� ��һ����Զ�Ǳ�������ܹ��ġ�����SX������
   �벻���õĽ���ñ����⣻ */
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
    //��i����20λ�Ķ��������֣�i��ÿһλ�����j�����Ƿ�ѡ��
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

