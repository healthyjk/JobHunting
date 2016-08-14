#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

/**
  * 测试用例：计算矩阵中最大的矩形面积,方法跟计算直方图中最大面积相同，只需要枚举矩形中的baseline，将其转化为一维高度即可；
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/
SUITE(MaxRectangleInMatrixTest)
{
    class Solution {
    public:
        int maximalRectangle(vector<vector<char>>& matrix) {
            int n = matrix.size();
            if (n <= 0) return 0;
            int m = matrix[0].size();
            if (m <= 0) return 0;

            int max_area = 0;
            int area;
            int top;
            int temp;
            stack<int> s;

            for (int k = 0; k < m; ++k) {
                vector<int> heights(n+1, 0);
                for (int l = 0; l < n; ++l) {
                    temp = k;
                    while (temp < m && matrix[l][temp++] == '1') heights[l]++;
                }

                while (!s.empty()) { s.pop(); }

                s.push(-1);
                heights[n] = -1;

                int i = 0;
                while (i < (n+1)) {
                    if (s.top() < 0 || heights[s.top()] <= heights[i]) {
                        s.push(i++);
                    } else {
                        top = s.top();
                        s.pop();
                        area = heights[top] * (s.empty() ? i : (i - s.top() -1));

                        if (area > max_area) {
                            max_area = area;
                        }
                    }
                }
            }

            return max_area;
        }
    };

    TEST_FIXTURE(Solution, Normal)
    {
        //C++ 11支持的列表初始化
        vector<vector<char>> matrix = {{'1','0','1','0','0'},
                                       {'1','0','1','1','1'},
                                       {'1','1','1','1','1'},
                                       {'1','0','0','1','0'}};
        int max_area = maximalRectangle(matrix);
        CHECK_EQUAL(6, max_area);
    }
}
