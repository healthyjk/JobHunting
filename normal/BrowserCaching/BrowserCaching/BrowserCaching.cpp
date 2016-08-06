// BrowserCaching.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <fstream>

using namespace std;

//int main()
//{
//	ifstream cin("input.txt");
//
//	int n, m;
//	map<string, int>  url_index;
//	list<string> urls;
//	while (cin >> n >> m) {
//		urls.clear();
//		url_index.clear();
//		for (int i = 0; i < n; ++i) {
//			string visit;
//			cin >> visit;
//			if (url_index.find(visit) == url_index.end()) {
//				if (urls.size() >= m) {
//					string temp = urls.back();
//					url_index.erase(url_index.find(temp));
//					urls.pop_back();
//				} 
//				urls.push_front(visit);
//				url_index.insert(make_pair(visit, 0));
//				cout << "Internet" << endl;
//			} else {
//				string temp = urls.front();
//				for (auto iter = urls.begin(); iter != urls.end(); ++iter) { 
//					if ((*iter) == visit) {
//						urls.erase(iter);
//						break;
//					}
//				}
//				urls.emplace_front(visit);
//				cout << "Cache" << endl;
//			}
//		}
//	}
//
//	return 0;
//}


int main()
{
	ifstream cin("input.txt");

	int n, m;
	map<string, bool>  url_index;
	list<string> urls;
	while (cin >> n >> m) {
		urls.clear();
		url_index.clear();
		for (int i = 0; i < n; ++i) {
			string visit;
			cin >> visit;
			auto iter_url = url_index.find(visit);
			if (iter_url == url_index.end() || !url_index[visit]) {
				if (urls.size() >= m) {
					string temp = urls.back();
					url_index[temp] = false;
					urls.pop_back();
				} 
				urls.push_front(visit);
				if (iter_url == url_index.end()) {
					url_index.insert(make_pair(visit, true));
				} else {
					url_index[visit] = true;
				}
				cout << "Internet" << endl;
			} else {
				string temp = urls.front();
				for (auto iter = urls.begin(); iter != urls.end(); ++iter) { 
					if ((*iter) == visit) {
						urls.erase(iter);
						break;
					}
				}
				url_index[temp] = false;
				urls.emplace_front(visit);
				cout << "Cache" << endl;
			}
		}
	}

	return 0;
}


