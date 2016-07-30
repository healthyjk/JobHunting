// PopularProducts.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"

#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>

using namespace std;

#define ERROR 0.0000001

/**
本题的解题难点主要在于id可以重复，如果用multi-map比较复杂；
因此我使用了id-price作为键值，id作为value，set存储id-price；
**/

string makeIdPrice(const string& id, double price) {
	ostringstream os;
	char a[20];
	sprintf_s(a, "%.2lf", price);
	os << id << '-' << a;
	return os.str();
}

int main()
{
	ifstream cin("input.txt");
	int N;
	while (cin >> N) {
		unordered_set<string> ids;
		vector<unordered_map<string, string>> productMap(N);
		for (int i = 0; i < N; ++i) {
			int m;
			cin >> m;
			for (int j = 0; j < m; ++j) {
				string id, data;
				double price;
				cin  >> id >> data >> price;
				string id_price = makeIdPrice(id, price);
				productMap[i][id_price] = id;
				ids.insert(id_price);
			}
		}

		vector<string> result;
		for (auto iter = ids.begin(); iter != ids.end(); ++iter) {
			int flag = true;
			for (int i = 0; i < N; ++i) {
				if (productMap[i].find((*iter)) == productMap[i].end()) {
					flag = false;
					break;
				}
			}
			if (flag) {
				result.push_back(productMap[0][*iter]);
			}
		}

		sort(result.begin(), result.end());

		for (int i = 0; i < result.size(); ++i) {
			cout << result[i] << endl;
		}
	}
	
	return 0;
}



