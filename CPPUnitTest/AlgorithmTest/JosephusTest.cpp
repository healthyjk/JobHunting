#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>

using namespace std;

/**
  * 测试用例：Josephus问题解答，包含三种算法，最简单的数组和循环链表模拟，及O(n)复杂度的算法；
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/

SUITE(JosephusTest)
{
    struct Node {
        int val;
        Node* next;
    };

    class Solution {
    public:
        /*使用数组来实现*/
        int JosephusSolution1(int n, int m) {
            if (n <= 0) return -1;
            vector<bool> a(n, true);
            int count = n;
            int start = 0;
            int result = -1;
            while (count > 0) {
                for(int i = 0; i < m;i++) {
                    while (!a[start]) {
                        start = (start + 1) % n;
                    }
                    if (i == m-1) {
                        a[start] = false;
                        count--;
                        result = start;
                    }
                    start = (start + 1) % n;
                }
            }
            return result;
        }

        /*使用链表来实现*/
        int JosephusSolution2(int n, int m) {
            int result = -1;
            if (n < 1) return result;
            if (n == 1) {
                return 0;
            }
            Node *p, *head, *curr, *r, *h;
            /*建立循环链表*/
            head = new Node();
            head->val = 0;
            head->next = head;//循环链表
            curr = head;
            for (int i = 1; i < n; ++i) {
                p = new Node();
                p->val = i;
                p->next = curr->next;
                curr->next = p;
                curr = p;
            }

            h = head;
            r = h;
            while (n--) {
                for (int i = m-1; i > 0; --i) {
                    r = h;
                    h = h->next;
                }
                r->next = h->next;
                result = h->val;
                delete h;
                h = r->next;
            }
            return result;
        }

        /*直接使用递推公式：
          f[1] = 0
          f[n] = (f[n -1] + m) % n
          该算法的时间复杂度为O(N)，空间复杂度为O(1)。对于N不是很大的数据来说，可以解决。*/
        int BestJosephusSolution_1(int n, int m) {
            int ret = 0;
            for (int i = 2; i <= n; ++i) {
                ret = (ret + m) % i;
            }
            return ret;
        }

        /*上述递推公式对于n很大的情况下仍然很慢，再做进一步的优化：
          对于n > m的情况， 第一次可以消除掉n/m个元素，剩下(n-n/m)个元素；
          假设F[n-n/m, k] = s, 那么有：
          s < n%m : s' = s + (n - n/m);
          s >= n%m : s' = s - (n%m) + (s - n%m)/(m-1) */
        int BestJosephusSolution_2(int n, int m) {
            if (n == 1) return 0;
            int last;
            if (n < m) {
                last = 0;
                for (int i = 2; i <= n; ++i) {
                    last = (last + m) % i;
                }
                return last;
            }
            last = BestJosephusSolution_2(n - (n/m), m);
            if (last < (n % m)) {
                last = last - (n % m) + n;
            } else {
                last = last - (n % m) + (last - (n % m)) / (m-1);
            }
            return last;
        }
    };

    TEST_FIXTURE(Solution, Normal1)
    {
        int result = JosephusSolution1(10,3);
        CHECK_EQUAL(3, result);
        result = JosephusSolution1(5,3);
        CHECK_EQUAL(3, result);
        result = JosephusSolution1(8,3);
        CHECK_EQUAL(6, result);
        return;
    }

    TEST_FIXTURE(Solution, Normal2)
    {
        int result = JosephusSolution2(10,3);
        CHECK_EQUAL(3, result);
        result = JosephusSolution2(5,3);
        CHECK_EQUAL(3, result);
        result = JosephusSolution2(8,3);
        CHECK_EQUAL(6, result);
        return;
    }

    TEST_FIXTURE(Solution, Normal3)
    {
        int result = BestJosephusSolution_1(10,3);
        CHECK_EQUAL(3, result);
        result = BestJosephusSolution_1(5,3);
        CHECK_EQUAL(3, result);
        result = BestJosephusSolution_1(8,3);
        CHECK_EQUAL(6, result);
        return;
    }

    TEST_FIXTURE(Solution, Normal4)
    {
        int result = BestJosephusSolution_2(10,3);
        CHECK_EQUAL(3, result);
        result = BestJosephusSolution_2(5,3);
        CHECK_EQUAL(3, result);
        result = BestJosephusSolution_2(8,3);
        CHECK_EQUAL(6, result);
        return;
    }
}
