/*======================================================
#
# Filename: activity-select.cpp
#
# Version: 
#
# Last modified: 2016-03-06 20:59
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
#include <vector>

#define MAX 10000000;

using namespace std;

/*使用贪心算法求解活动选择问题*/
void greedyActivitySelector(int* S, int n, int* start, int* end, vector<int>& A);

/*使用动态规划方法求解活动选择问题*/
void dynamicActivitySelector(int* S, int n, int* start, int* end, vector<int>& A);

void printActivity(int* S, int** b, int i, int j);

void print2DArray(int** a, int x, int y);

int main() {
	int S[] = {1,2,3,4,5,6,7,8,9,10,11};
	int start[] = {1,3,0,5,3,5,6,8,8,2,12};
	int end[] = {4,5,6,7,9,9,10,11,12,14,16};
	int start2[] = {0,1,3,0,5,3,5,6,8,8,2,12,100};
	int end2[] = {0,4,5,6,7,9,9,10,11,12,14,16,102};
	//int start2[] = {0,0,1,3,5,3,5,6,2,8,8,12,100};
	//int end2[] = {0,6,4,5,7,9,9,10,14,11,12,16,102};
	vector<int> A;
	greedyActivitySelector(S, 11, start, end, A);
	cout << "Select results:";
	for (int i = 0; i < A.size(); ++i) {
		cout << A[i] << "\t";
	}
	cout << endl;
	dynamicActivitySelector(S, 11, start2, end2, A);
	return 0;
}


void greedyActivitySelector(int* S, int n, int* start, int* end, vector<int>& A) {
	int k = 0;
	A.push_back(S[0]);
	for (int i = 1; i < n; ++i) {
		if (start[i] > end[k]) {
			A.push_back(S[i]);
			k = i;
		}
	}
}	


void dynamicActivitySelector(int* S, int n, int* start, int* end, vector<int>& A) {
	int** c = new int*[n+2];
	int** b = new int*[n+2];
	int i, j, k, l, q;

	for (i = 0; i < (n+2); ++i) {
		b[i] = new int[n+2];
		c[i] = new int[n+2];
	}

	for (j = 0; j < (n+2); ++j) {
		for (i = 0; i <= j; ++i) {
			c[i][j] = 0;
			b[i][j] = 0;
		}
	}

	for (j = 1; j < (n+2); ++j) {
		for (i = j-1; i >= 0; --i) {
			cout << "c[" << i << "," << j << "]:";
			for (k = i+1; k < j; ++k) {
				cout << k << "\t";
				if (start[k] >= end[i] && end[k] <= start[j]) {
					q = c[i][k] + c[k][j] + 1;
					if (c[i][j] < q) {
						c[i][j] = q;
						b[i][j] = k;
					}
				}
			}
			cout << endl;
		}
	}

	print2DArray(c, n+2, n+2);
	print2DArray(b, n+2, n+2);
	printActivity(S, b, 0, n+1);

	for (i = 0; i < (n+2); ++i) {
		delete[] b[i];
		delete[] c[i];
	}
}

void printActivity(int* S, int** b, int i, int j) {
	if (b[i][j] == 0) return;
	printActivity(S, b, i, b[i][j]);
	cout << S[b[i][j] - 1] << "\t";
	printActivity(S, b, b[i][j], j);
}

void print2DArray(int** a, int x, int y) {
	for (int i = 0; i < x; ++i) {
		for (int j = 0; j < y; ++j) {
			cout << a[i][j] << "\t";
		}
		cout << endl;
	}
}
