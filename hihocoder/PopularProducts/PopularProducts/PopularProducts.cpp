// PopularProducts.cpp : �������̨Ӧ�ó������ڵ㡣
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
����Ľ����ѵ���Ҫ����id�����ظ��������multi-map�Ƚϸ��ӣ�
�����ʹ����id-price��Ϊ��ֵ��id��Ϊvalue��set�洢id-price��
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



