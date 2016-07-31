
#include "stdafx.h"

#include<iostream>
#include<cstdio>
#include<string>
#include<set>
#include<map>
#include<cstring>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<sstream>
#include<limits>
using namespace std;

struct TrieNode{
  TrieNode* next[2];
  int index;
  bool flag;
  bool end;
  TrieNode() {
    memset(next,0,sizeof(next));
    flag=false;
    index=-1;     //�ǵڼ���ip
    end=false;    //�յ��־
  }
};

TrieNode* root;
int res_index;
bool res_f;
int nonExsit;  //��Զ�û��ƥ���ϵ�����������mask=0����������п�����true,�п�����false������nonExsit=-1��˵��û��mask=0�������
void insert(long long tmp,int mask,bool f,int tmp_index) {                       //nonExsit=1��ʾallow��nonExsit=-1����deny
  long long cnt=(long long)1<<31;               //Ҫ��Long longת����
  TrieNode* p=root;
  for(int i=0;i<mask;i++) {
    int num;
    if((tmp&cnt)==cnt) num=1;
    else num=0;
    if(p->next[num]==NULL) {
      p->next[num]=new TrieNode();
    }
    p=p->next[num];
    cnt>>=1;
  }
  if(p->index==-1) {
    p->index=tmp_index;
    p->flag=f;
  }
  p->end=true;
}
bool search(long long tmp) {
  TrieNode* p=root;
  long long cnt=(long long)1<<31;
  for(int i=0;i<32;i++) {
    int num;
    if((tmp&cnt)==cnt) num=1;    //ÿһλ��0����1
    else num=0;
    if(p->next[num]==NULL) {
      break;
    }
    if(p->next[num]->end) {
      if(res_index==-1||p->next[num]->index<res_index) {   //ȡ��С��Index״̬����������ƥ���
        res_index=p->next[num]->index;
        res_f=p->next[num]->flag;
      }
    }
    p=p->next[num];
    cnt>>=1;
  }
  if(res_index==-1) {
    if(nonExsit!=0)
      return true;
    else return false;
  }
  else return res_f;
}


//int main() {
//  int n,m;
//  scanf("%d%d",&n,&m);
//  nonExsit=-1;
//  char ss[20];
//  char ip[101];
//  root=new TrieNode();
//  for(int i=0;i<n;i++) {
//    scanf("%s",ss);
//    long long a,b,c,d;
//    scanf("%lld.%lld.%lld.%lld",&a,&b,&c,&d);
//    char cc=getchar();
//    int mask=32;
//    if(cc=='/') scanf("%d",&mask);
//    if(mask==0) {
//      if(nonExsit==-1) {
//        if(strcmp(ss,"allow")==0) nonExsit=1;
//        else nonExsit=0;
//      }
//    }
//    long long tmp=(a<<24)|(b<<16)|(c<<8)|d;
//    if(strcmp(ss,"allow")==0) {
//      insert(tmp,mask,true,i);
//    }
//    else {
//      insert(tmp,mask,false,i);
//    }
//  }
//  for(int i=0;i<m;i++) {
//    long long a,b,c,d;
//    scanf("%lld.%lld.%lld.%lld",&a,&b,&c,&d);
//    long long tmp=(a<<24)|(b<<16)|(c<<8)|d;
//    res_index=-1;
//    bool f=search(tmp);
//    if(f) printf("YES\n");
//    else printf("NO\n");
//  }
//  return 0;
//}

