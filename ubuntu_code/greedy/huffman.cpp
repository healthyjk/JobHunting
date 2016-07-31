/*======================================================
#
# Filename: huffman.cpp
#
# Version: 
#
# Last modified: 2016-03-08 20:26
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
#include "minHeap.hpp"
#include "BinaryTree.hpp"

using namespace std;

template<class T> class Huffman;  

template<typename T>
Huffman<T> huffmanTree(T freq[], int n);

template<typename T> 
class Huffman {
	public:
		friend Huffman<T> huffmanTree(T[], int);

		operator T() const {
			return weight;
		}

	//private:
		BinaryTree<int> tree;
		T weight;
};

int main() {
	const int N = 6;
	char chars[] = {'0', 'a', 'b', 'c', 'd', 'e', 'f'};
	int freq[] = {0, 45, 13, 12, 16, 9, 5};
	cout << "字符出现的频率分别为：" ;
	for (int i = 0; i < N; ++i) {
		cout << chars[i] << ":" << freq[i] << "\t";
	}
	cout << endl;

	BinaryTree<int> t = huffmanTree(freq, N).tree;

	cout << "preOrder:" ;
	t.preOrder();
	cout << endl;

	cout << "inOrder:" ;
	t.inOrder();
	cout << endl;

	cout << "postOrder:" ;
	t.postOrder();
	cout << endl;

	t.destory();

	return 0;
}

template<typename T>
Huffman<T> huffmanTree(T freq[], int n) {
	Huffman<T> *w = new Huffman<T>[n+1];
	Huffman<T> x;
	Huffman<T> y;
	BinaryTree<int> z, zero;
	MinHeap<Huffman<T> > Q;

	for (int i = 1; i <= n; ++i) {
		z.buildTree(i, zero, zero);
		w[i].weight = freq[i];
		w[i].tree = z;
	}

	cout << "init" << endl;

	for (int i = 1; i <= n; ++i) {
		Q.insert(w[i]);
	}	

	cout << "init Q" << endl;

	for (int i = 1; i < n; ++i) {
		x = Q.extractMin();
		y = Q.extractMin();
		z.buildTree(x.weight+y.weight, x.tree, y.tree);
		x.weight += y.weight;
		x.tree = z;
		Q.insert(x);
	}
	cout << "huffman Q" << endl;

	x = Q.extractMin();

	x.tree.preOrder();
	cout << endl;

	x.tree.inOrder();
	cout << endl;

	x.tree.postOrder();
	cout << endl;

	return x;
}


