// Test1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <fstream>
#include <cmath>
#include <cstdio>

using namespace std;

int main() {
  ifstream cin("input.txt");
  int n, m;
  while (cin >> n >> m) {
    double result = 0;
    double num = n;
    for(int i = 0; i < m; ++i) {
      result += num;
      num = sqrt(num);
    }

    printf("%.2lf\n", result);
  }
  return 0;
}


