// Work2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <fstream>

using namespace std;

string delim = " ";

void split(string& s, string& delim, vector<string>& ret)
{
  size_t last = 0;
  size_t index=s.find_first_of(delim,last);
  ret.clear();
  while (index!=std::string::npos)
  {
    ret.push_back(s.substr(last,index-last));
    last=index+1;
    index=s.find_first_of(delim,last);
  }
  if (index-last>0)
  {
    ret.push_back(s.substr(last,index-last));
  }
}

int ComputeMaxProfit(vector<int>& price) {
  int n = price.size();
  if(n <= 1)return 0;

  int valley = price[0];
  int profit = price[1] - price[0];

  for(int i = 2; i < n; i++)
  {
    valley = min(price[i-1], valley);
    profit = max(profit, price[i] - valley);
  }

  if(profit < 0) return 0;
  return profit;
}

int main() {
  ifstream cin("input.txt");
  string input;
  while (getline(cin, input)) {
    vector<string> temp;
    split(input, delim, temp);
    int n = temp.size();
    vector<int> price(n, 0);
    for (int i = 0; i < n; ++i) {
      price[i] = atoi(temp[i].c_str());
    }
    int profit = ComputeMaxProfit(price);
    cout << profit << endl;
  }
  return 0;
}



