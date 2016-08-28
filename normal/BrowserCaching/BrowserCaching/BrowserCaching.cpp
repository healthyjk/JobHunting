//// BrowserCaching.cpp : �������̨Ӧ�ó������ڵ㡣
////
//
#include "stdafx.h"
//
//#include <iostream>
//#include <vector>
//#include <list>
//#include <string>
//#include <map>
//#include <fstream>
//
//using namespace std;
//
////int main()
////{
////	ifstream cin("input.txt");
////
////	int n, m;
////	map<string, int>  url_index;
////	list<string> urls;
////	while (cin >> n >> m) {
////		urls.clear();
////		url_index.clear();
////		for (int i = 0; i < n; ++i) {
////			string visit;
////			cin >> visit;
////			if (url_index.find(visit) == url_index.end()) {
////				if (urls.size() >= m) {
////					string temp = urls.back();
////					url_index.erase(url_index.find(temp));
////					urls.pop_back();
////				} 
////				urls.push_front(visit);
////				url_index.insert(make_pair(visit, 0));
////				cout << "Internet" << endl;
////			} else {
////				string temp = urls.front();
////				for (auto iter = urls.begin(); iter != urls.end(); ++iter) { 
////					if ((*iter) == visit) {
////						urls.erase(iter);
////						break;
////					}
////				}
////				urls.emplace_front(visit);
////				cout << "Cache" << endl;
////			}
////		}
////	}
////
////	return 0;
////}
//
//
////int main()
////{
////	ifstream cin("input.txt");
////
////	int n, m;
////	map<string, bool>  url_index;
////  map<string, list<string>::iterator>  url_pstr;
////	list<string> urls;
////	while (cin >> n >> m) {
////		urls.clear();
////		url_index.clear();
////    url_pstr.clear();
////		for (int i = 0; i < n; ++i) {
////			string visit;
////			cin >> visit;
////			auto iter_url = url_index.find(visit);
////			if (iter_url == url_index.end() || !url_index[visit]) {
////				if (urls.size() >= m) {
////					string temp = urls.back();
////					url_index[temp] = false;
////					urls.pop_back();
////				} 
////        if (iter_url == url_index.end()) {
////					url_index.insert(make_pair(visit, true));
////				} else {
////					url_index[visit] = true;
////				}
////				urls.push_front(visit);
////        url_pstr.insert(make_pair(visit, urls.begin()));
////				
////				cout << "Internet" << endl;
////			} else {
////        
////        urls.erase(url_pstr[visit]);
////				/*for (auto iter = urls.begin(); iter != urls.end(); ++iter) { 
////					if ((*iter) == visit) {
////						urls.erase(iter);
////						break;
////					}
////				}*/
////				urls.emplace_front(visit);
////        url_pstr.insert(make_pair(visit, urls.begin()));
////				cout << "Cache" << endl;
////			}
////		}
////	}
////
////	return 0;
////}
//
//
////�ǳ���Ľⷨ������ʹ�ô������洢cache����ֻ��ʹ���±���ƶ���������ı仯
//const int N = 20005;  
//int n, m;  
//map<string, int> lastVisit;  
//string a[N];  
//
//int main()  
//{  
//	ifstream cin("input.txt");
//	cin >> n >> m;
//	int cacheCnt = 0;  
//	int start = 1;  
//
//	for(int i = 1; i <= n ; i ++)  
//	{  
//		cin >> a[i];  
//		if(lastVisit[a[i]] >= start && lastVisit[a[i]] <= i) {
//			printf("Cache\n");  
//		} else {  
//			printf("Internet\n");  
//			cacheCnt ++;  
//			// ��������  
//			if(cacheCnt > m) {  
//				start = start + 1;  
//			}  
//		}  
//		//�������һ�η���ʱ��  
//		lastVisit[a[i]] = i;  
//		//����start�ҵ����µ�����ķ��ʼ�¼  
//		while(lastVisit[a[start]] != start) {  
//			start = start + 1;  
//		}
//	}  
//
//	return 0;  
//}
//
