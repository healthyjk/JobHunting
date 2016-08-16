// Work3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <fstream>
#include <queue>

#define INF 0x3f3f3f3f   

using namespace std;

struct Node {
  int x; 
  int y;
  Node() {}
  Node(int X, int Y) : x(X), y(Y) {}
};

/*SPFA搜索算法*/
int bfs(int n, int m, vector<int>& a, vector<int>& b, int x, int y, int p, int q, vector<vector<int> >& dp) {
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


int main()
{
  ifstream cin("input.txt");
  int n, m;
  while (cin >> n >> m) {
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

      cout << minPath << endl;
    }


  }

  return 0;
}
