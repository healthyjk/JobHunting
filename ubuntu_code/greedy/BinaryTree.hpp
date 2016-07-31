/*======================================================
#
# Filename: BinaryTree.hpp
#
# Version: 
#
# Last modified: 2016-03-08 21:53
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
class BinaryTree {
	public:
		BinaryTree();
		~BinaryTree();

		BTreeNode<T>* root() { return _root; };

		void preOrder();
		void inOrder();
		void postOrder();

		int height() const;
		int nodeCount() const;

		void destory();
		void buildTree(T data, BinaryTree<T> leftTree, BinaryTree<T> rightTree);
		void change(BTreeNode<T> *r);

	private:
		void destoryTree(BTreeNode<T>* root);
		void preOrderTree(BTreeNode<T>* root);
		void inOrderTree(BTreeNode<T>* root);
		void postOrderTree(BTreeNode<T>* root);
		void treeHeight(const BTreeNode<T>* root) const;
		void treeNodeCount(const BTreeNode<T>* root) const;

	private:
		BTreeNode<T>* _root;
};

template<class T>
BinaryTree<T>::BinaryTree() {
	_root = NULL;
}

template<class T>
BinaryTree<T>::~BinaryTree() {

}

template<class T>
void BinaryTree<T>::preOrder() {
	preOrderTree(_root);
}

template<class T>
void BinaryTree<T>::inOrder() {
	inOrderTree(_root);
}

template<class T>
void BinaryTree<T>::postOrder() {
	postOrderTree(_root);
}

template<class T>
int BinaryTree<T>::height() const {
	return treeHeight(_root);
}

template<class T>
int BinaryTree<T>::nodeCount() const {
	return treeNodeCount(_root);
}

template<class T>
void BinaryTree<T>::destory() {
	destoryTree(_root);
}

template<class T>
void BinaryTree<T>::buildTree(T val, BinaryTree<T> leftTree, BinaryTree<T> rightTree) {
	_root = new BTreeNode<T>();
	_root->val = val;
	_root->left = leftTree.root();
	_root->right = rightTree.root();
}

/* 将二叉树所有结点的左右子树交换 */
template<class T>
void BinaryTree<T>::change(BTreeNode<T> *root) {
	BTreeNode<T>* p;
	if (NULL != root) {
		p = root->left;
		root->left = root->right;
		root->right = p;
		change(root->left);
		change(root->right);
	}
}

template<class T>
void BinaryTree<T>::destoryTree(BTreeNode<T>* root) {
	if (NULL == root) return;
	destoryTree(root->left);
	destoryTree(root->right);
	delete root;
	root = NULL;
}

template<class T>
void BinaryTree<T>::preOrderTree(BTreeNode<T>* root) {
	if (NULL == root) return;
	std::cout << root->val << "\t";
	preOrderTree(root->left);
	preOrderTree(root->right);
}

template<class T>
void BinaryTree<T>::inOrderTree(BTreeNode<T>* root) {
	if (NULL == root) return;
	inOrderTree(root->left);
	std::cout << root->val << "\t";
	inOrderTree(root->right);
}

template<class T>
void BinaryTree<T>::postOrderTree(BTreeNode<T>* root) {
	if (NULL == root) return;
	postOrderTree(root->left);
	postOrderTree(root->right);
	std::cout << root->val << "\t";
}

template<class T>
void BinaryTree<T>::treeHeight(const BTreeNode<T>* root) const {
	if (NULL == root) return 0;
	int lh = treeHeight(root->left);
	int rh = treeHeight(root->right);
	return 1+(lh > rh? lh : rh);
}

template<class T>
void BinaryTree<T>::treeNodeCount(const BTreeNode<T>* root) const {
	if (NULL == root) return 0;
	int lc = treeNodeCount(root->left);
	int rc = treeNodeCount(root->right);
	return (1+lc+rc);
}
