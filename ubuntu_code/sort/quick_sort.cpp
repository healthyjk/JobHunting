/*======================================================
#
# Filename:		quick_sort.cpp
#
# Version: 
#
# Last modified:	2016-02-24 09:30
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

void quick_sort(int* array, int begin, int end);
int quick_base(int* array, int begin, int end);
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

	quick_sort(array, 0, len-1);

	for (int i = 0; i < len; ++i) {
		cout << array[i] << "\t";
	}
	cout << endl;
	return 0;
}

void quick_sort(int* array, int begin, int end) {
	if (begin >= end) return;
	int i = quick_base(array, begin, end);
	quick_sort(array, begin, i-1);
	quick_sort(array, i+1, end);
}

int quick_base(int* array, int begin, int end) {
	int i = begin;
	int j = end;
	int base = array[i];
	while (i < j) {
		/*从右向左查找比基准小的数,并交换到i处*/
		while (i < j && array[j] >= base) j--;
		if (i < j) {
			array[i] = array[j];
			i++;
		}

		/*从左向右查找比基准大的数,并交换到j处*/
		while (i < j && array[i] < base) i++;
		if (i < j) {
			array[j] = array[i];
			j--;
		}
	}

	array[i] = base;

	return i;
}

void printArray(int* array, int len) {
	for (int i = 0; i < len; ++i) {
		printf("%d\t", array[i]);
	}
	printf("\n");
}
