#include "UnitTest++/UnitTest++.h"
#include <vector>
#include <iostream>
#include <cmath>
#include "EasyLogging/easylogging++.h"

using namespace std;

/**
  * 测试用例：Hihocoder Offer收割挑战赛
  * 作者：yanjiankang
  * 时间：2016年8月14日
  **/
SUITE(HihoCoder0814Test)
{
    class Solution {
    public:
        /* 第一题： 小Hi的防护盾
         * 题目描述：小Ho的虚拟城市正在遭受小Hi的攻击，小Hi用来攻击小Ho城市的武器是一艘歼星舰，
         * 这艘歼星舰会以T(T为大于0的整数)个单位时间的间隔向小Ho的城市轰击。歼星舰总共有N枚炮弹，其中第i枚会造成Ai点伤害值。
         * 幸好小Ho的城市有K层护盾，每层护盾可以抵挡M点伤害。当某次轰击使得伤害值达或超过M时，该层护盾就会被击碎；该次轰击溢出的伤害不会作用于下一层护盾；下一次轰击将由下一层护盾承受。
         * 同时，受损但尚未被击碎护盾会以每单位时间减少1点伤害值的速度修复自己，直到伤害值降为0。这就意味着小Hi的攻击间隔T越大，
         * 小Ho撑过这N枚炮弹的可能性就越大。那么问题来了，小Hi的攻击间隔T至少需要是多少，小Ho城市的防护护盾才能不被全部击破？*/
        int DefendAttack(string filename)
        {
            ifstream cin(filename);
            int n, m, k;
            cin >> n >> m >> k;
            vector<int> hurt(n);

            int dead = 0;
            for (int i = 0; i < n; ++i) {
                cin >> hurt[i];
                if (hurt[i] >= m) {
                    dead++;
                }
            }

            /*如果致命攻击次数超过了防护层数目，直接死亡*/
            if (k <= 0 || dead >= k) {
                cout << "-1" << endl;
                return 0;
            }

            int t = 0;
            int remainK, remainM;
            /*采用暴力解：直接从时间间隔为0开始尝试*/
            while (true) {
                remainK = k;
                remainM = m;
                for (int i = 0; i < n; ++i) {
                    if (hurt[i] >= remainM) {
                        remainK--;
                        remainM = m;
                    } else {
                        remainM -= hurt[i];
                        remainM = (remainM + t > m) ? m : (remainM + t);
                    }
                    if (remainK <= 0) break;
                }
                if (remainK <= 0) {
                    t++;
                } else {
                    break;
                }
            }

            /*此处为此题最大的坑，如果任意时间间隔，小hi的防护盾都不会被击碎；那么最小值不为0，而是1；*/
            if (t == 0) {
                cout << "1" << endl;
            } else {
                cout << t << endl;
            }
            return 0;
        }

        /*第二题：小Hi在虚拟世界中有一只小宠物小P。小P有K种属性，每种属性的初始值为Ai。
         * 小Ho送给了小Hi若干颗药丸，每颗药丸可以提高小P指定属性1点。通过属性值，
         * 我们可以计算小P的强力值=(C1^(1/B1))*(C2^(1/B2))*...*(CK^(1/BK))，
         * 其中Ci为小P第i项属性的最终值（Ai+药丸增加的属性）。
         * 已知小Ho送给小Hi的药丸一共有N颗，问小P的强力值最高能够达到多少？
         * 解题思路：暴力dfs解只能过30的数据 */
        double compute(vector<int>& a, vector<int>& b) {
            int n = a.size();
            double result = 1;
            for (int i = 0; i < n; ++i) {
                result *= pow((double)a[i], 1.0/(double)b[i]);
            }
            return result;
        }
        /*小Ho的强化值：暴力DFS解*/
        void dfs(vector<int>& a, vector<int>& b, int& n, double& max, int t) {
            int k = a.size();
            /*如果药丸用完*/
            if (n <= 0) {
                double current = compute(a, b);
                if (current > max) {
                    max = current;
                }
                return;
            }
            /*如果到了多项式最后一项*/
            if (k-1 == t) {
                a[t] += n;
                double current = compute(a, b);
                if (current > max) {
                    max = current;
                }
                a[t] -= n;
                return;
            }
            /*否则给当前多项式分配0-n颗药丸*/
            for (int i = n; i >= 0; --i) {
                a[t] += i;
                n = n - i;
                dfs(a, b, n, max, t+1);
                n += i;
                a[t] -= i;
            }
        }

        double DefendValue_force(string filename)
        {
            ifstream cin(filename);
            int n, k;
            double result = 0.0;
            while (cin >> n >> k) {
                vector<int> a(k);
                vector<int> b(k);
                for (int i = 0; i < k; ++i) {
                    cin >> a[i];
                }

                for (int i = 0; i < k; ++i) {
                    cin >> b[i];
                }
                dfs(a, b, n, result, 0);
                //printf("%.2lf\n", result);
            }
            return result;
        }

        double DefendValue_greedy(string filename)
        {
            ifstream cin(filename);
            int n, k;
            double result = 0.0;
            while (cin >> n >> k) {
                vector<int> a(k);
                vector<int> b(k);

                for (int i = 0; i < k; ++i) {
                    cin >> a[i];
                }

                for (int i = 0; i < k; ++i) {
                    cin >> b[i];
                }

                result = GreedyFind(a, b, n, k);
            }
            return result;
        }

        /*贪心算法，每一颗药丸都给全局最大的*/
        double GreedyFind(vector<int>& a, vector<int>& b, int n, int k) {
            if (k <= 0) return 0.0;
            while (n--) {
                double value = 0;
                int index = 0;
                for (int i = 0; i < k; ++i) {
                    double temp = pow((a[i] + 1)/(double)a[i], 1.0 / (double)b[i]);
                    if (temp > value) {
                        value = temp;
                        index = i;
                    }
                }
                a[index]++;
            }
            return compute(a, b);
        }

    };

    TEST_FIXTURE(Solution, Normal1)
    {
        double result = DefendValue_force("input_hihocoder0814-DefendValue.txt");
        LOG(INFO) << "Force:" << result;
        return;
    }

    TEST_FIXTURE(Solution, Normal2)
    {
        double result = DefendValue_greedy("input_hihocoder0814-DefendValue.txt");
        LOG(INFO) << "greedy:" << result;
        return;
    }

    TEST_FIXTURE(Solution, Normal3)
    {
        return;
    }
}
