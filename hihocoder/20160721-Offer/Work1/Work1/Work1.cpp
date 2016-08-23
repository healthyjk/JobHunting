// Work1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>

#define INT_MIN     (-2147483647 - 1) /* minimum (signed) int value */
#define INT_MAX       2147483647      /* maximum (signed) int value */

using namespace std;


int main()
{
	ifstream cin("input.txt");

	string input;

	while (cin >> input) {
		int n = input.size();

		for (int i = 0; i < n; ++i) {
			if (input[i] == 'J') {
				input[i] = 'I';
			}
		}

		int index = 0;
		string result;
		map<char, int> str_index;
		for (int i = 0; i < n; ++i) {
			if (str_index.find(input[i]) == str_index.end()) {
				str_index[input[i]] = index;
				index++;
				result.push_back(input[i]);
			}
		}


		for (int j = 0; j < 26; ++j) {
			char c = 'A' + j;
			if (c == 'J') continue;
			if (str_index.find(c) == str_index.end()) {
				index++;
				result.push_back(c);
			}
		}

		for (int i = 0; i < 5; ++i) {
			cout << result.substr(i*5, 5) << endl;
		}
	}


	return 0;
}


