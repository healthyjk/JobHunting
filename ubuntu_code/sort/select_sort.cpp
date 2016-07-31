/*======================================================
#
# Filename: select_sort.cpp
#
# Version: 
#
# Last modified: 2016-02-24 09:20
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

void select_sort(int* array, int len);

int main() {
	int len;
	cout << "Please input the length:" << endl;
	cin >> len;
	int array[len];
	cout << "Please input the numbers:" << endl;
	for (int i = 0; i < len; ++i) {
		cin >> array[i];
	}

	select_sort(array, len);

	for (int i = 0; i < len; ++i) {
		cout << array[i] << "\t";
	}
	cout << endl;
	return 0;
}

void select_sort(int* array, int len) {
	int index, i, j;
	for (i = 0; i < len - 1; ++i) {
		index = i;
		for (j=i+1;j < len; ++j) {
			if (array[j] < array[index]) {
				index = j;
			}
		}
		if (index != i) {
			int temp = array[index];
			array[index] = array[i];
			array[i] = temp;
		}
	}
}
