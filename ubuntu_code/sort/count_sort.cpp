/*======================================================
#
# Filename:		count_sort.cpp
#
# Version: 
#
# Last modified:	2016-02-26 08:48
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

void printArray(int* array, int len);

void count_sort(int* array, int len, int range);

int main() {
	/*
	int len;
	cout << "Please input the length:" << endl;
	cin >> len;
	int array[len];
	cout << "Please input the numbers:" << endl;
	for (int i = 0; i < len; ++i) {
		cin >> array[i];
	} */

	int array[] = {4,1,3,2,16,9,10,14,8,7};
	int len = 10;

	count_sort(array, len, 17);
	cout << "countSort:";
	printArray(array, len);

	return 0;
}

void printArray(int* array, int len) {
	for (int i = 0; i < len; ++i) {
		cout << array[i] << "\t";
	}
	cout << endl;
}


void count_sort(int* array, int len, int range) {
	int* temp_array = new int[len];
	int* counts = new int[range];
	for (int i = 0; i < range; ++i) {
		counts[i] = 0;
	}
	for (int i = 0; i < len; ++i) {
		counts[array[i]]++;
	}
	for (int i = 1; i < range; ++i) {
		counts[i] = counts[i] + counts[i-1];
	}
	for (int i = len - 1; i >=0 ; --i) {
		temp_array[counts[array[i]] - 1] = array[i];
		counts[array[i]]--;
	}
	for (int i = 0; i < len; ++i) {
		array[i] = temp_array[i];
	}
	if (temp_array) delete temp_array;
	if (counts) delete counts;
}
