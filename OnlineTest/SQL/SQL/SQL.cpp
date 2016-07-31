// SQL.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

//函数功能：基于给定的字符来分割字符串
//输入：待分割字符串s, 分割标识符delim
//输出：string vector ret,引用形式传入
//返回值：无
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

//函数功能：简历SQL中单词与SQL语句执行时间的map，使用multimap， 允许重复key；
//输入：查询语句数组sqls, 查询语句对应执行时间times
//输出：查询语句中单词对应的执行时间映射word_to_time,引用形式传入
//返回值：无
void BuildSQLTimeMap(const vector<string>& sqls, const vector<double>& times, multimap<string, double>& word_to_time) {
  int sn = sqls.size();
  vector<string> split_results;
  for (int i = 0; i < sn; ++i) {
    split(sqls[i], blank, split_results);
    //考虑同一个语句中的重复单词不重复计算，因此去除重复元素
    split_results.erase(unique(split_results.begin(),split_results.end()), split_results.end());
    int count = split_results.size();
    for (int j = 0; j < count; ++j) {
      word_to_time.insert(make_pair(split_results[j], times[i]));
    }
    split_results.clear();
  }
}

//sqls是SQL语句列表，times是对应的执行时间，keywords是每次查询的关键词。
//返回每个关键词对应查询结果SQL集合中SQL执行时间的平均值。
vector<double> BatchQueryExecutionTime(const vector<string>& sqls, const vector<double>& times, const vector<string>& keywords) {
  multimap<string, double> word_to_time;
  //建立multimap
  BuildSQLTimeMap(sqls, times, word_to_time);

  vector<double> results;

  for (int i = 0; i < keywords.size(); ++i) {
    //逐条查询单词，得到迭代器范围
    auto range = word_to_time.equal_range(keywords[i]);
    double sum = 0;
    int count = 0;
    //计算单词对应的所有时间，同一个语句中的重复单词已经剔除
    for (auto j = range.first; j != range.second; ++j) {
      sum += j->second;
      count++;
    }
    results.push_back((sum / count));
  }

  return results;
}




struct SQL {
    string text; //SQL语句
    int kind;//所属分类
    double time;//执行时间
    SQL(int text_, int kind_, int time_) {
      text = text_;
      kind = kind_;
      time = time_;
    }
};
 
struct Query {
    string keyword;// 查询关键词
    int kind;// 查询分类
    int id;// 查询标示，为传入查询列表的下标
    Query(int keyword_, int kind_, int id_) {
      keyword = keyword_;
      kind = kind_;
      id = id_;
    }
};


// kindSize为分类数M, kindsTree是分类的树形关系，对于每个分类kind，kindsTree[kind]存储其所有子分类，sqls和queries对应着SQL语句列表和查询列表。
vector<double> BatchQueryExecutionTime(int kindSize, const vector<vector<int>>&kindsTree, const vector<SQL>& sqls, const vector<Query>&queries) {
  typedef multimap<string, double> WordTime;
  WordTime *kinds_map = new WordTime[kindSize];
  vector<vector<string>> kind_sqls(kindSize);
  vector<vector<double>> kind_times(kindSize);

  //建立各个子分类的sql和time
  for (int i = 0; i < sqls.size(); ++i) {
    kind_sqls[sqls[i].kind].push_back(sqls[i].text);
    kind_times[sqls[i].kind].push_back(sqls[i].time);
  }

  //建立各个子分类的map
  for (int i = 0; i < kindSize; ++i) {
    BuildSQLTimeMap(kind_sqls[i], kind_times[i], kinds_map[i]);
  }

  vector<double> results;

  //执行查询
  for (int i = 0; i < queries.size(); ++i) {
    vector<int>  childKinds = kindsTree[queries[i].kind];
    int sum = 0;
    int count = 0;
    //遍历所有子分类的map
    for (int j = 0; j < kindsTree[queries[i].kind].size(); ++j) {
      auto range = kinds_map[kindsTree[queries[i].kind][j]].equal_range(queries[i].keyword);
      //计算单词对应的所有时间，同一个语句中的重复单词已经剔除
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
  //测试case，没有时间写从文本读入case
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

  //打印结果保留两位小数
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

