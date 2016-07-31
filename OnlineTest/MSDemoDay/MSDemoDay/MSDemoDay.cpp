// MSDemoDay.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <fstream>
#include <string.h>
#define maxn 110
#define inf 9999999
using namespace std;
int n, m;
int r[maxn][maxn];
int up[maxn][maxn];
char str[maxn][maxn];


//int GetUp(int i, int j)
//{
//  int x = r[i - 1][j];
//  int y = up[i - 1][j];
//  if(str[i-1][j+1]!= 'b')x++;
//  int ans = min(x,y);
//  return ans;
//
//}
//
//
//int GetR(int i, int j)
//{
//  int x = r[i][j - 1];
//  int y = up[i][j - 1];
//  if(str[i+1][j - 1]!='b')y++;
//  return min(x,y);
//}
//
//
//int main()
//{
//  ifstream fin;
//  //while(true)
//  //{
//  fin >> n >> m;
//  for(int i = 0 ; i < n;i++)
//  {
//    fin >> str[i];
//    int len = strlen(str[i]);
//    str[i][len] = 'b';
//    str[i][len+1] = '\0';
//  }
//
//  for(int i = 0 ; i <= m; i++)
//  {
//    str[n][i] = 'b';
//  }
//
//  //初始化第一行
//  int cnt = 0;
//  for(int j = 0 ; j < m;j++) {
//    if(str[0][j] == 'b') {
//      ++cnt;
//    }
//    r[0][j] = cnt;
//    up[0][j] = inf;
//  }
//
//  cnt = 0;
//  // 初始化第一列
//  // 一开始往右走，所以要判断一下
//  if(str[0][1]!='b')++cnt;
//
//  for(int i = 0 ; i < n; i++)
//  {
//    if(str[i][0] == 'b')
//    {
//      ++cnt;
//    }
//    up[i][0] = cnt;
//    r[i][0] = inf;
//  }
//
//  for(int i = 1 ; i < n;i++)
//  {
//    for(int j = 1;j < m;j++)
//    {
//      up[i][j] = GetUp(i,j);
//      r[i][j] = GetR(i, j);
//      if(str[i][j] == 'b')
//      {
//        up[i][j]++;
//        r[i][j]++;
//      }
//    }
//  }
//
//  printf("%d\n", min(up[n - 1][m - 1], r[n - 1][m - 1]));
//  //}
//}

