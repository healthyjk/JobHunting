#include "stdafx.h"

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

struct TrieNode {
  TrieNode* next[2];
  int index;  //inout order
  bool flag;  //allow or deny
  bool end;   //is end of a rule
  TrieNode() {
    memset(next, 0, sizeof(next));
    flag = false;
    index = -1;
    end = false;
  }
};

TrieNode* root;
int result_index; 
bool result_flag;
int mask0_exist;


void insert(long long ip, int mask, bool flag, int index) {
  long long cnt = (long long)1 << 31;
  TrieNode* p = root;

  for (int i = 0; i < mask; ++i) {
    int num;
    if ((ip & cnt) == cnt) {
      num =1;
    } else {
      num = 0;
    }
    if (p->next[num] == NULL) {
      p->next[num] = new TrieNode();
    }
    p = p->next[num];
    cnt >>= 1;
  }

  if (p->index == -1) {   //just assign once
    p->index = index;
    p->flag = flag;
  }

  p->end = true;
}

bool search(long long ip) {
  TrieNode* p = root;
  long long cnt = (long long)1 << 31;
  for (int i = 0; i < 32; ++i) {
    int num;
    if ((ip & cnt) == cnt) {
      num =1;
    } else {
      num = 0;
    }

    if (p->next[num] == NULL) {
      break;
    } else {
      if (p->next[num]->end) {
        if (result_index == -1 
          || p->next[num]->index < result_index) {
            result_index = p->next[num]->index;
            result_flag = p->next[num]->flag;
        }
      }
    }
  }

  if (result_index != -1) {
    return result_flag;
  } else {
    if (mask0_exist != 0) {
      return true;
    } else {
      return false;
    }
  }

}


int main() {
  int n, m;
  cin >> n >> m;

  root = new TrieNode();
  char rule[20];
  
  for (int i = 0; i < n; ++i) {
    scanf_s("%s", rule);
    long long a, b, c, d;
    char cc;
    scanf_s("%lld.%lld.%lld.%lld", &a, &b, &c, &d);
    cc = getchar();
    int mask = 32;
    if (cc == '/') {
      scanf_s("%d", &mask);
    }
    if (mask == 0) {
      if (mask0_exist == -1) {
        if (strcmp(rule, "allow") == 0) {
          mask0_exist = 1;
        } else {
          mask0_exist = 0;
        }
      } 
    }

    long long temp = (a << 24) | (b << 16) | (c << 8) | d;
    if (strcmp(rule, "allow") == 0) {
      insert(temp, mask, true, i);
    } else {
      insert(temp, mask, false, i);
    }
  }

  for (int i = 0; i < m; ++i) {
    long long a, b, c, d;
    char cc;
    scanf_s("%lld.%lld.%lld.%lld", &a, &b, &c, &d);
    long long temp = (a << 24) | (b << 16) | (c << 8) | d;
    result_index = -1;
    bool flag = search(temp);
    if (flag) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
  return 0;
}