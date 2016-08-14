// Work1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#define INT_MIN     (-2147483647 - 1) /* minimum (signed) int value */
#define INT_MAX       2147483647      /* maximum (signed) int value */

using namespace std;


int main()
{
	ifstream cin("input.txt");

	int n, m, k;
	cin >> n >> m >> k;
	vector<int> hurt(n);

	int dead = 0;

	for (int i = 0; i < n; ++i) {
		cin >> hurt[i];
		if (hurt[i] >= m) {
			dead++;
		}
	}

	if (k <= 0 || dead >= k) {
		cout << "-1" << endl;
		return 0;
	}

	int t = 0;
	int remainK, remainM;
	while (true) {
		remainK = k;
		remainM = m;
		for (int i = 0; i < n; ++i) {
			if (hurt[i] >= remainM) {
				remainK--;
				remainM = m;
			} else {
				remainM -= hurt[i];
				remainM = (remainM + t > m) ? m : (remainM + t);
			}
			if (remainK <= 0) break;
		}

		if (remainK <= 0) {
			t++;
		} else {
			break;
		}
	}

	if (t == 0) {
		cout << "1" << endl;
	} else {
		cout << t << endl;
	}

	return 0;
}

