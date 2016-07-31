#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

int N,M;
char per[20];
char ipf[100];

class TrieNode {
public:
  TrieNode(){
    isComplete = false;
    isAllow = false;
    mask = 32;
    priority = -1;
    next[0] = NULL;
    next[1] = NULL;
  }

  bool isComplete;
  bool isAllow;
  int mask;
  int priority;
  TrieNode *next[2];
};

unsigned int getIp(int num[]) {
  unsigned int ip = 0;
  for(int i=0; i<3; i++){
    ip |= num[i];
    ip = ip<<8;
  }
  ip |= num[3];
  return ip;
}

void insertTrieNode(TrieNode *root, bool isAllow, int mask, unsigned int ip, int priority){
  int len = min(mask, 32);
  unsigned int high = (1<<31);
  for(int i=0; i<len; i++){
    int t = ((high&ip)>>31);
    ip = (ip<<1);
    if(root->next[t] == NULL){
      root->next[t] = new TrieNode();
    }
    root = root->next[t];
  }

  if(root->isComplete == false){      //当有重复的规则的时候保证高优先级不会被低优先级覆盖
    root->isAllow = isAllow;
    root->mask = mask;
    root->priority = priority;
    root->isComplete = true;
  }


}

void constructTrieTree(TrieNode *root,char a[], char b[], int priority){
  bool isAllow = false;
  int mask=32;
  unsigned int ip=0;
  if(a[0] == 'a'){
    isAllow = true;
  }

  int num[4];
  if(sscanf_s(b, "%d.%d.%d.%d/%d", &num[0], &num[1], &num[2], &num[3], &mask) == 4){
    mask = 32;
  }

  ip = getIp(num);

  insertTrieNode(root, isAllow,mask, ip, priority);

}



bool searchIp(TrieNode *root, char sip[]){

  unsigned ip=0;
  bool res = true;       //初始值要根据题意来而不是随意指定的
  int tpriority = -1;

  int num[4];
  sscanf_s(sip, "%d.%d.%d.%d", &num[0], &num[1], &num[2], &num[3]);
  ip = getIp(num);

  unsigned int high = (1<<31);
  while(root){              //不能只遍历前32个
    int t = ((high&ip)>>31);
    ip = (ip<<1);

    if(root->isComplete){
      if(tpriority == -1 || root->priority < tpriority){     //路由表匹配有优先级
        tpriority = root->priority;
        res = root->isAllow;
      }
    }

    root = root->next[t];
  }

  return res;
}

//int main()
//{
//  //freopen("input.txt", "r", stdin);                    //提交的时候要记得去掉
//  scanf("%d %d", &N, &M);
//  TrieNode *root = new TrieNode();
//  for(int i=0; i<N; i++){
//    scanf("%s %s", per, ipf);
//    constructTrieTree(root, per, ipf, i);
//  }
//
//  for(int i=0; i<M; i++){
//    char ip[100];
//    scanf("%s", ip);
//    if(searchIp(root, ip)){
//      printf("YES\n");
//    }else {
//      printf("NO\n");
//    }
//  }
//
//  return 0;
//}