// LastRemaining_Solution.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Solution {
public:
    // 这是最简单的做法，使用模拟过程来得到结果，但实际上hihocoder上提供了更简单的做法，
    // 因此最后出队的情况基本上是确定的，可以更快的过滤
    int LastRemaining_Solution_1(unsigned int n, unsigned int m) {
        if (n <= 0) return -1;
        
        vector<bool> stillInGame(n, true);
        int start = 0;
        
        for (int i = 0; i < n-1; ++i) {
            int count = 0;
            for (int j = start; ; ) {
                if (stillInGame[j]) {
                    if ((++count) == m) {
                        stillInGame[j] = false;
                        start = (j + 1) % n;
                        break;
                    }
                }

                j = (j + 1) % n;
            }
        }
        
        for (int i = 0; i < n; ++i) {
            if (stillInGame[i]) {
                return i;
            }
        }
        
        return -1;
    }

    //hihocoder上的做法：需要切记这种做法，貌似剑指offer上也有解法，要看一看
    int LastRemaining_Solution(unsigned int n, unsigned int m) {
        if (n <= 0) return -1;

    }
};

int main()
{
  int n, m;
  Solution solution;

  while (cin >> n >> m) {
    int remain = solution.LastRemaining_Solution(n, m);
    cout << "remain:" << remain << endl;
  }

	return 0;
}

