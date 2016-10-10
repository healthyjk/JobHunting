// work3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

int Solution() {

  return 0;
}



int main()
{
  ifstream cin("input.txt");
  int s;
  cin >> s;
  while (s--) {
    int n, l;
    cin >> n >> l;
    vector<int> id(l, 0);
    vector<int> id2(l, 0);

    for (int i = 0; i < l; ++i) {
      cin >> id[i];
      id2[i] = id[i];
    }

    id2.erase(unique(id2.begin(), id2.end()), id2.end());
    if (l <= n) {
      if (id2.size() != id.size()) {
        cout << "B" << endl;
      } else {
        cout << "CAN'T DECIDE" << endl;
      }
      continue;
    }


    bool flag = false;
    vector<int> all_id(n+1);

    for (int i = 0; i < n; ++i) {
      bool temp = true;
      for (int j = i; j < id.size(); j+= n) {
        for (int i = 1; i <= n; ++i) {
          all_id[i] = -1;
        }
        for (int i = 0; i < n && (j+i) < id.size(); ++i) {
          if (all_id[id[j+i]] == -1) {
            all_id[id[j+i]] = i;
          } else {
            temp = false;
          }
        }

        if (!temp) {
          break;
        }
      }

      //cout << i << "," << temp << endl;

      if (temp) {
        flag = true;
        break;
      }
    }



    if (flag) {
      cout << "CAN'T DECIDE" << endl;
    } else {
      cout << "B" << endl;
    }


  }

  return 0;
}
