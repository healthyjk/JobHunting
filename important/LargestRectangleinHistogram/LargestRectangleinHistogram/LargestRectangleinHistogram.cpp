// LargestRectangleinHistogram.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
		int n = heights.size();
		if (n <= 0) return 0;

		long long area = 0;
		long long max_area = 0;
        stack<int> s;
		int i = 0; 
		int top;
        while (i < n) {
            if (s.empty() || heights[i] >= heights[s.top()]) {
                s.push(i++);
            } else {
                top = s.top();
                s.pop();
                area = heights[top] * (s.empty() ? i : (i - s.top() - 1));
                if (area > max_area) {
                    max_area = area;
                }
            }
        }

		while (!s.empty()) {
			top = s.top();
            s.pop();
            area = heights[top] * (s.empty() ? i : (i - s.top() - 1));
            if (area > max_area) {
                max_area = area;
            }
		}

        return max_area;
    }
};

void TestCase1(Solution solution) {
	int a[] = {2,1,5,6,2,3};
	vector<int> va(a, a+sizeof(a)/sizeof(int));
	int area = solution.largestRectangleArea(va);
	cout << area << endl;
}

void TestCase2(Solution solution) {
	int a[] = {1};
	vector<int> va(a, a+sizeof(a)/sizeof(int));
	int area = solution.largestRectangleArea(va);
	cout << area << endl;
}

int main()
{
	Solution solution;

	TestCase1(solution);
	TestCase2(solution);

	return 0;
}

