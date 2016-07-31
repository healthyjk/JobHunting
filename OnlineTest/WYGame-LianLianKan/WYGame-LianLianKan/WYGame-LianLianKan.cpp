// WYGame-LianLianKan.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

//对于i所在的行和j所在的列进行遍历
void markBoards(vector<string>& board, vector<vector<bool>>& flag, int i, int j) { 
  int n = board.size();
  int m = board[0].size();
  int a1 = i, a2 = i;
  int temp = 0;
  while ((--a1) >= 0 && board[a1][j] == board[i][j]) temp++;
  while ((++a2) < n && board[a2][j] == board[i][j]) temp++;
  if (temp > 1) {
    for (int k = a1+1; k < a2; ++k) {
      flag[k][j] = true;
    }
  }
  a1 = j; a2 = j;
  temp = 0;
  while ((--a1) >= 0 && board[i][a1] == board[i][j]) temp++;
  while ((++a2) < m && board[i][a2] == board[i][j]) temp++;
  if (temp > 1) {
    for (int k = a1+1; k < a2; ++k) {
      flag[i][k] = true;
    }
  }
}

//遍历整个局面，计算消除个数，并消除方块，垂直下降，返回消除个数
//逐列遍历，先考虑连续的消除以避免重复的下降
//记得将flag重置
int EliminateAndCount(vector<string>& board, vector<vector<bool>>& flag) {
  int n = board.size();
  int m = board[0].size();
  int a, b;
  int count = 0;
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n; ++i) {
      if (board[i][j] != '.') {
        if (flag[i][j] == true) {
          count++;
          a = i; b = i;
          while ((++b) < n && flag[b][j]) {
            count++;
          }
          for (int k = a-1; k >= 0; --k) {
            board[k+b-a][j] = board[k][j];
            flag[k+b-a][j] = false;
          }
          for (int k = 0; k < b-a; ++k) {
            board[k][j] = '.';
            //flag[k][j] = false;
          }
          i = b+1;
        }
      }
    }
  }
  return count;
}

//简单粗暴的方法
int iterEliminateGame(vector<string>& board, int x0, int y0, int x1, int y1) {
  int n = board.size();
  int m = board[0].size();
  vector<vector<bool>> flag(n, vector<bool>(m, false));

  //因此初始局面是合法的，因此第一次只需要考虑交换的两个位置；
  markBoards(board, flag, x0, y0);
  markBoards(board, flag, x1, y1);

  int count = INT_MAX;
  int result = 0;

  //没有可消除的跳出循环
  while (count > 0) {    
    //遍历整个局面，计算消除个数，并消除方块，垂直下降，返回消除个数
    count = EliminateAndCount(board, flag);
    result += count;

    //对下降后的新的局面重新标记
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (board[i][j] != '.') {
          markBoards(board, flag, i, j);
        }
      }
    }
  }
  return result;
}

//这种方法是参考csdn上找可消区域的枢轴 http://46aae4d1e2371e4aa769798941cef698.devproxy.yunshipei.com/loststephon/article/details/51223040
//但是方法是有误的，对于存在多个枢轴的情况下；
void iterEliminate(vector<string>& board, int& result) {
  int n = board.size();
  int m = board[0].size();  

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int x = i, y = j;
      int a = i, b = j, c = i, d = j;
      int sum = 0;

      if (board[i][j] != '.') {
        int ver_same = 0;
        while ((--a) >= 0 && board[a][j] == board[i][j])  ver_same++;
        while ((++c) < n && board[c][j] == board[i][j]) ver_same++;
        if (ver_same > 1) {
          sum += ver_same;
          int b1, d1, hor_same;
          int max_hor = 0;
          for (int k = a+1; k < c; ++k) {
            hor_same = 0;
            b1 = j; d1 = j;
            while ((--b1) >= 0 && board[k][b1] == board[k][j]) hor_same++;
            while ((++d1) < m && board[k][d1] == board[k][j]) hor_same++;
            if (hor_same > 1 && hor_same > max_hor) {
              b = b1; d= d1; x = k; 
              max_hor = hor_same;
            }
          }
          sum += max_hor;
        } else {
          a = i; c = i;
          int hor_same = 0;
          while ((--b) >= 0 && board[i][b] == board[i][j]) hor_same++;
          while ((++d) < m && board[i][d] == board[i][j]) hor_same++;
          if (hor_same > 1) {
            sum += hor_same;
            int a1, c1,ver_same;
            int max_ver = 0;
            for (int k = b+1; k < d; ++k) {
              ver_same = 0;
              a1 = i; c1 = i;
              while ((--a1) >= 0 && board[a1][k] == board[i][k]) ver_same++;
              while ((++c1) < n && board[c1][k] == board[i][k]) ver_same++;
              if (ver_same > 1 && ver_same > max_ver) {
                a = a1; c = c1; y = k;
                max_ver = ver_same;
              }
            }
            sum += max_ver;
          }
        }
      }

      if (sum > 1) {
        result += sum;
        result++;
        if (c - a  > 3) {
          for (int a0 = a; a0 >= 0; --a0) {
            board[a0+c-a-1][y] = board[a0][y];
          }
          for (int a0 = 0; a0 < c-a-1; ++a0) {
            board[a0][y] = '.';
          }
        }
        if (d - b > 3) {
          for (int b0 = b+1; b0 < d; ++b0) {
            for (int x0 = x-1; x0 >= 0; --x0) {
              board[x0+1][b0] = board[x0][b0];
            }
            board[0][b0] = '.';

          }
          for (int b0 = 0; b0 < d; ++b0) {

          }
        }
        iterEliminate(board, result);
      }

    }
  }
}


int main()
{
  ifstream cin("input.txt");
  int s, n, m;
  cin >> s;
  while (s--) {
    cin >> n >> m;
    vector<string> board(n);
    for (int i = 0; i < n; ++i) {
      cin >> board[i];
    }
    int x0, y0, x1, y1;
    cin >> x0 >> y0 >> x1 >> y1;

    //检查输入输出是否越界
    if (x0 < 0 || x0 >= n || y0 < 0 || y0 >= m 
      || x1 < 0 || x1 >= n || y1 < 0 || y1 >= m 
      || (x0 != x1 && y0 != y1)
      || (x0 == x1 && y0 == y1)) {
        cout << "0" << endl;
        continue;
    }

    //交换两个点
    char c = board[x0][y0];
    board[x0][y0] = board[x1][y1];
    board[x1][y1] = c;

    int result = 0; 
    //iterEliminate(board, result); 
    result = iterEliminateGame(board, x0, y0, x1, y1);
    cout << result << endl;
  }
  return 0;
}



