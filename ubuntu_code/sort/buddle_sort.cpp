/*======================================================
#
# Filename:		buddle_sort.cpp
#
# Version: 
#
# Last modified:	2016-02-23 21:41
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
using namespace std;

void buddle_sort(int* array, int len);
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

	buddle_sort(array, len);

	printArray(array, len);

	return 0;
}

void buddle_sort(int* array, int len) {
	int temp, max_index, j;
	int flag = len;
	while (flag > 0) {
			max_index = flag;
			flag = 0;
			for (j = 1; j < max_index; ++j) {
				if (array[j-1] > array[j]) {
					temp = array[j-1];
					array[j-1] = array[j];
					array[j] = temp;
					flag = j;
				}
			}
	}
}

void printArray(int* array, int len) {
	for (int i = 0; i < len; ++i) {
		printf("%d\t", array[i]);
	}
	printf("\n");
}
