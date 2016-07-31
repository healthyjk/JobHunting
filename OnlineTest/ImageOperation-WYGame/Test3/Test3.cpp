// Test3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

vector<vector<int>> rotateClockwise(vector<vector<int>>& image) {
  vector<vector<int>> rotate;
  int n = image.size();
  int m = image[0].size();
  rotate.assign(m, vector<int>(n, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      rotate[j][n-1-i] = image[i][j];
    }
  }
  return rotate;
}

vector<vector<int>> rotateAntiClockwise(vector<vector<int>>& image) {
  vector<vector<int>> rotate;
  int n = image.size();
  int m = image[0].size();
  rotate.assign(m, vector<int>(n, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      rotate[m-1-j][i] = image[i][j];
    }
  }
  return rotate;
}

void rotateVertical(vector<vector<int>>& image) {
  int n = image.size();
  int m = image[0].size();
  int temp;
  for (int i = 0; i < n/2; ++i) {
    for (int j = 0; j < m; ++j) {
      temp = image[i][j];
      image[i][j] = image[n-1-i][j];
      image[n-1-i][j] = temp;
    }
  }
}

void rotateHorizontal(vector<vector<int>>& image) {
  int n = image.size();
  int m = image[0].size();
  int temp;
  for (int j = 0; j < m/2; ++j) {
    for (int i = 0; i < n; ++i) {
      temp = image[i][j];
      image[i][j] = image[i][m-1-j];
      image[i][m-1-j] = temp;
    }
  }
}

void addGrayLocal(vector<vector<int>>& image, vector<int>& args) {
  int n = image.size();
  int m = image[0].size();
  int imin, imax, jmin, jmax;
  imin = args[0] > args[2] ? args[2] : args[0];
  imax = args[0] > args[2] ? args[0] : args[2];
  jmin = args[1] > args[3] ? args[3] : args[1];
  jmax = args[1] > args[3] ? args[1] : args[3];

  for (int i = imin; i <= imax && i < n; ++i) {
    for (int j = jmin; j <= jmax && j < m; ++j) {
      image[i][j] += args[4];
      if (args[4] > 0 && image[i][j] > 255) image[i][j] = 255;
      if (args[4] < 0 && image[i][j] < 0) image[i][j] = 0;
    }
  }
}

vector<vector<int>> clipImage(vector<vector<int>>& image, vector<int>& args) {
  vector<vector<int>> clip;
  int n = image.size();
  int m = image[0].size();
  int imin, imax, jmin, jmax;

  imin = args[0] > args[2] ? args[2] : args[0];
  imax = args[0] > args[2] ? args[0] : args[2];
  jmin = args[1] > args[3] ? args[3] : args[1];
  jmax = args[1] > args[3] ? args[1] : args[3];

  clip.assign(imax-imin+1, vector<int>(jmax-jmin+1, 0));

  for (int i = imin; i <= imax && i < n; ++i) {
    for (int j = jmin; j <= jmax && j < m; ++j) {
      clip[i-imin][j-jmin] = image[i][j];
    }
  }

  return clip;
}


void printVector(vector<vector<int>> a) {
  for (int i = 0; i < a.size(); ++i) {
    for (int j = 0; j < a[0].size(); ++j) {
      cout << a[i][j] << "\t";
    }
    cout << endl;
  }
  cout << endl;
}

int main()
{
  ifstream cin("input.txt");
  int s, n, m;
  cin >> s;
  while (s--) {
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cin >> a[i][j];
      }
    }

    /*int b[] = {1,1,2,3};
    vector<int> vb(b, b+4);
    a = clipImage(a,vb);
    printVector(a);
   
    system("pause");*/

    int t;
    cin >> t;
    int type;
    while (t--) {
      cin >> type;
      switch(type) {
      case 1: a = rotateClockwise(a);break;
      case 2: a = rotateAntiClockwise(a);break;
      case 3: rotateHorizontal(a);break;
      case 4: rotateVertical(a);break;
      case 5: {
        vector<int> args(5, 0);
        for (int i = 0; i < 5; ++i) {
          cin >> args[i];
        }
        addGrayLocal(a, args);
        break;
              }
      case 6: {
        vector<int> args(5, 0);
        for (int i = 0; i < 5; ++i) {
          cin >> args[i];
        }
        args[4] = -args[4];
        addGrayLocal(a, args);
        break;
              }
      case 7: {
        vector<int> args(4, 0);
        for (int i = 0; i < 4; ++i) {
          cin >> args[i];
        }
        a = clipImage(a, args);
        break;
              }
      default: break;
      }
    }

    int an = a.size();
    int am = a[0].size();
    int sum = 0;
    for (int i = 0; i < an; ++i) {
      for (int j = 0; j < am; ++j) {
        sum += a[i][j];
      }
    }
    cout << an << " " << am << " " << a[0][0] << " " << sum << endl;
  }

  cout << endl;
  system("pause");
	return 0;
}

