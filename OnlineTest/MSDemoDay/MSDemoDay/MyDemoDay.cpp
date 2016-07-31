#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

#define max 105
#define inf 999999

int down[max][max];
int rht[max][max];
char str[max][max];

int getDownCount(int i, int j) {
  int r = rht[i-1][j];
  int u = down[i-1][j];
  if (str[i-1][j+1] != 'b') {
    r++;
  }
  return (r < u ? r : u);
}

int getRightCount(int i, int j) {
  int r = rht[i][j-1];
  int u = down[i][j-1];
  if (str[i+1][j-1] != 'b') {
    u++;
  }
  return (r < u ? r : u);
}

int main() {
  int n, m;
  ifstream fin("input.txt");
  //cin >> n >> m;
  fin >> n >> m;
  if (n <= 0 || m <= 0) return 0;

  //read input
  int len;
  for (int i = 0; i < n; ++i) {
    //cin >> str[i];
    fin >> str[i];
    len = strlen(str[i]);
    str[i][len] = 'b';
    str[i][len+1] = '\0';
  }
  
  for (int i = 0;i <= m; ++i) {
    str[n][i] = 'b';
  }

  //for (int i = 0; i <= n; ++i) {
  //  for (int j = 0;j <= m; ++j) {
  //     cout << str[i][j] << "\t";
  //  }
  //  cout << endl;
  //}

  //initiate the first row
  int count = 0;
  for (int i = 0; i < m; ++i) {
    if (str[0][i] == 'b') {
      count++;
    }
    down[0][i] = inf;
    rht[0][i] = count;
  }

  //initiate the first column
  count = 0;
  if (str[0][1] != 'b') {
    count++;
  }
  for (int i = 1; i < n; ++i) {
    if (str[i][0] == 'b') {
      count++;
    }
    down[i][0] = count;
    rht[i][0] = inf;
  }

  // calculate down and rht
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j < m; ++j) {
      down[i][j] = getDownCount(i, j);
      rht[i][j] = getRightCount(i, j);
      if (str[i][j] == 'b') {
        down[i][j]++;
        rht[i][j]++;
      }
    }
  }

  int min =  (down[n-1][m-1] < rht[n-1][m-1] ? down[n-1][m-1] : rht[n-1][m-1]);
  cout << min << endl;

  system("pause");
  return 0;
}
