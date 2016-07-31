/*======================================================
#
# Filename: BTreeNode.h
#
# Version: 
#
# Last modified: 2016-02-26 14:44
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
#include <sstream>
          
template<class T>
class BTreeNode {
	public:
		T val;
		BTreeNode<T>* left; //指向左孩子的指针
		BTreeNode<T>* right;
		BTreeNode<T>* parent; //指向父结点的指针

		BTreeNode(T tVal){
			val = tVal;
			left = right = parent = NULL;
		}

		bool operator==(BTreeNode<T>* bt) { //重载操作符比较两结点是否相等
			return bt.val == val ? true: false;
		}

		std::string valToString() {
			std::ostringstream oss;
			oss << val;
			return oss.str();
		}
};

