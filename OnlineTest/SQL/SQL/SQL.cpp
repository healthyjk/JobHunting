// SQL.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

//�������ܣ����ڸ������ַ����ָ��ַ���
//���룺���ָ��ַ���s, �ָ��ʶ��delim
//�����string vector ret,������ʽ����
//����ֵ����
void split(const string& s, string& delim, vector<string>& ret)  
{  
  size_t last = 0;  
  size_t index=s.find_first_of(delim,last);  
  while (index!=std::string::npos)  
  {  
    ret.push_back(s.substr(last,index-last));  
    last=index+1;  
    index=s.find_first_of(delim,last);  
  }  
  if (index-last>0)  
  {  
    ret.push_back(s.substr(last,index-last));  
  }  
}

string blank = " ";

//�������ܣ�����SQL�е�����SQL���ִ��ʱ���map��ʹ��multimap�� �����ظ�key��
//���룺��ѯ�������sqls, ��ѯ����Ӧִ��ʱ��times
//�������ѯ����е��ʶ�Ӧ��ִ��ʱ��ӳ��word_to_time,������ʽ����
//����ֵ����
void BuildSQLTimeMap(const vector<string>& sqls, const vector<double>& times, multimap<string, double>& word_to_time) {
  int sn = sqls.size();
  vector<string> split_results;
  for (int i = 0; i < sn; ++i) {
    split(sqls[i], blank, split_results);
    //����ͬһ������е��ظ����ʲ��ظ����㣬���ȥ���ظ�Ԫ��
    split_results.erase(unique(split_results.begin(),split_results.end()), split_results.end());
    int count = split_results.size();
    for (int j = 0; j < count; ++j) {
      word_to_time.insert(make_pair(split_results[j], times[i]));
    }
    split_results.clear();
  }
}

//sqls��SQL����б�times�Ƕ�Ӧ��ִ��ʱ�䣬keywords��ÿ�β�ѯ�Ĺؼ��ʡ�
//����ÿ���ؼ��ʶ�Ӧ��ѯ���SQL������SQLִ��ʱ���ƽ��ֵ��
vector<double> BatchQueryExecutionTime(const vector<string>& sqls, const vector<double>& times, const vector<string>& keywords) {
  multimap<string, double> word_to_time;
  //����multimap
  BuildSQLTimeMap(sqls, times, word_to_time);

  vector<double> results;

  for (int i = 0; i < keywords.size(); ++i) {
    //������ѯ���ʣ��õ���������Χ
    auto range = word_to_time.equal_range(keywords[i]);
    double sum = 0;
    int count = 0;
    //���㵥�ʶ�Ӧ������ʱ�䣬ͬһ������е��ظ������Ѿ��޳�
    for (auto j = range.first; j != range.second; ++j) {
      sum += j->second;
      count++;
    }
    results.push_back((sum / count));
  }

  return results;
}




struct SQL {
    string text; //SQL���
    int kind;//��������
    double time;//ִ��ʱ��
    SQL(int text_, int kind_, int time_) {
      text = text_;
      kind = kind_;
      time = time_;
    }
};
 
struct Query {
    string keyword;// ��ѯ�ؼ���
    int kind;// ��ѯ����
    int id;// ��ѯ��ʾ��Ϊ�����ѯ�б���±�
    Query(int keyword_, int kind_, int id_) {
      keyword = keyword_;
      kind = kind_;
      id = id_;
    }
};


// kindSizeΪ������M, kindsTree�Ƿ�������ι�ϵ������ÿ������kind��kindsTree[kind]�洢�������ӷ��࣬sqls��queries��Ӧ��SQL����б�Ͳ�ѯ�б�
vector<double> BatchQueryExecutionTime(int kindSize, const vector<vector<int>>&kindsTree, const vector<SQL>& sqls, const vector<Query>&queries) {
  typedef multimap<string, double> WordTime;
  WordTime *kinds_map = new WordTime[kindSize];
  vector<vector<string>> kind_sqls(kindSize);
  vector<vector<double>> kind_times(kindSize);

  //���������ӷ����sql��time
  for (int i = 0; i < sqls.size(); ++i) {
    kind_sqls[sqls[i].kind].push_back(sqls[i].text);
    kind_times[sqls[i].kind].push_back(sqls[i].time);
  }

  //���������ӷ����map
  for (int i = 0; i < kindSize; ++i) {
    BuildSQLTimeMap(kind_sqls[i], kind_times[i], kinds_map[i]);
  }

  vector<double> results;

  //ִ�в�ѯ
  for (int i = 0; i < queries.size(); ++i) {
    vector<int>  childKinds = kindsTree[queries[i].kind];
    int sum = 0;
    int count = 0;
    //���������ӷ����map
    for (int j = 0; j < kindsTree[queries[i].kind].size(); ++j) {
      auto range = kinds_map[kindsTree[queries[i].kind][j]].equal_range(queries[i].keyword);
      //���㵥�ʶ�Ӧ������ʱ�䣬ͬһ������е��ظ������Ѿ��޳�
      for (auto j = range.first; j != range.second; ++j) {
        sum += j->second;
        count++;
      }
    }

    results.push_back((sum/count));
  }

  delete[] kinds_map;
  return results;
}



int main()
{
  //����case��û��ʱ��д���ı�����case
  vector<string> sqls;
  sqls.push_back("insert into tableA values (1, \"columnA\", \"columnB\")");
  sqls.push_back("insert into tableB values (2, \"columnA\", \"columnB\", \"columnC\")");
  sqls.push_back("select columnA, columnC from tableB");

  double a[] = {2.5,12.5,30.0};
  vector<double> times(a, a+sizeof(a)/sizeof(double));

  vector<string> keywords;
  keywords.push_back("tableB");
  keywords.push_back("insert");
  keywords.push_back("select");
  keywords.push_back("tableA");

  vector<double> results = BatchQueryExecutionTime(sqls, times, keywords);

  //��ӡ���������λС��
  for (int i = 0; i < results.size(); ++i) {
    printf("%.2lf\n", results[i]);
  }

  int kindSize = 5;
  int a0[] = {0,1,2,3,4,5};
  int a1[] = {1,4,5};
  int a2[] = {2};
  int a3[] = {3};
  int a4[] = {4};
  int a5[] = {5};

  vector<int> va0(a0,a0+sizeof(a0)/sizeof(int));
  vector<int> va1(a1,a1+sizeof(a1)/sizeof(int));
  vector<int> va2(a2,a2+sizeof(a2)/sizeof(int));
  vector<int> va3(a3,a3+sizeof(a3)/sizeof(int));
  vector<int> va4(a4,a4+sizeof(a4)/sizeof(int));
  vector<int> va5(a5,a5+sizeof(a5)/sizeof(int));

  vector<vector<int>> kindsTree;
  kindsTree.push_back(va0);
  kindsTree.push_back(va1);
  kindsTree.push_back(va2);
  kindsTree.push_back(va3);
  kindsTree.push_back(va4);
  kindsTree.push_back(va5);
  

  system("pause");

	return 0;
}

