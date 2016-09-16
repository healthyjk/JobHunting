#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：代码测试模版用于拷贝
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/

SUITE(SortTest)
{
    class Solution {
    public:
        /*归并排序：分治算法，将数组不断切分到长度为2的大小*/
        void MergeSort(vector<int>& input) {
            int n = input.size();
            if (n <= 0) return;
            MergeSortIter(input, 0, n-1);
        }

        /*归并排序递归函数：从上倒下的递归排序*/
        void MergeSortIter(vector<int>& input, int begin, int end) {
            if (end <= begin) return;
            int middle = (begin + end) / 2;
            MergeSortIter(input, begin, middle);
            MergeSortIter(input, middle+1, end);
            MergeTwoSorted(input, begin, middle, end);
        }

        void MergeTwoSorted(vector<int>& input, int begin, int middle, int end) {
            int len_a = middle - begin + 1;
            int len_b = end - middle;

            vector<int> a(len_a);
            for (int i = 0; i < len_a; ++i) {
                a[i] = input[i + begin];
            }
            vector<int> b(len_b);
            for (int i = 0; i < len_b; ++i) {
                b[i] = input[i + middle + 1];
            }

            int i = 0;
            int j = 0;
            int k = begin;
            while (i < len_a && j < len_b) {
                if (a[i] > b[j]) {
                    input[k++] = a[i];
                    i++;
                } else {
                    input[k++] = b[j];
                    j++;
                }
            }

            while (i != len_a) {
                input[k++] = a[i];
                i++;

            }
            while (j != len_b) {
                input[k++] = b[j];
                j++;
            }
            return;
        }
    };

    TEST_FIXTURE(Solution, Normal1)
    {
        vector<int> a = {1, 6, 3, 5, 9, 4};
        MergeSort(a);
        return;
    }

    TEST_FIXTURE(Solution, Normal2)
    {
        vector<int> a = {1, 4, 3, 9, 9, 4};
        MergeSort(a);
        //CHECK_EQUAL(a[4], 9);
        return;
    }

    TEST_FIXTURE(Solution, Normal3)
    {
        return;
    }
}
