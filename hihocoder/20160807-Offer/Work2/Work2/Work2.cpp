// Work2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

double compute(vector<int>& a, vector<int>& b) {
	int n = a.size();
	double result = 1;
	for (int i = 0; i < n; ++i) {
		result *= pow((double)a[i], 1.0/(double)b[i]);
	}
	return result;
}


void dfs(vector<int>& a, vector<int>& b, int& n, double& max, int t) {
	int k = a.size();

	if (n <= 0) {
		double current = compute(a, b);
		if (current > max) {
			max = current;
		}
		return;
	}
	if (k-1 == t) {
		a[t] += n;
		double current = compute(a, b);
		if (current > max) {
			max = current;
		}
		a[t] -= n;
		return;
	}

	for (int i = n; i >= 0; --i) {
		a[t] += i;
		n = n - i;
		dfs(a, b, n, max, t+1);
		n += i;
		a[t] -= i;
	}
}


//int main()
//{
//	ifstream cin("input.txt");
//	int n, k;
//	while (cin >> n >> k) {
//		vector<int> a(k);
//		vector<int> b(k);
//		for (int i = 0; i < k; ++i) {
//			cin >> a[i];
//		}
//
//		for (int i = 0; i < k; ++i) {
//			cin >> b[i];
//		}
//
//		double result = 0.0;
//		dfs(a, b, n, result, 0);
//
//		printf("%.2lf\n", result);
//
//	}
//
//	return 0;
//}
