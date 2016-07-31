// Test1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

int n, p, w, h; 

int floor(int num1, int num2) {
  return (num1/num2);
}

int ceil(int num1, int num2) {
  if (num1 % num2 != 0) {
    return (num1/num2+1);
  } else {
    return (num1/num2);
  }
}

int getMaxFontSize(vector<int> a) {
  if (n == 0) return 0;
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += a[i];
  }
  int dmax = sqrt((double)((w*h)/(sum/p+1)));

  int d;
  int min,arow, rows, pc;
  for (d = dmax+1; d >= 0; d--) {
    rows = 0;
    pc = floor(h,d);
    for (int i = 0; i < n; ++i) {
      arow = floor(w,d);
      if (arow > 0) {
        rows += ceil(a[i], arow);
      }
    }
    if (pc*p >= rows) {
      break;
    }
  }
  return d;
}



int main()
{
  int t;
  ifstream fin("input.txt");
  fin >> t;
  while (t--) {
    fin >> n >> p >> w >> h;
    vector<int> a(n, 0);
    for (int i = 0; i < n; ++i) {
      fin >> a[i];
    }

    int result = getMaxFontSize(a);

    cout << result << endl;
  }

  system("pause");
	return 0;
}

