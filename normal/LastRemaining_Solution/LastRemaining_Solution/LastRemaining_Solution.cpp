// LastRemaining_Solution.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Solution {
public:
    // ������򵥵�������ʹ��ģ��������õ��������ʵ����hihocoder���ṩ�˸��򵥵�������
    // ��������ӵ������������ȷ���ģ����Ը���Ĺ���
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

    //hihocoder�ϵ���������Ҫ�м�����������ò�ƽ�ָoffer��Ҳ�нⷨ��Ҫ��һ��
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

