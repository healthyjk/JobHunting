// Work3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>

#define INT_MIN     (-2147483647 - 1) /* minimum (signed) int value */
#define INT_MAX       2147483647      /* maximum (signed) int value */

using namespace std;

struct Node {
	int x; 
	int y;
	Node() {}
	Node(int X, int Y) : x(X), y(Y) {}
};

int bfs(int n, int m, vector<int>& a, vector<int>& b, int x, int y, int p, int q, vector<vector<int> >& dp) {
	queue<Node> queue;
	queue.push(Node(x,y));

	dp[x][y] = 0;

	while (!queue.empty()) {
		Node cur = queue.front();
		queue.pop();

		if (cur.x - 1 >= 1 && cur.x - 1 <= n && cur.y >= 1 && cur.y <= m && dp[cur.x - 1][cur.y] == INT_MAX) {
			queue.push(Node(cur.x - 1, cur.y));
			dp[cur.x - 1][cur.y] = dp[cur.x][cur.y] + b[cur.x - 1];
			if (cur.x - 1 == p && cur.y == q) {
				return dp[cur.x - 1][cur.y];
			}
		}

		if (cur.x >= 1 && cur.x <= n && cur.y - 1 >= 1 && cur.y - 1 <= m && dp[cur.x][cur.y - 1] == INT_MAX) {
			queue.push(Node(cur.x, cur.y - 1));
			dp[cur.x][cur.y - 1] = dp[cur.x][cur.y] + a[cur.y - 1];
			if (cur.x == p && cur.y - 1 == q) {
				return dp[cur.x][cur.y - 1];
			}
		}

		if (cur.x + 1 >= 1 && cur.x + 1 <= n && cur.y >= 1 && cur.y <= m && dp[cur.x + 1][cur.y] == INT_MAX) {
			queue.push(Node(cur.x + 1, cur.y));
			dp[cur.x + 1][cur.y] = dp[cur.x][cur.y] + b[cur.x];
			if (cur.x + 1 == p && cur.y == q) {
				return dp[cur.x + 1][cur.y];
			}
		}

		if (cur.x >= 1 && cur.x <= n && cur.y + 1 >= 1 && cur.y + 1 <= m && dp[cur.x][cur.y + 1] == INT_MAX) {
			queue.push(Node(cur.x, cur.y + 1));
			dp[cur.x][cur.y + 1] = dp[cur.x][cur.y] + a[cur.y];
			if (cur.x == p && cur.y + 1 == q) {
				return dp[cur.x][cur.y + 1];
			}
		}
	}

	return -1;
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
					dp[i][j] = INT_MAX;
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
