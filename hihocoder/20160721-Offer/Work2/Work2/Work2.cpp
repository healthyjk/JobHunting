// Work2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>

#define INT_MIN     (-2147483647 - 1) /* minimum (signed) int value */
#define INT_MAX     2147483647

using namespace std;

bool Compare(const pair<int,int>& a, const pair<int,int>& b)  {
	return (a.first < b.first) || ((a.first == b.first) && (a.second < b.second));
}

vector<int> findNeedRepair_bak(vector<int> heights, int l) {
	int n = heights.size();
	vector<int> result;

	if (n <= 0) return result;

	int start = 0;
	long long min_weight;
	
	for (int i = 0; i < n; ++i) {
		long long weight = 0;
		for (int j = 0; j < l; ++j) {
			int index = (j+i) % n;
			weight += heights[index];
		}

		if (i == 0) {
			min_weight = weight;
		}

		if (weight < min_weight) {
			min_weight = weight;
			start = i;
		}
	}

	for (int i = start; i < start+l; ++i) {
		result.push_back((i%n));
	}
	
	return result;
}

vector<int> findNeedRepair(vector<int> heights, int l) {
	int n = heights.size();
	vector<int> result;
	if (n <= 0) return result;
	
	vector<pair<int, int> > height_index;
	for (int i = 0; i < n; ++i) {
		height_index.push_back(make_pair(heights[i], i));
	}
	sort(height_index.begin(), height_index.end(), Compare);

	map<int, int> weight;

	for (int i = 0; i < n; ++i) {
		weight[height_index[i].first] = n - i;
	}


	int index = height_index[0].second;

	int left_w = 0;
	for (int j = 0; j < l; ++j) {
		int k = (index+j) % n;
		left_w += weight[heights[k]];
	}

	int right_w = 0;
	for (int j = 0; j < l; ++j) {
		int k = (index-j) % n;
		right_w += weight[heights[k]];
	}

	if (left_w < right_w) {
		for (int i = index; i < index+l; ++i) {
			result.push_back((i%n));
		}
	} else {
		for (int i = index; i > index-l; --i) {
			result.push_back((i%n));
		}
	}
	
	return result;
}

int main()
{
	ifstream cin("input.txt");

	int n, m, l;

	while (cin >> n >> m >> l) {
		vector<int> heights(n);
		int max = INT_MIN;
		for (int i = 0; i < n; ++i) {
			cin >> heights[i];
			if (heights[i] > max) {
				max = heights[i];
			}
		}

		for (int i = 0; i < m; ++i) {
			vector<int> need_repair = findNeedRepair(heights, l);
			for (int j = 0; j < l; ++j) {
				heights[need_repair[j]] = max;
			}
		}

		int min_board = INT_MAX;
		for (int i = 0; i < n; ++i) {
			if (heights[i] < min_board) {
				min_board = heights[i];
			}
		}

		cout << min_board << endl;
	}

	return 0;
}



