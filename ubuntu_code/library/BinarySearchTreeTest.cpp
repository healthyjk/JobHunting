/*======================================================
#
# Filename:		BinarySearchTreeTest.cpp
#
# Version: 
#
# Last modified:	2016-02-26 17:50
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
#include "BinarySearchTree.hpp"

using namespace std;

int main() {
	BinarySearchTree<int> bsTree;
	bsTree.insert(6);
	bsTree.inOrderWalk();
	cout << endl;
	bsTree.insert(66);
	bsTree.inOrderWalk();
	cout << endl;
	bsTree.insert(8);
	bsTree.inOrderWalk();
	cout << endl;
	bsTree.insert(45);
	bsTree.inOrderWalk();
	cout << endl;
	bsTree.insert(0);
	bsTree.inOrderWalk();
	cout << endl;
	bsTree.insert(3);
	bsTree.inOrderWalk();
	cout << endl;
	bsTree.insert(-3);
	bsTree.inOrderWalk();
	cout << endl;
	cout << "postNode:" << (bsTree.inOrderPostNode(-3))->val << endl;
	cout << "postNode:" << (bsTree.inOrderPostNode(66)) << endl;
	cout << "postNode:" << (bsTree.inOrderPostNode(8))->val << endl;
	cout << "postNode:" << (bsTree.inOrderPostNode(45))->val << endl;

	cout << (bsTree.contain(-3) ? "true" : "false") << endl;
	cout << (bsTree.contain(3) ? "true" : "false") << endl;
	cout << (bsTree.contain(1656) ? "true" : "false") << endl;
	cout << "in:";
	bsTree.inOrderWalk();
	cout << endl;
	cout << "pre:";
	bsTree.preOrderWalk();
	cout << endl;
	cout << "post:";
	bsTree.postOrderWalk();
	cout << endl;
	bsTree.deleteNode(-3);
	cout << "in:";
	bsTree.inOrderWalk();
	cout << endl;
	cout << "pre:";
	bsTree.preOrderWalk();
	cout << endl;
	cout << "post:";
	bsTree.postOrderWalk();
	cout << endl;
	bsTree.deleteNode(6);
	cout << "in:";
	bsTree.inOrderWalk();
	cout << endl;
	cout << "pre:";
	bsTree.preOrderWalk();
	cout << endl;
	cout << "post:";
	bsTree.postOrderWalk();
	cout << endl;
}
