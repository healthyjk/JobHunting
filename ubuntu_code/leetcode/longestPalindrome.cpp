/*======================================================
#
# Filename: longestPalindrome.cpp
#
# Version: 
#
# Last modified: 2016-03-12 22:21
#
# Description: 
#
# Author: jkyan - jkyan@fudan.edu.cn
#
# Copyright (c) 2014, All Right Reserved, MicroSystems, Fudan University
#
# Mode: C++; tab-width: 2;
# vim: set tabstop=2 softtabstop=2 shiftwidth=2 expandtab: 
#
=====================================================*/
          
#include <iostream> 
#include <string.h>

using namespace std;

string longestPalindrome(string s) {
	int n = s.length();
	if (n == 0) return "";
	if (n == 1) return s;

	int i, j = 0;
	//preprocess the string
	string s1 = "$#";
	for (int i = 0; i < n; ++i) {
		s1 += s.substr(i,1) + "#";
	}

	int nf = 2*n+2;
	int id = 0;
	int mx = 0;
	int p[nf];

	for (i = 0; i < nf; ++i) {
		j = 2*id - i;
		if (i >= mx) {
			p[i] = 1;
		}	else {
			if (mx - i < p[j]) {
				p[i] = mx -i;
			} else {
				p[i] = p[j];
			}
		}

		while((i-p[i]) >=0 && (i+p[i] < nf) && s1[i-p[i]] == s1[i+p[i]]) {
			p[i]++;
		}

		if (i+p[i] > mx) {
			mx = i + p[i];
			id = i;
		}

	}
	int max = 0, ii;
	for (i = 0; i < nf; ++i) {
		if (p[i] > max) {
			max = p[i];
			ii = i;
		}
	}
	int start = (ii - max) / 2;
	max--;
	cout << "start:" << start << "  max:" << max << endl;
	cout << s.substr(start, max) << endl;
	return s.substr(start, max);
}

int main() {

	string s,sub;

	while(true) {
		cout << "Please input string:";
		cin >> s;
		sub = longestPalindrome(s);
		cout << "substring:" << sub << endl;
	}
	return 0;
}
