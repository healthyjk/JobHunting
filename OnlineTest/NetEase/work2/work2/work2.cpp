// work2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include <fstream>

using namespace std;


struct Step {
  int x;
  int y;
  int color;
};


void getCurrentNum(vector<string>& board, int& white, int& black) {
  white = 0;
  black = 0;
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if (board[i][j] == '*') {
        black++;
      } else if (board[i][j] == 'o') {
        white++;
      }
    }
  }
  //cout << white << "," << black << endl;
}

void goStep(vector<string>& board, Step& step, int& white, int& black) {
  board[step.x][step.y] = (step.color == 0) ? '*' : 'o';

  char cur = (step.color == 0) ? '*' : 'o';
  char rev = (step.color == 1) ? '*' : 'o';

  if (cur == '*') {
    black++;
  } else {
    white++;
  }

  int left = step.x - 1;
  int temp = 0;
  while (left >= 0 && board[left][step.y] == rev) {
    temp++;
    left--;
  }
  if (left < 0) {
    temp = 0;
  } else {
    if (board[left][step.y] == cur) {
      for (int i = step.x - 1; i > left; --i) {
        board[i][step.y] = cur;
        if (cur == '*') {
          black++;
          white--;
        } else {
          white++;
          black--;
        }
      }
    }
  }

  //向下
  int right = step.x + 1;
  temp = 0;
  while (right < 8 && board[right][step.y] == rev) {
    temp++;
    right++;
  }
  if (right == 8) {
    temp = 0;
  } else {
    if (board[right][step.y] == cur) {
      for (int i = step.x + 1; i < right; ++i) {
        board[i][step.y] = cur;
        if (cur == '*') {
          black++;
          white--;
        } else {
          white++;
          black--;
        }
      }
    }
  }


  //向上
  int up = step.y - 1;
  temp = 0;
  while (up >= 0 && board[step.x][up] == rev) {
    temp++;
    up--;
  }
  if (up < 0) {
    temp = 0;
  } else {
    if (board[step.x][up] == cur) {
      for (int i = step.y - 1; i > up; --i) {
        board[step.x][i] = cur;
        if (cur == '*') {
          black++;
          white--;
        } else {
          white++;
          black--;
        }
      }
    }
  }


  //向下
  int down = step.y + 1;
  temp = 0;
  while (down < 8 && board[step.x][down] == rev) {
    temp++;
    down++;
  }
  if (down == 8) {
    temp = 0;
  } else {
    if (board[step.x][down] == cur) {
      for (int i = step.y + 1; i < down; ++i) {
        board[step.x][i] = cur;
        if (cur == '*') {
          black++;
          white--;
        } else {
          white++;
          black--;
        }
      }
    }
  }

  //左上
  int leftup_x = step.x - 1;
  int leftup_y = step.y - 1;
  temp = 0;
  while (leftup_x>= 0 &&  leftup_y >= 0 && board[leftup_x][leftup_y] == rev) {
    temp++;
    leftup_x--;
    leftup_y--;
  }
  if (leftup_x < 0 || leftup_y < 0) {
    temp = 0;
  } else {
    if (board[leftup_x][leftup_y] == cur) {
      for (int i = step.x - 1, j = step.y - 1; i > leftup_x && j > leftup_y; --i, --j) {
        board[i][j] = cur;
        if (cur == '*') {
          black++;
          white--;
        } else {
          white++;
          black--;
        }
      }
    }
  }

  //左下
  int leftdown_x = step.x - 1;
  int leftdown_y = step.y + 1;
  temp = 0;
  while (leftdown_x>= 0 &&  leftdown_y < 8 && board[leftdown_x][leftdown_y] == rev) {
    temp++;
    leftdown_x--;
    leftdown_y++;
  }
  if (leftdown_x < 0 || leftdown_y == 8) {
    temp = 0;
  } else {
    if (board[leftdown_x][leftdown_y] == cur) {
      for (int i = step.x - 1, j = step.y + 1; i > leftdown_x && j < leftdown_y; --i, ++j) {
        board[i][j] = cur;
        if (cur == '*') {
          black++;
          white--;
        } else {
          white++;
          black--;
        }
      }
    }
  }


  //右上
  int rightup_x = step.x + 1;
  int rightup_y = step.y - 1;
  temp = 0;
  while (rightup_x < 8 &&  rightup_y >= 0 && board[rightup_x][rightup_y] == rev) {
    temp++;
    rightup_x++;
    rightup_y--;
  }
  if (rightup_x == 8 || rightup_y < 0) {
    temp = 0;
  } else {
    if (board[rightup_x][rightup_y] == cur) {
      for (int i = step.x + 1, j = step.y - 1; i < rightup_x && j > rightup_y; ++i, --j) {
        board[i][j] = cur;
        if (cur == '*') {
          black++;
          white--;
        } else {
          white++;
          black--;
        }
      }
    }
  }

  //右下
  int rightdown_x = step.x + 1;
  int rightdown_y = step.y + 1;
  temp = 0;
  while (rightdown_x < 8 &&  rightdown_y < 8 && board[rightdown_x][rightdown_y] == rev) {
    temp++;
    rightdown_x++;
    rightdown_y++;
  }
  if (rightdown_x == 8 || rightdown_y == 8) {
    temp = 0;
  } else {
    if (board[rightdown_x][rightdown_y] == cur) {
      for (int i = step.x + 1, j = step.y + 1; i < rightdown_x && j < rightdown_y; ++i, ++j) {
        board[i][j] = cur;
        if (cur == '*') {
          black++;
          white--;
        } else {
          white++;
          black--;
        }
      }
    }
  }

}

void computeRemain(vector<string>& board, vector<Step>& steps, int& white, int& black) {
  getCurrentNum(board, white, black);
  int n = steps.size();
  for (int i = 0; i < n; ++i) {
    goStep(board, steps[i], white, black);
  }
}

int main()
{
  ifstream cin("input.txt");
  int s;
  cin >> s;
  while (s--) {

    vector<string> board(8,"");
    for (int i = 0; i < 8; ++i) {
      cin >> board[i];
    }

    int n;
    cin >> n;
    vector<Step> steps(n);
    for (int i = 0; i < n; ++i) {
      cin >> steps[i].x >> steps[i].y >> steps[i].color;
    }

    int white, black;
    computeRemain(board, steps, white, black);

    cout << black << " " << white << endl;

  }

  return 0;
}



