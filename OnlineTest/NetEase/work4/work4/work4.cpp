// work4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include <fstream>
#include <cmath>

using namespace std;

struct State {
  int cur;
  int dir;
  int time;
  State(int x, int y, int z) : cur(x), dir(y), time(z) {}
};

struct Request {
  int t; 
  int s;
  int e;
  int dir;
  int dur;
};

bool CompFunc(const Request& a, const Request& b) {
  return a.t < b.t;
}

int main()
{
  ifstream cin("input.txt");
  int t;
  cin >> t;
  while (t--) {
    int cur = 1;
    int n; 
    cin >> n;
    vector<Request> reqs(n);
    for (int i = 0; i < n; ++i) {
      cin >> reqs[i].t >> reqs[i].s >> reqs[i].e;
      reqs[i].dir == reqs[i].s > reqs[i].e ? 0 : 1;
    }

    //sort(reqs.begin(), reqs.end(), CompFunc);
  
    State curstate(1, 1, 0);

    cur = 1;

    for (auto iter = reqs.begin(); iter != reqs.end(); ++iter) {
      cout << abs(iter->s - cur) << endl;
      cur = iter->e;
    }
  
  
  
  }

	return 0;
}