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

SUITE(OfferTest)
{
    class Solution {
    public:
        /*小于n的数中1出现的个数*/
        int NumberOf1Between1AndN_Solution(int n)
        {
            int lowNumber = 0;
            int curentNum = 0;
            int hightNumber = 0;
            int count = 0;
            int k = 1;

            while (n >= k) {
                lowNumber = n - (n / k * k);
                hightNumber = n / (k * 10);
                curentNum = (n / k) % 10;
                switch(curentNum) {
                case 0:
                    count += hightNumber * k;
                    break;
                case 1:
                    count += hightNumber * k + lowNumber + 1;
                    break;
                default:
                    count += (hightNumber + 1) * k;
                    break;
                }
                k *= 10;
            }
            return count;
        }

        /*题目描述：把只包含因子2、3和5的数称作丑数（Ugly Number）。例如6、8都是丑数，但14不是，
         * 因为它包含因子7。 习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。*/
        /*主要解题思想：在数组中必定有一个丑数M2， 在它之前的数 * 2 都小于当前最大丑数， 在它之后的数 * 2都大于当前最大丑数， 同样有M3, M5；
         * 显然，当前位置的下一个数肯定是之前某个位置的数*2、*3、*5的结果，这3个数要比当前位置的数大才能候选，选的时候选3个数里面最小的那个，
         * 有人说这还用比吗，一定是*2最小，如果是同一个数*2*3*5肯定是*2的最小，但是这个“某个位置的数”是不同的，*5的数可能因为更靠前而比*2的数小。
         * 现在要做的就是把“某个位置”记住，对于*2、*3、*5分别有一个位置满足各自位置的数*2、*3、*5刚好大于当前位置的数，
         * 所谓“刚好”的意思就是各自“某个位置”前一个位置的数*2、*3、*5小于当前数。*/
        int GetUglyNumber_Solution(int index) {
            if (index < 7) return index;
            vector<int> num(index);
            num[0] = 1;
            int t2 = 0;
            int t3 = 0;
            int t5 = 0;
            for (int i = 1; i < index; ++i) {
                //LOG(INFO) << "t2 = " << t2 << ", t3 = " << t3 << ", t5 = " << t5;
                //LOG(INFO) << "min(" << (num[t2] * 2) << ", " << (num[t3] * 3) << ", " << (num[t5] * 5) << ")";
                num[i] = std::min(num[t2] * 2, num[t3] * 3);
                num[i] = std::min(num[i], num[t5] * 5);
                if (num[i] == num[t2] * 2) t2++;
                if (num[i] == num[t3] * 3) t3++;
                if (num[i] == num[t5] * 5) t5++;
                //LOG(INFO) << "i = " << i << ", num = " << num[i];
            }
            return num[index - 1];
        }

        /*采用归并排序计算数组逆序对，注意中间结果采用long long存储*/
        int MergeSort(vector<int>& input) {
            int n = input.size();
            if (n <= 0) return 0;
            return MergeSortIter(input, 0, n-1) % 1000000007;
        }

        /*归并排序递归函数：从上倒下的递归排序*/
        long long MergeSortIter(vector<int>& input, int begin, int end) {
            if (end <= begin) return 0;
            int middle = (begin + end) / 2;
            long long leftCount = MergeSortIter(input, begin, middle);
            long long rightCount = MergeSortIter(input, middle+1, end);
            long long count = MergeTwoSorted(input, begin, middle, end);
            return leftCount + rightCount + count;
        }

        long long MergeTwoSorted(vector<int>& input, int begin, int middle, int end) {
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
            long long count = 0;
            while (i < len_a && j < len_b) {
                if (a[i] <= b[j]) {
                    input[k++] = a[i];
                    i++;
                } else {
                    input[k++] = b[j];
                    j++;
                    /*在MergeSort中合并数组时添加一行统计逆序对即可；
                    统计思路：如果a[i]大于b[j],由于a[i]由小到大有序，因此a[i]后的所有元素大于b[j]*/
                    count += len_a - i;
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
            return count;
        }

        /*LeetCode：最后剩下来的数，效率不行，解法超时*/
        int lastRemaining(int n) {
            if (n <= 0) return -1;
            vector<bool> flag(n, true);

            int remain = n;
            int gap = 2;
            int start = 0;
            while (remain > 1) {
                start = 0;
                for (; start < n && !flag[start]; ++start);

                for (int i = start; i < n; i = i + gap) {
                    flag[i] = false;
                    remain--;
                }
                if (remain == 1) break;

                start = n-1;
                for (; start >= 0 && !flag[start]; --start);

                gap <<= 1;
                for (int i = start; i >= 0; i = i - gap) {
                    flag[i] = false;
                    remain--;
                }
                gap <<= 1;
            }

            for (int i = 0; i < n; ++i) {
                if (flag[i]) return (i+1);
            }
            return -1;
        }
    };

    /*小于n的数中1出现的次数测试*/
    TEST_FIXTURE(Solution, Normal1)
    {
        int result = NumberOf1Between1AndN_Solution(6);
        CHECK_EQUAL(result, 1);
        result = NumberOf1Between1AndN_Solution(13);
        CHECK_EQUAL(result, 6);
        result = NumberOf1Between1AndN_Solution(1213);
        CHECK_EQUAL(result, 660);
        return;
    }

    /*寻找丑数测试*/
    TEST_FIXTURE(Solution, Normal2)
    {
        GetUglyNumber_Solution(20);
        return;
    }

    /*归并排序计算逆序对的测试*/
    TEST_FIXTURE(Solution, Normal3)
    {
        vector<int> data = {364,637,341,406,747,995,234,971,571,219,993,407,416,366,
                            315,301,601,650,418,355,460,505,360,965,516,648,727,667,
                            465,849,455,181,486,149,588,233,144,174,557,67,746,550,
                            474,162,268,142,463,221,882,576,604,739,288,569,256,936,
                            275,401,497,82,935,983,583,523,697,478,147,795,380,973,
                            958,115,773,870,259,655,446,863,735,784,3,671,433,630,425,
                            930,64,266,235,187,284,665,874,80,45,848,38,811,267,575};
        int result = MergeSort(data);
        CHECK_EQUAL(2519, result);
        return;
    }

    /*最后剩下来的数测试*/
    TEST_FIXTURE(Solution, Normal4)
    {

        int result = lastRemaining(9);
        CHECK_EQUAL(6, result);
        return;
    }
}
