/*======================================================
#
# Filename: maxHeap.h
#
# Version: 
#
# Last modified: 2016-03-08 20:39
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

#ifndef _MAX_HEAP_
#define _MAX_HEAP_

class MaxHeap {
	public:
		MaxHeap(int heapsize);	
		
		MaxHeap(int size, int heapsize);

		MaxHeap(int* array, int len);

		~MaxHeap();

		int size() { return _size; }
		int heapsize() { return _heapsize; }

		void setSize(int size) { _size = size; }
		void setHeapSize(int heapsize) { _heapsize = heapsize; }

		void maxHeapify(int index);

		void buildMaxHeap();

		void printMaxHeapArray();

		void sortMaxHeap();
		
	private:
		int* _array;
		int _size;
		int _heapsize;
};

#endif
