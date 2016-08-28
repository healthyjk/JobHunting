
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>

using namespace std;

#define INT_MIN     (-2147483647 - 1) /* minimum (signed) int value */
#define INT_MAX       2147483647    /* maximum (signed) int value */

int getMinHeight(int n, const vector<int>& width, const vector<int>& height, int m, int delete_index) {
	
	int current_height = 0;
	int remain_width = n;
	int total_height = 0;
	
	for (int i = 0; i < m; ++i) {
		if (i == delete_index) {
			continue;
		}
		int temp_width = width[i];
		int temp_height = height[i];
		if (temp_width > remain_width) {
			temp_height = ceil(((double)remain_width / temp_width) * (double)temp_height);
			temp_width = remain_width;
		}
		if (temp_height > current_height) {
			current_height = temp_height;
		}
		remain_width -= temp_width;
		if (remain_width == 0) {
			remain_width = n;
			total_height += current_height;
			current_height = 0;
		}
	}

	if (current_height != 0) {
		total_height += current_height;
	}

	return total_height;
}

int main()
{
	ifstream cin("input.txt");

	int n, m;
	while (cin >> n >> m) {
		vector<int> height(m, 0);
		vector<int> width(m, 0);
		for (int i = 0; i < m; ++i) {
			cin >> width[i] >> height[i];
		}

		int min_height = INT_MAX;
		for (int i = 0; i < m; ++i) {
			int result = getMinHeight(n, width, height, m, i);
			if (result < min_height) {
				min_height = result;
			}
		}

		cout << min_height << endl;
	}

	return 0;
}
