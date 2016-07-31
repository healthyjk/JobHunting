/*======================================================
#
# Filename: heap.hpp
#
# Version: 
#
# Last modified: 2016-02-25 14:30
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

class MaxHeap {
	public:
		MaxHeap(int heapsize) {
			_size = 1024;
			_array = new int[_size];
			_heapsize = heapsize;
		}	
		
		MaxHeap(int size, int heapsize) {
			_array = new int[size];
			_size = size;
			_heapsize = heapsize;
		}  

		MaxHeap(int* array, int len) {
			_array = new int[len];
			_size = len;
			_heapsize = len;
			for (int i = 0; i < _size; ++i) {
				_array[i] = array[i];
			}
		}

		~MaxHeap() {
			if (_array) delete _array;
		}

		void maxHeapify(int index) { 
			int left = 2 * index + 1;
			int right = 2 * index + 2;
			int largest = index;
			if (left < _heapsize && _array[left] > _array[largest]) {
				largest = left;
			}
			if (right < _heapsize && _array[right] > _array[largest]) {
				largest = right;
			}
			if (index != largest) {
				int temp = _array[index];
				_array[index] = _array[largest];
				_array[largest] = temp;
				maxHeapify(largest);
			}
		}

		void buildMaxHeap() { 
			for (int i = _heapsize / 2 - 1; i >= 0; --i) {
				maxHeapify(i);
			}
		}

		void printMaxHeapArray() { 
			for (int i = 0; i < _heapsize; ++i) {
				std::cout << _array[i] << "\t";
			}
			std::cout << std::endl;
		}

		void sortMaxHeap() { 
			buildMaxHeap();
			std::cout << "Before sort:";
			printMaxHeapArray();
			int temp_heapsize = _heapsize;
			for (int i = _heapsize-1; i >= 0; --i) {
				int temp = _array[i];
				_array[i] = _array[0];
				_array[0] = temp;
				_heapsize--;
				maxHeapify(0);
			}
			_heapsize = temp_heapsize;
			std::cout << "After sort:";
			printMaxHeapArray();
		}
		
	private:
		int* _array;
		int _size;
		int _heapsize;
};

int main() {
	int a[] = {4,1,3,2,16,9,10,14,8,7};
	MaxHeap myheap(a, 10);
	//myheap.buildMaxHeap();
	//myheap.printMaxHeapArray();
	myheap.sortMaxHeap();
}
