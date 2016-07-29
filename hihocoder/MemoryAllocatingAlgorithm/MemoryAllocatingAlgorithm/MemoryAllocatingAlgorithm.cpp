// MemoryAllocatingAlgorithm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct MemoryDataList {
	int num;
	int size;
	MemoryDataList* prev;
	MemoryDataList* next;
	MemoryDataList(int num, int size) : num(num), size(size), prev(NULL), next(NULL) {}
};

vector<MemoryDataList*> pos;

void insertNode(MemoryDataList* emptyNode, int num, int size) {
	if (emptyNode->size == size) {
		emptyNode->num = num;
		pos.push_back(emptyNode);
		return;
	} 
	MemoryDataList* node = new MemoryDataList(num, size);
	node->next = emptyNode;
	node->prev = emptyNode->prev;
	emptyNode->prev->next = node;
	emptyNode->prev = node;
	emptyNode->size -= size;
	pos.push_back(node);
}

void deleteNode(MemoryDataList* const head, int k) {
	if (k >= pos.size()) return;
	MemoryDataList* p = pos[k];
	p->num = 0;
	if (p != NULL) {
		while (p->prev->num == 0) {
			p->prev->next = p->next;
			p->next->prev = p->prev;
			p->prev->size += p->size;
			MemoryDataList* tmp = p->prev;
			delete p;
			p = tmp;
		}

		while (p->next->num == 0) {
			p->next->next->prev = p;
			p->size += p->next->size;
			MemoryDataList* tmp = p->next;
			p->next = p->next->next;
			delete tmp;
		}
	}
	return;
}

void freeMemoryList(MemoryDataList* head) {
	MemoryDataList* p = head, *n = NULL;
	while (p != NULL) {
		n = p->next;
		delete p;
		p = n;
	}
}

MemoryDataList* findEmptyInsertNode(MemoryDataList* head, int need_size) {
	MemoryDataList* p = head;
	while (NULL != p->next) {
		if (p->num == 0 && p->size >= need_size) {
			return p;
		}
		p = p->next;
	}
	if (NULL == p->next) return NULL;
}

vector<pair<int, int> > getFinalMemoryCount(int n, int m, vector<int>& data_size) {
	MemoryDataList* head = new MemoryDataList(-1, 0);
	MemoryDataList* node = new MemoryDataList(0, m);
	MemoryDataList* tail = new MemoryDataList(-1, 0);
	head->next = node;
	node->prev = head;
	node->next = tail;
	tail->prev = node;
	int lastDelete = 0;

	for (int i = 0; i < n; ++i) {
		while (true) {
			MemoryDataList* emptyNode = findEmptyInsertNode(head, data_size[i]);
			if (NULL != emptyNode) {
				insertNode(emptyNode, i+1, data_size[i]);
				break;
			} else {
				deleteNode(head, lastDelete++);
			}
		}
	}
	MemoryDataList* p = head->next;
	vector<pair<int,int> > result;
	int index = 0;
	while (NULL != p->next) {
		if (p->num != 0) {
			result.push_back(make_pair(p->num, index));
		}
		index += p->size;
		p = p->next;
	}
	freeMemoryList(head);
	return result;
}

bool comparePair(const pair<int, int>& a, const pair<int, int>& b) {
	return a.first < b.first;
}

int main()
{
	ifstream cin("input.txt");

	int n, m;
	while (cin >> n >> m) {
		vector<int> data_size(n, 0);
		for (int i = 0; i < n; ++i) {
			cin >> data_size[i];
		}
		vector<pair<int, int> > result = getFinalMemoryCount(n, m, data_size);
		sort(result.begin(), result.end(), comparePair);
		for (int i = 0; i < result.size(); ++i) {
			cout << result[i].first << " " << result[i].second << endl;
		}
	}

	return 0;
}

