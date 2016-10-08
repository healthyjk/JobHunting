/*************************************************************************
* File Name: constraint_checker.cpp
* Author: yanjiankang
* Description: program function
* Mail: healthyjk@gmail.com 
* Created Time: 2016年10月08日 星期六 08时59分12秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>

using namespace std;

bool isUpperLetter(char c) {
	return (c >= 'A' && c <= 'Z');
}

bool isDigit(char c) {
	return (c >= '0' && c <= '9');
}

bool checkConstraint(string& str, map<char, int>& value_map) {
	int n = str.size();
	int last = -1;
	int cur = -1;
	bool isLess = true;

	for (int i = 0; i < n; ++i) {
		if (i == 0 || i == n-1) {
			if (!isDigit(str[i]) && !isUpperLetter(str[i])) {
				return false;
			}
		}
		if (i == 0) {
			if (isUpperLetter(str[i])) {
				last = value_map[str[i]];
			} else {
				int num = 0;
				while (isDigit(str[i])) {
					num = num*10 + str[i] - '0';
					i++;
				}
				last = num;
				i--;
			}
			continue;
		}

		if (str[i] == '<') {
			if (str[i+1] == '=') {
				isLess = false;
				i++;
			} else {
				isLess = true;
			}
			continue;
		}

		if (isUpperLetter(str[i])) {
			cur = value_map[str[i]];
		} else {
			int num = 0;
			while (isDigit(str[i])) {
				num = num*10 + str[i] - '0';
				i++;
			}
			cur = num;
			i--;
		}

		if (isLess) {
			if (last >= cur) {
				return false;
			}
		} else {
			if (last > cur) {
				return false;
			}
		}
		last = cur;
	}

	return true;
}

int main() {
	ifstream cin("input.txt");
	int n, m;
	while (cin >> n) {
		vector<string> input(n, "");
		for (int i = 0; i < n; ++i) {
			cin >> input[i];		
		}
		
		set<char> variable;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < input[i].size(); ++j) {
				if (input[i][j] >= 'A' && input[i][j] <= 'Z') {
					variable.insert(input[i][j]);
				}
			}

		}

		int k = variable.size();
		map<char, int> value_map;

		cin >> m;

		while (m--) {
			for (int i = 0; i < k; ++i) {
				char temp;
				int value;
				cin >> temp >> value;
				value_map[temp] = value;
			}

			bool flag = true;
			for (int i = 0; i < n; ++i) {
				if(!checkConstraint(input[i], value_map)) {
					flag = false;
					break;
				}
			}

			if (flag) {
				cout << "Yes" << endl;
			} else {
				cout << "No" << endl;
			}
		}
	}
	return 0;
}
