// DynamicProgrammingBag.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Solution {
public:
	//最简单的0-1背包问题解法，不包括任何优化部分，直接使用动态规划
	//此处的dp[i][j]代表前i件物品恰放入体积为j的背包里产生的最大价值；
	int dynamicProgrammingBag_normal(vector<int>& W, vector<int>& C, int V) {
		int n = W.size();
		vector<vector<int> > dp(n+1);
		for (int i = 0; i <= n; ++i) {
			dp[i].resize(V+1, 0);
		}

		for (int i = 1; i <= n; ++i) {
			for (int j = C[i-1]; j <= V; ++j) {
				dp[i][j] = max(dp[i-1][j], dp[i-1][j-C[i-1]] + W[i-1]);
			}
		}

		return dp[n][V];
	}

	//优化后的0-1背包问题解法：优化空间复杂度
	int dynamicProgrammingBag_improve(vector<int>& W, vector<int>& C, int V) {
		int n = W.size();
		vector<int> dp(V+1, 0);

		for (int i = 1; i <= n; ++i) {
			for (int j = V; j >= C[i-1]; --j) {
				dp[j] = max(dp[j], dp[j-C[i-1]] + W[i-1]);
			}
		}

		return dp[V];
	}

	//变种的的0-1背包问题解法：这种题目中没有容积上限，每种物品也没有数量上限，而是要求满足不低于给定的价值上容积最小
	//比如建造基地题目中给定每种材料的成本和建设值，要求一定的建设值之下成本最低
	//参数啊前两项同上，K代表要求的必须满足的价值，如果全部物品加起来都不能满足价值，那么返回-1；
	//此处的dp[i][value]代表在前i个物品在满足价值大于等于value需要的体积值；（此处不一定达到价值value，达不到的时候为INT_MAX）
	int dynamicProgrammingBag_special(vector<int>& W, vector<int>& C, int K) {
		int n = W.size();
		vector<vector<long long> > dp(n+1);
		for (int i = 0; i <= n; ++i) {
			dp[i].resize(K+1, INT_MAX);
		}

		long long current = INT_MAX;

		dp[0][0] = 0;
		for (int i = 1; i <= n; ++i) {
			dp[i][0] = 0;  //达到满足价值为0需要的体积为0
			for (int j = 0; j <= K; ++j) {
				//cout << "i=" << i << ",j=" << j << ",j+w[i-1]=" << (j+W[i-1]) << ",dp[i-1][j]=" << dp[i-1][j] << ",dp[i][j]=" << dp[i][j] << endl;
				if (j+W[i-1] > K) {
					current = min(current, dp[i][j] + C[i-1]);
					//cout << "current=" << current << endl;
				} else {
					dp[i][j+W[i-1]] = min(dp[i-1][j+W[i-1]], dp[i][j] + C[i-1]);
					//cout << "dp[" << i << "][" << (j+W[i-1]) << "]=" << dp[i][j+W[i-1]] << endl;
				}
			}
		}

		current = min(current, dp[n][K]);

		//前n个物品均无法满足价值达到K，返回-1；
		if (current == INT_MAX) {
			return -1;
		}

		return current;
	}
};


int main()
{
	int w[] = {3, 4, 5, 6, 7, 9, 1};
	vector<int> vw(w, w + sizeof(w)/sizeof(int));

	int c[] = {5, 6, 9, 2, 1, 3, 6};
	vector<int> vc(c, c + sizeof(c)/sizeof(int));

	int V = 15;

	Solution solution;

	int result = solution.dynamicProgrammingBag_normal(vw, vc, V);
	cout << "result:" << result << endl;

	result = solution.dynamicProgrammingBag_improve(vw, vc, V);
	cout << "result:" << result << endl;

	result = solution.dynamicProgrammingBag_special(vw, vc, V);
	cout << "result:" << result << endl;

	return 0;
}

