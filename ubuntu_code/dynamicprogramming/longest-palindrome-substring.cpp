/*======================================================
#
# Filename:		longest-palindrome-substring.cpp
#
# Version: 
#
# Last modified:	2016-03-04 09:38
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

/*使用普通的遍历中心轴方法*/
void longestPalindromeSubString1(const char* x, int n, int& max, int& begin, int& end);

/*使用Manacher方法*/
void longestPalindromeSubString2(const char* x, int n, int& max, int& begin, int& end);

void printLPS(const char* x, int n, int begin, int end);

int main() {
	string xs;
	int max1, begin1, end1;
	int max2, begin2, end2;
	while (1) {
		cout << "Please input string:";
		cin >> xs;
		int n = xs.length();
		const char* x = xs.c_str();
		longestPalindromeSubString1(x, n, max1, begin1, end1);
		cout << "1:" << "max=" << max1 << " begin= " 
			   << begin1 << " end=" << end1 << endl << "LCS1:";
		printLPS(x, n, begin1, end1);
		longestPalindromeSubString2(x, n, max2, begin2, end2);
		cout << "2:" << "max=" << max2 << " begin= " 
			   << begin2 << " end=" << end2 << endl << "LCS2:";
		printLPS(x, n, begin2, end2);
	}
}	

void longestPalindromeSubString1(const char* x, int n, 
		int& max, int& begin, int& end) {
	int i, j;
	int k = 0;
	int temp;
	max = 0;

	for (i = 0; i < n; ++i) {
		temp = 0;
		for (j = 0; (i-j) >= 0 && (i+j) < n; ++j) {
			if (x[i-j] != x[i+j]) {
				break;
			}
			temp = j * 2 + 1;
		}
		if (temp > max) {
			k = i;
			max = temp;
		}

		temp = 0;
		for (j = 0; (i-j) >= 0 && (i+j+1) < n; ++j) {
			if (x[i-j] != x[i+j+1]) {
				break;
			}	
			temp = j * 2 + 2;
		}
		if (temp > max) {
			k = i;
			max = temp;
		}
	}

	begin = k - max/2 + (max%2 == 0 ? 1 : 0);
	end = k + max/2;
} 

void longestPalindromeSubString2(const char* x, int n, 
		int& max, int& begin, int& end) {
	int i, j;
	//format x
	char a[2*n+2];
	a[0] = '$';
	a[1] = '#';
	for (i = 0; i < n; ++i) {
		a[2*i+2] = x[i];
	  a[2*i+3] = '#';	
	}
	string str = a;

	int n2 = str.length();
	int p[n2+1];
	memset(p, 0, sizeof(p));
	int mx = 0;
	int id = 0;

	for (i = 1; i <= n2; ++i) {
		if (mx > i) {
			p[i] = (p[2*id-i] < (mx-i) ? p[2*id-i] : (mx-i));
		} else {
			p[i] = 1;
		}

		while (str[i-p[i]] == str[i+p[i]]) {
			p[i]++;
		}
		
		if (mx - i < p[i]) {
			mx = i+p[i];
			id = i;
		}
	}	

	int z;
	max = 0;
	for (i = 1; i < n2; ++i) {
		if (p[i] > max) {
			z = i;
			max = p[i];
		}
	}

	max--;

	int a_max;
	if (z % 2 == 0) {
		z = (z-2)/2;
		a_max = (max+1)/2 - 1;
		begin = z - a_max;
		end = z + a_max;
	} else {
		z = (z-1-2)/2;
		a_max = max/2;
		begin = z - a_max + 1;
	  end = z + a_max;	
	}
} 

void printLPS(const char* x, int n, int begin, int end) {
	if (begin < 0 || end >= n || end < begin) {
		cout << "Wrong range! Please check!" << endl;
		return;
	}
	for (int i = begin; i <= end; ++i) {
		cout << x[i];
	}
	cout << endl;
}

