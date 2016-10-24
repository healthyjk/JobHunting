// Work4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <fstream>

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

/*字符串分割函数*/
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




int main() {
  ifstream cin("input.txt");
  int n, m;
  while (cin >> n >> m) {



    int result;


    cout << result << endl;
  }

  return 0;
}

