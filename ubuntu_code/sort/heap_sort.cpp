/*======================================================
#
# Filename:		heap_sort.cpp
#
# Version: 
#
# Last modified:	2016-02-25 21:41
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

void maxHeapify(int* array, int len, int i);
void buildMaxHeap(int* array, int len);
void maxHeapSort(int* array, int len);

void minHeapify(int* array, int len, int i);
void buildMinHeap(int* array, int len);
void minHeapSort(int* array, int len);

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

	maxHeapSort(array, len);
	cout << "maxHeapSort:";
	printArray(array, len);


	int array2[] = {4,1,3,2,16,9,10,14,8,7};
	minHeapSort(array2, len);
	cout << "minHeapSort:";
	printArray(array2, len);

	return 0;
}

void printArray(int* array, int len) {
	for (int i = 0; i < len; ++i) {
		cout << array[i] << "\t";
	}
	cout << endl;
}

/*最大堆的下降函数:在左右子数已经为最大堆时,调整根节点,使其形成新的最大堆*/
void maxHeapify(int* array, int len, int i) {
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int largest = i;
	if (left < len && array[left] > array[largest]) {
		largest = left;
	}
	if (right < len && array[right] > array[largest]) {
		largest = right;
	}
	if (largest != i) {
		int temp = array[largest];
		array[largest] = array[i];
		array[i] = temp;
		maxHeapify(array, len, largest);
	}	
}

/*建立最大堆*/
void buildMaxHeap(int* array, int len) {
	for (int i = (len/2 - 1); i >= 0; --i) {
		maxHeapify(array, len, i);
	}
}

/*最大堆排序算法*/
void maxHeapSort(int* array, int len) {
	buildMaxHeap(array, len);
	cout << "maxHeap:";
	printArray(array, len);
	int temp;
	int heapsize = len;
	for (int i = len - 1; i >=0; --i) {
		temp = array[0];
		array[0] = array[i];
		array[i] = temp;
		heapsize--;
		maxHeapify(array, heapsize, 0);
	}	
}

/*最小堆的下降函数:在左右子数已经为最小堆时,调整根节点,使其形成新的最小堆*/
void minHeapify(int* array, int len, int i) {
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int min = i;
	if (left < len && array[left] < array[min]) {
	  min = left;
	}
	if (right < len && array[right] < array[min]) {
		min = right;
	}
	if (min != i) {
		int temp = array[min];
		array[min] = array[i];
		array[i] = temp;
		minHeapify(array, len, min);
	}	
}

/*建立最小堆*/
void buildMinHeap(int* array, int len) {
	for (int i = (len/2 - 1); i >= 0; --i) {
		minHeapify(array, len, i);
	}
}

/*最小堆排序算法*/
void minHeapSort(int* array, int len) {
	buildMinHeap(array, len);
	cout << "minHeap:";
	printArray(array, len);
	int temp;
	int heapsize = len;
	for (int i = len - 1; i >=0; --i) {
		temp = array[0];
		array[0] = array[i];
		array[i] = temp;
		heapsize--;
		minHeapify(array, heapsize, 0);
	}	
}
