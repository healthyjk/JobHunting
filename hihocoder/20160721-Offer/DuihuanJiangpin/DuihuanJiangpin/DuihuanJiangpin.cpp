// DuihuanJiangpin.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


//最简单的0-1背包问题解法，不包括任何优化部分，直接使用动态规划
//此处的dp[i][j]代表前i件物品恰放入体积为j的背包里产生的最大价值；
long long dynamicProgrammingBag_normal(vector<int>& W, vector<int>& C, int V) {
	int n = W.size();
	vector<vector<long long> > dp(n+1);
	for (int i = 0; i <= n; ++i) {
		dp[i].resize(V+1, 0);
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = C[i-1]; j <= V; ++j) {
			dp[i][j] = max(dp[i-1][j], dp[i-1][j-C[i-1]] + (long long)W[i-1]);
		}
	}

	return dp[n][V];
}

long long dynamicProgrammingBag_improve(vector<int>& W, vector<int>& C, int V) {
	int n = W.size();
	vector<long long> dp(V+1, 0);
	for (int i = 1; i <= n; ++i) {
		for (int j = V; j >= C[i-1]; --j) {
			dp[j] = max(dp[j], dp[j-C[i-1]] + (long long)W[i-1]);
		}
	}
	return dp[V];
}

int main()
{
	ifstream cin("input.txt");
	int n, m;
	while (cin >> n >> m) {
		vector<int> w(n, 0);
		vector<int> p(n, 0);
		for (int i = 0; i < n; ++i) {
			cin >> w[i] >> p[i];
		}
		long long result = dynamicProgrammingBag_improve(p, w, m);
		cout << result << endl;
	}
	return 0;
}

