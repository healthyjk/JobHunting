/*======================================================
#
# Filename: BSortTree.cpp
#
# Version: 
#
# Last modified: 2016-02-26 15:03
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
#include "BTreeNode.h"

template<class T> 
class BinarySearchTree {
	private:
		BTreeNode<T>* _pRoot;
		int _size;

	public:
		BinarySearchTree(void) {
			_pRoot = NULL;
			_size = 0;
		}

		BinarySearchTree(BTreeNode<T>* pRoot) {
			_pRoot = pRoot;
		}

		BinarySearchTree(const BinarySearchTree& bst) {
			_pRoot = bst.root();
			_size = bst.size();
		}

		~BinarySearchTree(void) {
		
		}

		int size() const { return _size; }
		BTreeNode<T>* root() const { return _pRoot; }

		void insert(T val) {
			if (_pRoot == NULL) {
				BTreeNode<T> *pNode = new BTreeNode<T>(val);
				_pRoot = pNode;
				_size++;
				return;
			}
			insertTree(_pRoot, val);
		}


		void inOrderWalk() {
			inOrderTreeWalk(_pRoot);
		}

		void preOrderWalk() {
			preOrderTreeWalk(_pRoot);
		}

		void postOrderWalk() {
			postOrderTreeWalk(_pRoot);
		}

		BTreeNode<T>* search(T val) {
			return searchTree(_pRoot, val);
		}

		BTreeNode<T>* searchMaxVal() const {
			return searchTreeMaxVal(_pRoot);
		}

		BTreeNode<T>* searchMinVal() const {
			return searchTreeMinVal(_pRoot);
		}

		void deleteNode(T val) {
			deleteTreeNode(_pRoot, val);
		}

		bool contain(T val) {
			BTreeNode<T>* pNode = search(val);
			if (NULL == pNode) {
				return false;
			} else {
				return true;
			}
		}

		BTreeNode<T>* inOrderPostNode(T val);

	private:
		void preOrderTreeWalk(BTreeNode<T>* pRoot);
		void postOrderTreeWalk(BTreeNode<T>* pRoot);
		void inOrderTreeWalk(BTreeNode<T>* pRoot);
		void insertTree(BTreeNode<T>* pRoot, T node);
		void deleteTreeNode(BTreeNode<T>* pRoot, T val);
		BTreeNode<T>* searchTree(BTreeNode<T>* pRoot, T val);
		BTreeNode<T>* searchTreeIterative(BTreeNode<T>* pRoot, T val);
		BTreeNode<T>* searchTreeMaxVal(BTreeNode<T>* pRoot);
		BTreeNode<T>* searchTreeMinVal(BTreeNode<T>* pRoot);
};

template<class T>
void BinarySearchTree<T>::inOrderTreeWalk(BTreeNode<T>* pRoot) {
	if (pRoot != NULL) {
		BinarySearchTree::inOrderTreeWalk(pRoot->left);
		std::cout << pRoot->valToString() << "\t";
		BinarySearchTree::inOrderTreeWalk(pRoot->right);	
	}
}

template<class T>
void BinarySearchTree<T>::preOrderTreeWalk(BTreeNode<T>* pRoot) {
	if (pRoot != NULL) {
		std::cout << pRoot->valToString() << "\t";
		BinarySearchTree::preOrderTreeWalk(pRoot->left);
		BinarySearchTree::preOrderTreeWalk(pRoot->right);	
	}
}

template<class T>
void BinarySearchTree<T>::postOrderTreeWalk(BTreeNode<T>* pRoot) {
	if (pRoot != NULL) {
		BinarySearchTree::postOrderTreeWalk(pRoot->left);
		BinarySearchTree::postOrderTreeWalk(pRoot->right);	
		std::cout << pRoot->valToString() << "\t";
	}
}

template<class T>
void BinarySearchTree<T>::insertTree(BTreeNode<T>* pRoot, T val) {
	BTreeNode<T>* pNode = new BTreeNode<T>(val);
	if (NULL == pRoot) {
		pRoot = pNode;
		_size++;
		return;
	}
	if (NULL == pRoot->left && val < pRoot->val) {
		pRoot->left = pNode;
		pNode->parent = pRoot;
		_size++;
		return;
	} 
	if (NULL == pRoot->right && val >= pRoot->val) {
		pRoot->right = pNode;
		pNode->parent = pRoot;
		_size++;
		return;
	}
	if (val < pRoot->val) {
		insertTree(pRoot->left, val);
	} else {
		insertTree(pRoot->right, val);
	}
}

template<class T>
void BinarySearchTree<T>::deleteTreeNode(BTreeNode<T>* pRoot, T val) {
	BTreeNode<T>* pNode = searchTree(pRoot, val);
	if (NULL == pNode) return; //节点不存在
	//1.被删节点是叶子节点,直接删
	if (NULL == pNode->left && NULL == pNode->right) {
		if (NULL == pNode->parent) {
			//该树只有一个节点
			_size = 0;
			_pRoot = NULL;
		} else if (pNode->parent->left == pNode) {
			//被删结点是左孩子
			pNode->parent->left = NULL;
		}	else {
			//被删结点是右孩子
			pNode->parent->right = NULL;
		}
		delete pNode;
		_size--;
		return;
	} 

	//2.被删结点只有左子树
	if (NULL != pNode->left && NULL == pNode->right) {
		pNode->left->parent = pNode->parent;
		if (NULL == pNode->parent) {
			_pRoot = pNode->left;
		} else if (pNode->parent->left == pNode) {
			pNode->parent->left = pNode->left;
		} else {
			pNode->parent->right = pNode->left;
		}
		delete pNode;
		_size--;
		return;
	}

	//3.被删结点只有右子树
	if (NULL == pNode->left && NULL != pNode->right) {
		pNode->right->parent = pNode->parent;
		if (NULL == pNode->parent) {
			_pRoot = pNode->right;
		} else if (pNode->parent->left == pNode) {
			pNode->parent->left = pNode->right; 
		} else {
			pNode->parent->right = pNode->right;
		}
		delete pNode;
		_size--;
		return;
	}

	//4.被删结点有左右子树:如果二叉查找树的某个结点有两个子女, 则其后继没有左子女
	if (NULL != pNode->left && NULL != pNode->right) {
		BTreeNode<T>* replaceNode = searchTreeMinVal(pNode->right);
		pNode->val = replaceNode->val;
		deleteTreeNode(pNode->right, replaceNode->val);
	}
}

template<class T>
BTreeNode<T>* BinarySearchTree<T>::searchTree(BTreeNode<T>* pRoot, T val) {
	if (pRoot == NULL || pRoot->val == val) {
		return pRoot;
	}	
	if (val < pRoot->val) {
		return searchTree(pRoot->left, val);
	} else {
		return searchTree(pRoot->right, val);
	}
}

template<class T>
BTreeNode<T>* BinarySearchTree<T>::searchTreeIterative(BTreeNode<T>* pRoot, T val) {
	while (NULL != pRoot && pRoot->val == val) {
		if (val < pRoot->val) {
			pRoot = pRoot->left;
		} else {
			pRoot = pRoot->right;
		}
	}
	return pRoot;
}

template<class T>
BTreeNode<T>* BinarySearchTree<T>::searchTreeMaxVal(BTreeNode<T>* pRoot) {
	if (NULL == pRoot) {
		return NULL;
	}
	if (NULL == pRoot->right) {
		return pRoot;
	}
	return searchTreeMaxVal(pRoot->right);
}

template<class T>
BTreeNode<T>* BinarySearchTree<T>::searchTreeMinVal(BTreeNode<T>* pRoot) {
	if (NULL == pRoot) {
		return NULL;
	}
	if (NULL == pRoot->left) {
		return pRoot;
	}
	return searchTreeMinVal(pRoot->left);	
}

template<class T>
BTreeNode<T>* BinarySearchTree<T>::inOrderPostNode(T val) {
	BTreeNode<T>* pNode = BinarySearchTree<T>::search(val);
	if (NULL == pNode) {
		return NULL;
	}
	if (NULL != pNode->right) {
		return searchTreeMinVal(pNode->right);
	} else {
		BTreeNode<T>* postNode;
		postNode = pNode->parent;
		while (NULL != postNode && pNode == postNode->right) {
			pNode = postNode;
			postNode = pNode->parent;
		}
		return postNode;
	}
}
