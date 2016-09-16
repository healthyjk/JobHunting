#include "UnitTest++/UnitTest++.h"
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：汉诺塔游戏
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/
SUITE(HanioGameTest)
{
    class Solution {
    public:
        int move(int n, const string& from, const string& to) {
            //LOG(INFO) << "move " << n << " from " << from << " to " << to << endl;
            return 1;
        }

        //普通的汉诺塔，三根柱子
        int hanio_normal(int n, const string& left, const string& mid, const string& right) {
            if (n <= 0) return 0;
            if (n == 1) {
                return move(n, left, right);
            } else {
                int step1 = hanio_normal(n-1, left, right, mid);
                int step2 = move(n, left, right);
                int step3 = hanio_normal(n-1, mid, left, right);
                return step1 + step2 + step3;
            }
        }

        //汉诺塔规则修改：不允许直接从最左边移动到最右边或者从最右边移动到最左边，必须经过中间
        //牛客上左程云的做法
        int hanio_special(int n, const string& left, const string& mid, const string& right) {
            if(n <=0) return 0;
            return process(n, left, mid, right, left, right);
        }

        int process(int n, const string& left, const string& mid, const string& right,
                    const string& from, const string& to) {
            if (n == 1) {
                if (from == mid || to == mid) {
                    return move(n, from, to);
                } else {
                    return (move(n, from, mid) + move(n, mid, to));
                }
            }
            if (from == mid || to == mid) {
                string another = (from == left || to == left) ? right : left;
                int step1 = process(n-1,left, mid, right, from, another);
                int step2 = move(n, from, to);
                int step3 = process(n-1,left, mid, right, another, to);
                return step1+step2+step3;
            } else {
                int step1 = process(n-1,left, mid, right, from, to);
                int step2 = move(n, from, mid);
                int step3 = process(n-1,left, mid, right, to, from);
                int step4 = move(n, mid, to);
                int step5 = process(n-1,left, mid, right, from, to);
                return step1+step2+step3+step4+step5;
            }
        }

        /*下面这种是错误解法, 步数多了:从left移到right不应该展开，也不能展开*/
        int hanio_special_1(int n, const string& left, const string& mid, const string& right, const string& from, const string& to) {
            if (n == 0) return 0;
            if (from == mid || to == mid) {
                string another = (from == left || to == left) ? right : left;
                int step1 = hanio_special_1(n-1,left, mid, right, from, to);
                int step2 = hanio_special_1(n-1,left, mid, right, to, another);
                int step3 = move(n, from, to);
                int step4 = hanio_special_1(n-1,left, mid, right, another, to);
                return step1+step2+step3+step4;
            } else {
                int step1 = hanio_special_1(n-1,left, mid, right, from, mid);
                int step2 = hanio_special_1(n-1,left, mid, right, mid, to);
                int step3 = move(n, from, mid);
                int step4 = hanio_special_1(n-1,left, mid, right, to, mid);
                int step5 = hanio_special_1(n-1,left, mid, right, mid, from);
                int step6 = move(n, mid, to);
                int step7 = hanio_special_1(n-1,left, mid, right, from, mid);
                int step8 = hanio_special_1(n-1,left, mid, right, mid, to);
                return step1+step2+step3+step4+step5+step6+step7+step8;
            }
            return 0;
        }

        /*传统汉诺塔游戏的非递归版本, 暂未理解*/
        int hanio_normal_stack(int n, const string& left, const string& mid, const string& right) {
            if(n <=0) return 0;
            char order[2][256];
            char pos[64];
            order[0]['A'] = 'B';
            order[0]['B'] = 'C';
            order[0]['C'] = 'A';
            order[1]['A'] = 'C';
            order[1]['B'] = 'A';
            order[1]['C'] = 'B';
            //0是顺序 1是逆序
            int index[64];
            //确定轨迹的顺序还是逆序
            int i, j, m;
            for(i = n; i > 0; i -= 2)
                index[i] = 1;
            for(i = n - 1; i > 0; i -= 2)
                index[i] = 0;
            memset(pos, 'A', sizeof(pos));
            for(i = 1; i < (1 << n); i ++)
            {
                for(m = 1, j = i; j%2 == 0; j/=2, m ++);
                cout << m <<" : "<< pos[m]  <<" --> " << order[index[m]][pos[m]] << endl;
                pos[m] = order[index[m]][pos[m]];
            }
            return 0;
        }

        /*改进版本的汉诺塔的非递归版本，使用三个栈：只有四种动作：L->M， M->R， R->M，M->L；*/
        /*遵循两个原则：1.小压大； 2. 相邻动作不能互逆*/
        int hanio_special_stack(int n, const string& left, const string& mid, const string& right) {
            if(n <=0) return 0;
            return process_stack(n, left, mid, right);
        }

        enum MoveState{
            INIT,
            LTOM,
            MTOR,
            RTOM,
            MTOL
        };

        int process_stack(int n, const string& left, const string& mid, const string& right) {
            stack<int> left_stack;
            stack<int> mid_stack;
            stack<int> right_stack;

            left_stack.push(INT_MAX);
            mid_stack.push(INT_MAX);
            right_stack.push(INT_MAX);



            for (int i = n; i >= 1; --i) {
                left_stack.push(i);
            }

            int count = 0;
            MoveState last_state = INIT;
            while (right_stack.size() < (n+1)) {
                //L->M
                if (last_state != MTOL && left_stack.top() < mid_stack.top()) {
                    mid_stack.push(left_stack.top());
                    count += move(left_stack.top(), left, mid);
                    left_stack.pop();
                    last_state = LTOM;
                    continue;
                }
                //M->R
                if (last_state != RTOM && mid_stack.top() < right_stack.top()) {
                    right_stack.push(mid_stack.top());
                    count += move(mid_stack.top(), mid, right);
                    mid_stack.pop();
                    last_state = MTOR;
                    continue;
                }

                //R->M
                if (last_state != MTOR && right_stack.top() < mid_stack.top()) {
                    mid_stack.push(right_stack.top());
                    count += move(right_stack.top(), right, mid);
                    right_stack.pop();
                    last_state = RTOM;
                    continue;
                }

                //M->L
                if (last_state != LTOM && mid_stack.top() < left_stack.top()) {
                    left_stack.push(mid_stack.top());
                    count += move(mid_stack.top(), mid, left);
                    mid_stack.pop();
                    last_state = MTOL;
                    continue;
                }
            }
            return count;
        }
    };

    TEST_FIXTURE(Solution, Normal1)
    {
        int result = hanio_normal(3, "left", "mid", "right");
        CHECK_EQUAL(7, result);
        result = hanio_normal(4, "left", "mid", "right");
        CHECK_EQUAL(15, result);
        return;
    }

    TEST_FIXTURE(Solution, Normal2)
    {
        int result = hanio_special(3, "left", "mid", "right");
        //LOG(INFO) << "result:" << result;
        CHECK_EQUAL(26, result);
        return;
    }

    TEST_FIXTURE(Solution, Normal3)
    {
        int result = hanio_special_stack(3, "left", "mid", "right");
        //LOG(INFO) << "result:" << result;
        CHECK_EQUAL(26, result);
        return;
    }

    TEST_FIXTURE(Solution, Normal4)
    {
        int result = hanio_normal_stack(3, "left", "mid", "right");
        //LOG(INFO) << "result:" << result;
        //CHECK_EQUAL(26, result);
        return;
    }
}
