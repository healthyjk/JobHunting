// FullBinaryTreePicture.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Node {
  int x;
  int y;
  int height;
  Node* left;
  Node* right;
  Node(int x, int y) : x(x), y(y), left(NULL), right(NULL) {}
};

int getStepByHeight(int height) {
  if (height == 1) return 0;
  if (height == 2) return 1;
  if (height == 3) return 2;
  return (2*getStepByHeight(height - 1) + 1);
}



void buildTreeWithHeight(Node* root, int height) {
  if (height == 1) return;
  int step = getStepByHeight(height) + 1;
  Node* left = new Node(root->x + step, root->y - step);
  Node* right = new Node(root->x + step, root->y + step);
  root->left = left;
  root->right = right;
  buildTreeWithHeight(left, height-1);
  buildTreeWithHeight(right, height-1);
}

int countTreeNodeInRectangle(Node* root, int x1, int y1, int x2, int y2) {
  int count = 0;
  if (root->x >= x1 && root->x <= x2 && root->y >= y1 && root->y <= y2) {
    count++;
  }
  if (NULL != root->left) {
    count += countTreeNodeInRectangle(root->left, x1, y1, x2, y2);
  }

  if (NULL != root->right) {
    count += countTreeNodeInRectangle(root->right, x1, y1, x2, y2);
  }
  return count;
}

int main() {
  ifstream cin("input.txt");
  int n, m;
  while (cin >> n >> m) {
    Node* root = new Node(0, 0);
    buildTreeWithHeight(root, n);

    int x1, y1, x2, y2;
    for (int i = 0; i < m; ++i) {
      cin >> x1 >> y1 >> x2 >> y2;
      int count = countTreeNodeInRectangle(root, x1, y1, x2, y2);
      cout << count << endl;
    }
  }

  return 0;
}
