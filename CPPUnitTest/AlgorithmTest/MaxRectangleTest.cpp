#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

/**
  * 测试用例：计算直方图中最大的矩形面积
  * 作者：yanjiankang
  * 时间：2016年8月11日
  **/
SUITE(MaxRectangleTest)
{
    class Solution {
    public:
        /*这个版本的代码通过在栈中预先放入一个-1，并且在高度数组末尾放入-1，从而避免栈空的判断*/
        int largestRectangleArea(vector<int>& heights) {
            int n = heights.size();
            if (n <= 0) return 0;

            int max_area = 0;
            int area;
            int top;
            stack<int> s;
            s.push(-1);
            heights.push_back(-1);

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
            return max_area;
        }

        int largestRectangleArea_normal(vector<int>& heights) {
            int n = heights.size();
            if (n <= 0) return 0;

            int max_area = 0;
            int area;
            int top;
            stack<int> s;

            int i = 0;
            while (i < n) {
                if (s.empty() || heights[s.top()] <= heights[i]) {
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

            while (!s.empty()) {
                top = s.top();
                s.pop();
                area = heights[top] * (s.empty() ? i : (i - s.top() -1));

                if (area > max_area) {
                    max_area = area;
                }
            }

            return max_area;
        }
    };

    TEST_FIXTURE(Solution, Normal)
    {
        vector<int> heights = {2,1,5,6,2,3};
        int max_area = largestRectangleArea(heights);
        CHECK_EQUAL(10, max_area);
    }

    TEST_FIXTURE(Solution, OnlyOne)
    {
        vector<int> heights = {0, 9};
        int max_area = largestRectangleArea(heights);
        CHECK_EQUAL(9, max_area);
    }

    TEST_FIXTURE(Solution, NoExtraNormal)
    {
        vector<int> heights = {2,1,5,6,2,3};
        int max_area = largestRectangleArea_normal(heights);
        CHECK_EQUAL(10, max_area);
    }

    TEST_FIXTURE(Solution, NoExtraOnlyOne)
    {
        vector<int> heights = {0, 9};
        int max_area = largestRectangleArea_normal(heights);
        CHECK_EQUAL(9, max_area);
    }
}
