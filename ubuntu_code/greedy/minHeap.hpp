/*======================================================
#
# Filename:		minHeap.hpp
#
# Version: 
#
# Last modified:	2016-03-09 10:26
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


template<class T>
class MinHeap {
	public:
		MinHeap();
		MinHeap(int heapsize);	
		
		MinHeap(int size, int heapsize);

		MinHeap(T* array, int len);

		~MinHeap();

		int size() { return _size; }
		int heapsize() { return _heapsize; }

		void setSize(int size) { _size = size; }
		void setHeapSize(int heapsize) { _heapsize = heapsize; }

		void minHeapify(int index);

		void buildMinHeap();

		void printMinHeapArray();

		void sortMinHeap();

		/*自底向上进行调整，使继续满足最小堆性质*/
		void filterUp(const int index);

		bool insert(const T& x);

		T getMin();
		T extractMin();

		bool isEmpty() const;

		bool isFull() const;
	
	private:
		T* _array;
		int _size;
		int _heapsize;
		const static int BLOCK_NUM = 1024;;
};

template<class T> 
MinHeap<T>::MinHeap() {
	_size = BLOCK_NUM;
	_array = new T[_size];
	_heapsize = 0;
}

template<class T>
MinHeap<T>::MinHeap(int heapsize) {
	_size = BLOCK_NUM;
	_array = new T[_size];
	_heapsize = heapsize;
}	

template<class T>
MinHeap<T>::MinHeap(int size, int heapsize) {
	_array = new T[size];
	_size = size;
	_heapsize = heapsize;
}  

template<class T>
MinHeap<T>::MinHeap(T* array, int len) {
	_array = new T[BLOCK_NUM];
	_size = BLOCK_NUM;
	_heapsize = len;
	for (int i = 0; i < _size; ++i) {
		_array[i] = array[i];
	}
	buildMinHeap();
}

template<class T>
MinHeap<T>::~MinHeap() {
	if (_array) delete[] _array;
}

/*自上而下调整，使关键字小的节点在上*/
template<class T>
void MinHeap<T>::minHeapify(int index) { 
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int least = index;
	if (left < _heapsize && _array[left] < _array[least]) {
		least = left;
	}
	if (right < _heapsize && _array[right] < _array[least]) {
		least = right;
	}
	if (index != least) {
		T temp = _array[index];
		_array[index] = _array[least];
		_array[least] = temp;
		minHeapify(least);
	}
}

template<class T>
void MinHeap<T>::buildMinHeap() { 
	for (int i = _heapsize / 2 - 1; i >= 0; --i) {
		minHeapify(i);
	}
}

template<class T>
void MinHeap<T>::printMinHeapArray() { 
	for (int i = 0; i < _heapsize; ++i) {
		std::cout << _array[i] << "\t";
	}
	std::cout << std::endl;
}

template<class T>
void MinHeap<T>::sortMinHeap() { 
	buildMinHeap();
	std::cout << "Before sort:";
	printMinHeapArray();
	int temp_heapsize = _heapsize;
	for (int i = _heapsize-1; i >= 0; --i) {
		T temp = _array[i];
		_array[i] = _array[0];
		_array[0] = temp;
		_heapsize--;
		minHeapify(0);
	}
	_heapsize = temp_heapsize;
	std::cout << "After sort:";
	printMinHeapArray();
}

template<class T>
void MinHeap<T>::filterUp(const int index) {
	if (index < 0 || index >= _heapsize) return;
	int parent = (index-1) / 2;
	int  i = index;
	T temp = _array[i];
	while (i > 0) {
		if (_array[parent] <= temp) {
			break;
		} else {
			_array[i] = _array[parent];
			i = parent;
			parent = (parent-1)/2;
		}
	}
	_array[i] = temp;
}

template<class T> 
bool MinHeap<T>::insert(const T& x) {
	if (_heapsize == _size) return false;
	int index = _heapsize;
	_array[index] = x;
	_heapsize++;
	filterUp(index);
	return true;
}

template<class T>
T MinHeap<T>::extractMin() {
	T temp = _array[0];
	_heapsize--;
	_array[0] = _array[_heapsize];
	minHeapify(0);
	return temp;
}

template<class T>
T MinHeap<T>::getMin() {
	return _array[0];
}

template<class T>
bool MinHeap<T>::isEmpty() const {
	return _heapsize == 0;
}

template<class T> 
bool MinHeap<T>::isFull() const {
	return _heapsize == _size;
}

