// Work1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

bool isReverseWord(const string& str1, const string& str2) {
	if (str1.size() != str2.size() || str1.size() <= 0) {
		return false;
	}
	int n = str1.size();
	for (int i = 0; i < n; ++i) {
		if (str1[i] != str2[n-1-i]) {
			return false;
		}
	}

	return true;
}

void getReverse(const string& str, string& r_str) {
	int n = str.size();
	if (n <= 0) return;

	for (int i = n-1; i >= 0; --i) {
		r_str.push_back(str[i]);
	}
}



int main()
{
	ifstream cin("input.txt");
	int n;
	while (cin >> n) {
		vector<string> words(n);
		for (int i = 0; i < n; ++i) {
			cin >> words[i];
		}

		map<string, bool> str_flag;
		int result = 0;
		for (int i = 0; i < n; ++i) {
			
			if (str_flag.find(words[i]) != str_flag.end()) {
				result++;
			} else {
				string r_str;
				getReverse(words[i], r_str);
				str_flag[r_str] = true;
			}
		}

		cout << result << endl;
	}
	
	return 0;
}

