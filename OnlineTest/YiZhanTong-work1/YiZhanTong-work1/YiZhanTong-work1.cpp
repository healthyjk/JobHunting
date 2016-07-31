// YiZhanTong-work1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;



struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};

TreeNode* transArrayToTree(vector<int>& values) {
  int n = values.size();
  if (n <= 0) return NULL;
  vector<TreeNode*> pNodes; 
  for (int i = 0; i < n; ++i) {
    TreeNode* node = new TreeNode(values[i]);
    pNodes.push_back(node);
  }
  int left, right;
  for (int i = 0; i < n; ++i) {
    left = (i << 1) + 1;
    if (left < n) {
      pNodes[i]->left = pNodes[left];
    } else {
      pNodes[i]->left = NULL;
    }
    right = (i << 1) + 2;
    if (right < n) {
      pNodes[i]->right = pNodes[right];
    } else {
      pNodes[i]->left = NULL;
    }
  }
  return pNodes[0];
}

void destroyTree(TreeNode* root) {
  if (root == NULL) return;
  if (root->left == NULL && root->right == NULL) {
    delete root;
    root = NULL;
    return ;
  } 
  destroyTree(root->left);
  destroyTree(root->right);
  delete root;
  root = NULL;
}

class LongestPath {
public:
    int findPath(TreeNode* root) {
        int max = 0;
        findPathIter(root, max);
        return max;
    }
    
    int findPathIter(TreeNode* root, int& max) {
        if (NULL == root) {
            return 0;
        }
        if (NULL == root->left && NULL == root->right) return 1;
        
        int left_max = 0, right_max = 0;
        
        if (NULL != root->left) {
            left_max = findPathIter(root->left, max);
        }
        if (NULL != root->right) {
            right_max = findPathIter(root->right, max);
        }
        
        int r_left, r_right;
        if (left_max > 0 && root->val == root->left->val) {
            r_left = left_max + 1;
        } else {
            r_left = 1;
        }
        
        if (right_max > 0 && root->val == root->right->val) {
            r_right = right_max + 1;
        } else {
            r_right = 1;
        }
        
        int r_max = 0;
        if (left_max > 0 && right_max > 0) {
            r_max = ((root->left->val == root->right->val && root->val == root->left->val) ? 
                     (left_max+right_max+1) : (r_left > r_right ? r_left : 

r_right));
        } else {
            r_max = r_left > r_right ? r_left : r_right;
        }
        
        if (r_max > max) {
            max = r_max;
        }
        return (r_left > r_right ? r_left : r_right);
    }
};


int main()
{
  ifstream cin("input.txt");
  int a[] = {1,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1};
  vector<int> values(a, a+sizeof(a)/sizeof(int));
  TreeNode* root = transArrayToTree(values);
  LongestPath longestPath;
  int result = longestPath.findPath(root);
  cout << result << endl;
  destroyTree(root);
	return 0;
}

