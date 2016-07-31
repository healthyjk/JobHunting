/*======================================================
#
# Filename: addTwoNumber.cpp
#
# Version: 
#
# Last modified: 2016-03-13 20:18
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
#include <vector>
#include <malloc.h>
#include <ctime>

using namespace std;


//Definition for singly-linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
	public:

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    if (l1 == NULL) return l2;
	if (l2 == NULL) return l1;
	struct ListNode* head = l1;
	l1->val += l2->val;

	while (NULL != l1->next && NULL != l2->next) {
		if (l1->val > 9) {
			l1->val %= 10;
			l1->next->val ++;
		}
		l1->next->val += l2->next->val;
		l1 = l1->next;
		l2 = l2->next;
	}
	
	if (NULL != l2->next) {
		l1->next = l2->next;
	}

	while (l1->val > 9) {
		l1->val %= 10;
		if (NULL == l1->next) {
			l1->next = (struct ListNode*)malloc(sizeof(struct ListNode));
		} else {
			l1->next->val++;
			l1 = l1->next;
		}
	}

	return head;
}
		
	ListNode* addTwoNumbers4(ListNode* l1, ListNode* l2) {
			if (l1 == NULL) return l2;
			if (l2 == NULL) return l1;
			ListNode* head = l1;
			l1->val += l2->val;

			while (NULL != l1->next && NULL != l2->next) {
				if (l1->val > 9) {
					l1->val %= 10;
					l1->next->val ++;
				}
				l1->next->val += l2->next->val;
				l1 = l1->next;
				l2 = l2->next;
			}
			if (NULL != l2->next) {
				l1->next = l2->next;
			}

			while (l1->val > 9) {
				l1->val %= 10;
				if (NULL == l1->next) {
					l1->next = new ListNode(1);
				} else {
					l1->next->val++;
					l1 = l1->next;
				}
			}

			return head;
		}



		ListNode* addTwoNumbers3(ListNode* l1, ListNode* l2) {
			if (l1 == NULL) return l2;
			if (l2 == NULL) return l1;
			int c = 0;
		  int	v1, v2;
			ListNode* head;
			ListNode* p;
			int flag = 0;
			while (l1 || l2) {
				int v1 = NULL == l1 ? 0 : l1->val;
				int v2 = NULL == l2 ? 0 : l2->val;
				int val = v1 + v2 + c;
				c = 0;
				if (val >= 10) {
					val = val % 10;
					c = 1;
				}
				ListNode* pNode = new ListNode(val);
				if (flag == 0) {
					head = pNode;
					p = pNode;
				} else {
					p->next = pNode;
					p = pNode;
				}

				if (l1) {
					l1 = l1->next;
				}
				if (l2) {
					l2 = l2->next;
				}
				flag++;
			}
			return head;
		}

		ListNode* addTwoNumbers2(ListNode* l1, ListNode* l2) {
			vector<int> v1, v2, vo;
			while (l1) {
				v1.push_back(l1->val);
				l1 = l1->next;
			}
			while (l2) {
				v2.push_back(l2->val);
				l2 = l2->next;
			}
			int m = v1.size();
			int n = v2.size();

			int max = m > n? m : n;
			int n1, n2, num;
			int c = 0;
			ListNode* head;
			ListNode* p;
			
			for (int i = 0; i < max; ++i) {
				n1 = i < m ? v1[i] : 0;
				n2 = i < n ? v2[i] : 0;
				num = n1 + n2 + c;
				c = 0;
				if (num >= 10) {
					num %= 10;
					c = 1;
				}
				ListNode* node = new ListNode(num);
				if (i == 0) {
					head = node;
				} else {
					p->next = node;
				}
				p = node;
			}

			if (c == 1) {
				ListNode* node = new ListNode(1);
				p->next = node;
			}

			return head;
		}
};

int main() {
	ListNode* l1;
	ListNode* l2;
  ListNode*	head;

	
	ListNode a1(2);
	ListNode a2(4);
	ListNode a3(3);
	ListNode a4(3);
	ListNode b1(5);
	ListNode b2(6);
	ListNode b3(4);

	l1 = &a1;
	a1.next = &a2;
	a2.next = &a3;
	a3.next = &a4;

	l2 = &b1;
	b1.next = &b2;
	b2.next = &b3;   

	/*
	ListNode a1(5);
	ListNode b1(5);
	l1 = &a1;
	l2 = &b1;   */

	clock_t start, end;

	Solution solution;
	start = clock();
	head = solution.addTwoNumbers(l1, l2);
	end = clock();
	cout << "Results:";
	while (NULL != head) {
		cout << head->val;
		if (head->next != NULL) {
			cout << "->";
		}
		head = head->next;
	}
	cout << endl;
	cout << "Runtime:" << (double)(end-start)*1000/CLOCKS_PER_SEC << "ms." << endl;

	start = clock();
	head = solution.addTwoNumbers2(l1, l2);
	end = clock();
	cout << "Results:";
	while (NULL != head) {
		cout << head->val;
		if (head->next != NULL) {
			cout << "->";
		}
		head = head->next;
	}
	cout << endl;
	cout << "Runtime:" << (double)(end-start)*1000/CLOCKS_PER_SEC << "ms." << endl;

	return 0;
}
