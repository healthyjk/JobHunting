/*======================================================
#
# Filename: insertion_sort_2.cpp
#
# Version: 
#
# Last modified: 2016-02-18 13:24
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
#include <malloc.h>
#define INT_MAX 2147483647
using namespace std;

void merge_sort(int* array, int begin, int end);
void merge(int* array, int begin, int middle, int end);
void merge_no_guard(int* array, int begin, int middle, int end);
void printArray(int* array, int len);

int main() {
	int len;
	cout << "Please input the length:" << endl;
	cin >> len;
	int array[len];
	cout << "Please input the numbers:" << endl;
	for (int i = 0; i < len; ++i) {
		cin >> array[i];
	}

	merge_sort(array, 0, len-1);

	for (int i = 0; i < len; ++i) {
		cout << array[i] << "\t";
	}
	cout << endl;
	return 0;
}

void merge_sort(int* array, int begin, int end) {
	if (begin >= end) return;
	int middle = (int)((end+begin)/2.0);
	merge_sort(array, begin, middle);
	merge_sort(array, middle+1, end);
	merge_no_guard(array, begin, middle, end);
}

/*有哨兵时,当排序数中出现INT_MAX时会出现错误*/
void merge(int* array, int begin, int middle, int end) {
	if (begin >= end) return;
	int left_len = middle - begin + 1;
	int right_len = end - middle;
	int* left = new int[left_len+1];
	int* right = new int[right_len+1];
	int i = 0;
	for (i = 0; i < left_len; ++i) {
		left[i] = array[begin+i];
	}		
	left[i] = INT_MAX;
	for (i = 0; i < right_len; ++i) {
		right[i] = array[middle+1+i];
	}
	right[i] = INT_MAX;
	int k = 0;
	int l = 0;
	for (i = 0; i < (right_len+left_len); ++i) {
		if (left[k]<right[l]) {
			array[begin+i] = left[k];
			k++;
		} else {
			array[begin+i] = right[l];
			l++;
		}
	}
	delete left;
	delete right;
}

void merge_no_guard(int* array, int begin, int middle, int end) {
	if (begin >= end) return;
	int left_len = middle - begin + 1;
	int right_len = end - middle;
	int* left = new int[left_len];
	int* right = new int[right_len];
	int i = 0;
	for (i = 0; i < left_len; ++i) {
		left[i] = array[begin+i];
	}		
	for (i = 0; i < right_len; ++i) {
		right[i] = array[middle+1+i];
	}
	int k = 0;
	int l = 0;
	i = begin;
	while (k < left_len && l < right_len) {
		if (left[k]<right[l]) {
			array[i] = left[k];
			k++;
		} else {
			array[i] = right[l];
			l++;
		}
		i++;
	}
	if (k != left_len) {
		for (l = k; l < left_len; ++l) {
			array[begin+i] = left[l];
			i++;
		}
	}
	if (l != right_len) {
		for (k = l; k < right_len; ++k) {
			array[begin+i] = right[k];
			i++;
		}
	}
	delete left;
	delete right;
}

void printArray(int* array, int len) {
	for (int i = 0; i < len; ++i) {
		printf("%d\t", array[i]);
	}
	printf("\n");
}
