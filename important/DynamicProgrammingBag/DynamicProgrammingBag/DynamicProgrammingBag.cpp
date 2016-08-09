// DynamicProgrammingBag.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Solution {
public:
	//��򵥵�0-1��������ⷨ���������κ��Ż����֣�ֱ��ʹ�ö�̬�滮
	//�˴���dp[i][j]����ǰi����Ʒǡ�������Ϊj�ı��������������ֵ��
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

	//�Ż����0-1��������ⷨ���Ż��ռ临�Ӷ�
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

	//���ֵĵ�0-1��������ⷨ��������Ŀ��û���ݻ����ޣ�ÿ����ƷҲû���������ޣ�����Ҫ�����㲻���ڸ����ļ�ֵ���ݻ���С
	//���罨�������Ŀ�и���ÿ�ֲ��ϵĳɱ��ͽ���ֵ��Ҫ��һ���Ľ���ֵ֮�³ɱ����
	//������ǰ����ͬ�ϣ�K����Ҫ��ı�������ļ�ֵ�����ȫ����Ʒ�����������������ֵ����ô����-1��
	//�˴���dp[i][value]������ǰi����Ʒ�������ֵ���ڵ���value��Ҫ�����ֵ�����˴���һ���ﵽ��ֵvalue���ﲻ����ʱ��ΪINT_MAX��
	int dynamicProgrammingBag_special(vector<int>& W, vector<int>& C, int K) {
		int n = W.size();
		vector<vector<long long> > dp(n+1);
		for (int i = 0; i <= n; ++i) {
			dp[i].resize(K+1, INT_MAX);
		}

		long long current = INT_MAX;

		dp[0][0] = 0;
		for (int i = 1; i <= n; ++i) {
			dp[i][0] = 0;  //�ﵽ�����ֵΪ0��Ҫ�����Ϊ0
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

		//ǰn����Ʒ���޷������ֵ�ﵽK������-1��
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

