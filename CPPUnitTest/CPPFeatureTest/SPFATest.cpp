#include "UnitTest++/UnitTest++.h"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <fstream>
#include <queue>

#define INF       0x3f3f3f3f      /* maximum (signed) int value */

using namespace std;

/**
  * 测试用例：积水的城市
  * 如下图所示，某市市区由M条南北向的大街和N条东西向的道路组成。
  * 其中由北向南第i条路和第i+1条路之间的距离是Bi (1 <= i < N)，
  * 由西向东第i条街和第i+1条街之间的距离是Ai (1 <= i < M)。
  * 小Ho现在位于第x条路和第y条街的交叉口，他的目的地是第p条路和第q条街的交叉口。
  * 由于连日降雨，城市中有K个交叉口积水太深不能通行。小Ho想知道到达目的地的最短路径的长度是多少。
  * 作者：yanjiankang
  * 时间：2016年8月18日
  **/

SUITE(SPFATestCase1)
{
    struct Node {
      int x;
      int y;
      Node() {}
      Node(int X, int Y) : x(X), y(Y) {}
    };

    class Solution {
    public:
        int bfs(int n, int m, vector<int>& a, vector<int>& b,
                int x, int y, int p, int q, vector<vector<int> >& dp) {
          queue<Node> queue;
          queue.push(Node(x,y));

          dp[x][y] = 0;

          int dx[] = {-1, 0, 1, 0};
          int dy[] = {0, -1, 0, 1};


          while (!queue.empty()) {
            Node cur = queue.front();
            queue.pop();

            for (int i = 0; i < 4; ++i) {
              int nx = cur.x + dx[i];
              int ny = cur.y + dy[i];

              if (nx <= 0 || nx > n || ny <= 0 || ny > m || dp[cur.x][cur.y] == -1) {
                continue;
              }

              int temp = dp[cur.x][cur.y] + (dx[i] == 0 ? a[min(cur.y, ny)] : b[min(cur.x, nx)]);
              if (temp >= dp[nx][ny]) {
                continue;
              }

              dp[nx][ny] = temp;
              if (nx != p || ny != q) {
                queue.push(Node(nx, ny));  //此处包括没有访问的结点和访问过后更新最短长度的
              }
            }
          }

          return dp[p][q] == INF ? -1 : dp[p][q];
        }

        int ShortestPath(string input_file) {
            ifstream cin(input_file);
            int n, m;
            cout << " test " << endl;
            while (cin >> n >> m) {
              cout << n << "," << m << endl;
              vector<int> b(n+1);
              for (int i = 1; i < n; ++i) {
                cin >> b[i];
              }

              vector<int> a(m+1);
              for (int i = 1; i < m; ++i) {
                cin >> a[i];
              }

              vector<vector<int> > dp(n+1);
              for (int i = 1; i <= n; ++i) {
                dp[i].resize(m+1);
              }

              int k;
              cin >> k;
              vector<Node> track(k);
              for (int i = 0; i < k; ++i) {
                cin >> track[i].x >> track[i].y;
              }

              int Q;
              cin >> Q;
              while (Q--) {
                int x, y, p, q;
                cin >> x >> y >> p >> q;

                for (int i = 1; i <= n; ++i) {
                  for (int j = 1; j <= m; ++j) {
                    dp[i][j] = INF;
                  }
                }

                for (int i = 0; i < k; ++i) {
                  dp[track[i].x][track[i].y] = -1;
                }

                int minPath = bfs(n, m, a, b, x, y, p, q, dp);

                return minPath;
              }
            }
        }
    };

    TEST_FIXTURE(Solution, Normal1)
    {
        string file = "input_spfatest.txt";
        cout << "test" << endl;

        int result = 0;
        result = ShortestPath(file);

        cout << result << endl;
        //CHECK_EQUAL(24,result);
        return;
    }
}
