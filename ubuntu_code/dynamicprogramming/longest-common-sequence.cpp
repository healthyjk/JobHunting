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

using namespace std;

enum {
	SLANT,
	BACK,
	UP
};

void lcsLength(char* x, int m, char* y, int n, int** c, int** b) {
	int i, j;
	for (i = 1; i <= m; ++i) {
		c[i][0] = 0;
	}
	for (i = 0; i <= n; ++i) {
		c[0][j] = 0;
	}
	for (i = 1;i <= m; ++i) {
		for (j = 1; j <= n; ++j) {
			if (x[i-1] == y[j-1]) {
				c[i][j] = c[i-1][j-1]+1;
				b[i][j] = SLANT;
			} else if (c[i-1][j] >= c[i][j-1]) {
				c[i][j] = c[i-1][j];
				b[i][j] = UP;
			} else {
				c[i][j] = c[i][j-1];
				b[i][j] = BACK;
			}
		}
	}
} 

void printLcs(int** b, char* x, int i, int j) {
	if (i == 0 || j == 0) {
		return;
	}
	if (b[i][j] == SLANT) {
		printLcs(b, x, i-1, j-1);
		cout << x[i-1];
	} else if (b[i][j] == UP) {
		printLcs(b, x, i-1, j);
	} else {
		printLcs(b, x, i, j-1);
	}
}

void print2DArray(int** a, int x, int y);

int main() {
	char x[] = {'A', 'B', 'C', 'B', 'D', 'A', 'B'};
	char y[] = {'B', 'D', 'C', 'A', 'B', 'A'};	
	int i;
	int** c = new int*[7+1];
	for (i = 0; i < 8; ++i) {
		c[i] = new int[6+1];
	}
	int** b = new int*[7+1];
	for (i = 0; i < 8; ++i) {
		b[i] = new int[6+1];
	}
	lcsLength(x, 7, y, 6, c, b);
	cout << "c array:" << endl; 
	print2DArray(c, 8, 7);
	cout << "LCS: ";
	printLcs(b, x, 7, 6);
	cout << endl;
	for (i = 0; i < 7; ++i) {
		delete[] c[i];
		delete[] b[i];
	}
	return 0;
}	

void print2DArray(int** a, int x, int y) {
	for (int i = 0; i < x; ++i) {
		for (int j = 0; j < y; ++j) {
			cout << a[i][j] << "\t";
		}
		cout << endl;
	}
}
