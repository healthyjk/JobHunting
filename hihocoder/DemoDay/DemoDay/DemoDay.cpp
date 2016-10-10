// DemoDay.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#define INT_MIN     (-2147483647 - 1) /* minimum (signed) int value */
#define INT_MAX       2147483647    /* maximum (signed) int value */
#define UINT_MAX      0xffffffff    /* maximum unsigned int value */
#define LONG_MIN    (-2147483647L - 1) /* minimum (signed) long value */
#define LONG_MAX      2147483647L   /* maximum (signed) long value */
#define ULONG_MAX     0xffffffffUL  /* maximum unsigned long value */
#define LLONG_MAX     9223372036854775807i64       /* maximum signed long long int value */
#define LLONG_MIN   (-9223372036854775807i64 - 1)  /* minimum signed long long int value */
#define ULLONG_MAX    0xffffffffffffffffui64       /* maximum unsigned long long int value */


int main() {
  ifstream cin("input.txt");
  int n, m;
  while (cin >> n >> m) {
    vector<string> maze(n, "");
    for (int i = 0; i < n; ++i) {
      cin >> maze[i];
      maze[i].push_back('b');
    }
    string temp(m+1, 'b');
    maze.push_back(temp);

    vector<vector<int> > h(n+1, vector<int>(m+1, 0));
    vector<vector<int> > v(n+1, vector<int>(m+1, 0));

    h[0][0] = maze[0][0] == '.' ? 0 : 1;
    v[0][0] = h[0][0];

    //初始化第一行和第一列
    for (int j = 1; j < m; ++j) {
      h[0][j] = (maze[0][j] == 'b') ? (h[0][j-1]+1) : h[0][j-1];
      v[0][j] = INT_MAX;
    }

    for (int i = 1; i < n; ++i) {
      if (i == 1)  {
        v[1][0] = (maze[0][1] == 'b') ? 0 : 1; 
        v[1][0] = (maze[1][0] == 'b') ? (v[1][0]+1) : v[1][0];
      } else {
        v[i][0] = (maze[i][0] == 'b') ? (v[i-1][0]+1) : v[i-1][0];
      }
      h[i][0] = INT_MAX;
    }

    for (int i = 1; i < n; ++i) {
      for (int j = 1; j < m; ++j) {
        h[i][j] = min(h[i][j-1], v[i][j-1] + (maze[i+1][j-1] == 'b' ? 0 : 1));
        h[i][j] = (maze[i][j] == '.' ? h[i][j] : (h[i][j] + 1));

        v[i][j] = min(v[i-1][j], h[i-1][j] + (maze[i-1][j+1] == 'b' ? 0 : 1));
        v[i][j] = (maze[i][j] == '.' ? v[i][j] : (v[i][j] + 1));
      }
    }

    /*for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << h[i][j] << "\t";
      }
      cout << endl;
    }

    cout << endl;
    cout << endl;


    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << v[i][j] << "\t";
      }
      cout << endl;
    }

    cout << endl;
    cout << endl;*/

    int result = min(h[n-1][m-1], v[n-1][m-1]);
    cout << result << endl;

  }

  return 0;
}

