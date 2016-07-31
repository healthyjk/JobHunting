// Test2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

string ipToString(vector<int>& ips) {
  string result;
  char c;
  for (int i = 0; i < ips.size(); ++i) {    
    int k = 8;
    int a = 128;
    while (k--) {
      c = (ips[i] & a) == 0 ? '0' : '1';
      result.push_back(c);
      a >>= 1;
    }
  }
  return result;
}

void split(string& s, string& delim, vector<string>& ret)  
{  
  size_t last = 0;  
  size_t index=s.find_first_of(delim,last);  
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

bool compareIp(string& str, vector<int>& mask, vector<string>& ips, vector<string>& rules) {
  for (int i = 0; i < ips.size(); ++i) {
    if (mask[i] == 0) {
      return rules[i] == "allow" ? true : false;
    }
    mask[i] = mask[i] > 0 ? mask[i] : 32;
    if (str.substr(0, mask[i]) == ips[i].substr(0, mask[i])) {
      if (rules[i] == "allow") {
        return true;
      } else {
        return false;
      }
    }
  }
  return true;
}

string dot = ".";
string dl = "/";

int main()
{
  //ifstream fin("input.txt");
  
  int n, m;
  cin >> n >> m;
  vector<string> rules(n, "");
  vector<string> ips(n, "");
  vector<int> mask(n, -1);
  string temp;
  vector<int> v(4,0);
  vector<string> splits1;
  vector<string> splits2;
  for (int i = 0; i < n; ++i) {
    cin >> rules[i] >> temp;
    split(temp, dot, splits1);
    v[0] = atoi(splits1[0].c_str());
    v[1] = atoi(splits1[1].c_str());
    v[2] = atoi(splits1[2].c_str());
    split(splits1[3], dl, splits2);
    v[3] = atoi(splits2[0].c_str());

    if (splits2.size() > 1) {
      mask[i] = atoi(splits2[1].c_str());
    }
    ips[i] = ipToString(v);

    splits1.clear();
    splits2.clear();
  }

  /*for (int i = 0; i < n; ++i) {
    cout << "r:" << rules[i] << " ip:" << ips[i] << " m:" << mask[i] << endl;
  }*/

  string str;
  for (int i = 0; i < m; ++i) {
    cin >> temp;
    split(temp, dot, splits1);
    v[0] = atoi(splits1[0].c_str());
    v[1] = atoi(splits1[1].c_str());
    v[2] = atoi(splits1[2].c_str());
    v[3] = atoi(splits1[3].c_str());
    str = ipToString(v);

    if (compareIp(str,mask,ips,rules)) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }

    splits1.clear();
  }

  //system("pause");
  return 0;
}
