/*======================================================
#
# Filename: longest-common-substring.cpp
#
# Version: 
#
# Last modified: 2016-03-02 22:45
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

void printLPS(int** c, const char* x, int i, int j);

void longestPalindrome(const char* x, int m);

void print2DArray(int** a, int x, int y);

int main() {
	string xs;
	while (1) {
		cout << "Please input string:";
		cin >> xs;
		const char* x = xs.c_str();
		longestPalindrome(x, xs.length());
	}
}	

void longestPalindrome(const char* x, int m) {
	int i, j;
	int** c = new int*[m];
	for (i = 0; i < m; ++i) {
		c[i] = new int[m];
	}
	//初始化c
	for (i = 0; i < m; ++i) {
		for (j = 0; j < m; ++j) {
			c[i][j] = (i==j? 1 : 0);
		}
	}
	for (i = 1;i < m; ++i) {
		for (j = 0; j+i < m; ++j) {
			if (x[j] == x[j+i]) {
				c[j][j+i] = c[j+1][j+i-1]+2;
			} else if (c[j+1][j+i] > c[j][j+i-1]) {
				c[j][j+i] = c[j+1][j+i];
			} else {
				c[j][j+i] = c[j][j+i-1];
			}
		}
	}
	cout << "Longest palindrome length:" << c[0][m-1] << endl;
	cout << "Array C:" << endl;
	print2DArray(c, m, m);
	cout << "Longest palindrome strings:";
	printLPS(c, x, 0, m-1);
	cout << endl;
} 

void printLPS(int** c, const char* x, int i, int j) {
	if (j < i || j < 0) {  //因为等于情况划到j-1中,因此不需考虑i<=m
		return;
	}
	if (j == i) {
		cout << x[i];
		return;
	}
	if (x[i] == x[j]) {
		cout << x[i];
		printLPS(c, x, i+1, j-1);
		cout << x[j];
	} else if (c[i+1][j] > c[i][j-1]) {
		printLPS(c, x, i+1 ,j);
	} else if (c[i+1][j] < c[i][j-1]){
		printLPS(c, x, i, j-1);
	} else {
		cout << "(";
		printLPS(c, x, i, j-1);
		cout << "||";
		printLPS(c, x, i+1 ,j);
		cout << ")";
	}
}

void print2DArray(int** a, int x, int y) {
	for (int i = 0; i < x; ++i) {
		for (int j = 0; j < y; ++j) {
			cout << a[i][j] << "\t";
		}
		cout << endl;
	}
}
