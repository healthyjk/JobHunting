// FirstOnceChar.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        int n = str.size();
        if (n <= 0) return -1;
        vector<int> pos(52, 0);
        for (int i = 0; i < n; ++i) {
            int index = 0;
            if (str[i] >= 'a' && str[i] <= 'z') {
                index = str[i] - 'a';
            } else if (str[i] >= 'A' && str[i] <= 'Z') {
				index = str[i]-'A' + 26;
            } else {
				continue;
            }
            if (pos[index] < 0) {
                continue;
            } else if (pos[index] == 0) {
                pos[index] = i+1;
            } else {
                pos[index] = -1;
            }
        }
        int result = INT_MAX;
        for (int i = 0; i < 52; ++i) {
            if (pos[i] > 0 && pos[i] < result) {
                result = pos[i];
            }
        }
        if (result != INT_MAX) {
            return (result-1);
        }
        return -1;
    }
};


int main()
{
	Solution solution;
	string testStr = "NXWtnzyoHoBhUJaPauJaAitLWNMlkKwDYbbigdMMaYfkVPhGZcrEwp";
	int index = solution.FirstNotRepeatingChar(testStr);
	cout << "pos: " << index << endl;
	return 0;
}

