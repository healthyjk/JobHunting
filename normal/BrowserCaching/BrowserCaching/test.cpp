
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>

using namespace std;

map<string, int> lastVisited;

vector<bool> BrowserCache(const vector<string>& pages, int n, int m) {
	vector<bool> result;
	int start = 1;
	int cache_cnt = 0;

	for (int i = 1; i <= n; ++i) {
		if (lastVisited[pages[i]] >= start && lastVisited[pages[i]] <= i) {
			result.push_back(true);
		} else {
			result.push_back(false);
			
			cache_cnt++;
			if (cache_cnt > m) {
				start = start + 1;
			}
		}
		lastVisited[pages[i]] = i;
		while (lastVisited[pages[start]] != start) {
			start = start + 1;
		}
	}

	return result;
}


int main()
{
	ifstream cin("input.txt");

	int n, m;
	while (cin >> n >> m) {
		vector<string> inputs(n+1);
		for (int i = 1; i <= n; ++i) {
			cin >> inputs[i];
		}

		vector<bool> result = BrowserCache(inputs, n, m);
		for (int i = 0; i < n; ++i) {
			if (result[i]) {
				cout << "Cache" << endl;
			} else {
				cout << "Internet" << endl;
			}
		}

		
	}

	return 0;
}
