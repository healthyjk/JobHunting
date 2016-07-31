/*======================================================
#
# Filename: matrix-chain-order2.cpp
#
# Version: 
#
# Last modified: 2016-03-02 11:10
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
#define MAX 1000000

void matrixChainOrder(int* p, int len, int** m, int** s) {
	int n = len - 1;
	int i, j, l, k, q;
	for (i = 1; i <= n; ++i) {
		m[i][i] = 0;
	}
	for (l = 2; l <= n; ++l) {
		for (i = 1; i <= (n-l+1); ++i) {
			j = i+l-1;
			m[i][j] = MAX;		
			for (k = i; k <= j-1; ++k) {
				q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
}

void printOptimalParens(int** s, int i, int j) {
	if (i == j) {
		cout << 'A' << i;
	} else {
		cout << '(';
		printOptimalParens(s, i, s[i][j]);
		printOptimalParens(s, s[i][j]+1, j);
		cout << ')';
	}
}	

int main() {
	int p[] = {30,35,15,5,10,20,25};		
	int** m = new int*[6+1];
	int** s = new int*[6+1];
	int i;
	for (i = 0; i < 7; ++i) {
		m[i] = new int[6+1];
	}
	for (i = 0; i < 7; ++i) {
		s[i] = new int[6+1];
	}
	matrixChainOrder(p, 7, m ,s);
	printOptimalParens(s, 1, 6);
	cout << endl;

	for (int i = 0; i < 7; ++i) {
		delete[] m[i];
	}
	for (int i = 0; i < 7; ++i) {
		delete[] s[i];
	}
}


