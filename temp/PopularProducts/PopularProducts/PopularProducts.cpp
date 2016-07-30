// PopularProducts.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

#define ERROR 0.0000001


int main()
{
	ifstream cin("input.txt");
	int N;
	while (cin >> N) {
		unordered_set<string> ids;
		vector<unordered_map<string, double>> productMap(N);
		for (int i = 0; i < N; ++i) {
			int m;
			cin >> m;
			for (int j = 0; j < m; ++j) {
				string id, data;
				double price;
				cin >> id >> data >> price;
				productMap[i][id] = price;
				ids.insert(id);
			}
		}

		vector<string> result;
		for (auto iter = ids.begin(); iter != ids.end(); ++iter) {
			int flag = true;
			double price = -1.0;
			for (int i = 0; i < N; ++i) {
				if (productMap[i].find((*iter)) == productMap[i].end()) {
					flag = false;
					break;
				} else {
					if (price < 0) {
						price = productMap[i][(*iter)];
					} else if (abs(price - productMap[i][(*iter)]) > ERROR){
						flag = false;
						break;
					}
				}
			}
			if (flag) {
				result.push_back((*iter));
			}
		}

		sort(result.begin(), result.end());

		for (int i = 0; i < result.size(); ++i) {
			cout << result[i] << endl;
		}
	}
	
	return 0;
}



