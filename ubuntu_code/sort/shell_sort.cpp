/*======================================================
#
# Filename: shell_sort.cpp
#
# Version: 
#
# Last modified: 2016-02-23 22:14
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

void shell_sort(int* array, int len);

int main() {
	int len;
	cout << "Please input the length:" << endl;
	cin >> len;
	int array[len];
	cout << "Please input the numbers:" << endl;
	for (int i = 0; i < len; ++i) {
		cin >> array[i];
	}

  shell_sort(array, len);

	for (int i = 0; i < len; ++i) {
		cout << array[i] << "\t";
	}
	cout << endl;
	return 0;
}

void shell_sort(int* array, int len) {
	int gap;
	for (gap = len / 2; gap >0; gap /= 2) {
		for (int i = gap; i < len; ++i) {
			if (array[i] < array[i-gap]) {

				int temp = array[i];
				int j = i - gap;
				while ((j >= 0) && (array[j] > temp)) {
					array[j+gap] = array[j];
					j -= gap;
				}
				array[j+gap] = temp;
			}
		}
	}
}
