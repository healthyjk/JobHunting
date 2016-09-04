#ifndef __GRAPH_HPP_
#define __GRAPH_HPP_

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define WHITE 1
#define BLACK 0
#define GRAY 2

using namespace std;

void topoSort(vector<int> degree, const vector<vector<int> >& edges, vector<int>& toposort);

struct Edge {
    int start;
    int end;
    int value;
    Edge* next;
    Edge(int s, int e, int v) : start(s), end(e), value(v), next(NULL) {}
};

class Vertex {
public:
    int color;
    int d;
    int f; /*用于拓扑排序*/
    Edge* head;
    Vertex() : head(NULL), color(WHITE), d(INT_MAX){}
    ~Vertex() {
        Edge* p = head;
        while (NULL != head) {
            p = head;
            head = head->next;
            delete p;
        }
    }
};

class LinkGraph {
public:
    int vNum;
    Vertex* V;

    LinkGraph(int num) {
        V = new Vertex[num];
        vNum = num;
    }

    ~LinkGraph() {
        delete[] V;
    }

    void AddSingleEdge(int start, int end, int value = 1)
    {
        Edge *NewEdge = new Edge(start, end, value);
        if(V[start].head == NULL || V[start].head->end > end)
        {
            NewEdge->next = V[start].head;
            V[start].head = NewEdge;
        }
        else
        {
            Edge *e = V[start].head, *pre = e;
            while(e != NULL && e->end < end)
            {
                pre = e;
                e = e->next;
            }
            if(NULL != e && e->end == end)
            {
                delete NewEdge;
                return;
            }
            NewEdge->next = e;
            pre->next = NewEdge;
        }
    }


    void AddDoubleEdge(int a, int b, int value = 1)
    {
        AddSingleEdge(a, b, value);
        AddSingleEdge(b, a, value);
    }


    void DeleteSingleEdge(int start, int end)
    {
        Edge *e = V[start].head, *pre = e;
        while(e && e->end < end)
        {
            pre = e;
            e = e->next;
        }
        if(e == NULL || e->end > end) return;
        if(e == V[start].head)
            V[start].head = e->next;
        else
            pre->next = e->next;
        delete e;
    }


    void DeleteDoubleEdge(int a, int b)
    {
        DeleteSingleEdge(a, b);
        DeleteSingleEdge(b, a);
    }

    void DFS();
    void BFS(int start);
    void TopologySort();
    void TopologySort_2();

private:
    void DFSVisit(int u, int& time);
};


void LinkGraph::DFS() {
    for (int i = 0; i < vNum; ++i) {
        V[i].color = WHITE;
        V[i].d = 0;
        V[i].f = 0;
    }
    int time = 0;

    cout << "DFS Result:" ;
    for (int i = 0; i < vNum; ++i) {
        if (WHITE == V[i].color) {
            DFSVisit(i, time);
        }
    }
    cout << endl;
}

void LinkGraph::DFSVisit(int u, int& time) {
    time++;
    V[u].d = time;
    V[u].color = GRAY;
    cout << (u+1) << "\t";

    Edge* head = V[u].head;
    while (NULL != head) {
        if (WHITE == V[head->end].color) {
            DFSVisit(head->end, time);
        }
        head = head->next;
    }
    V[u].color = BLACK;
    time++;
    V[u].f = time;
}

void LinkGraph::BFS(int start) {
    if (start < 0 || start > vNum) {
        return;
    }
    for (int i = 0; i < vNum; ++i) {
        V[i].color = WHITE;
        V[i].d = INT_MAX;
    }

    cout << "BFS Result:" ;

    queue<int> q;
    q.push(start);
    V[start].d = 0;
    V[start].color = BLACK;

    while (!q.empty()) {
        int top = q.front();
        q.pop();
        cout << (top+1) << "\t";
        Edge* head = V[top].head;
        while (NULL != head) {
            if (V[head->end].color == WHITE) {
                q.push(head->end);
                V[head->end].d = V[top].d + 1;
                V[head->end].color = BLACK;
            }
            head = head->next;
        }
    }
    cout << std::endl;
}

bool CompFunc(const pair<int, Vertex*> v1, const pair<int, Vertex*> v2) {
    return v1.second->f > v2.second->f;
}

/**
拓扑排序函数：利用DFS来实现，理论上只需要在DFS中每个顶点遍历完成后添加到
**/
void LinkGraph::TopologySort() {
    DFS();
    vector<pair<int, Vertex*>> all;
    for (int i = 0; i < vNum; ++i) {
        all.push_back(make_pair(i, &V[i]));
    }
    sort(all.begin(), all.end(), CompFunc);
    cout << "TopologySort Result:";
    for (int i = 0; i < vNum; ++i) {
        cout << all[i].first << "\t";
    }
    cout << endl;
}


void LinkGraph::TopologySort_2() {
    vector<int> degree(vNum, 0);
    vector<vector<int> > edges(vNum);
    for (int i = 0; i < vNum; ++i) {
        Edge* head = V[i].head;
        while(NULL != head) {
            degree[head->end]++;
            edges[i].push_back(head->end);
            head = head->next;
        }
    }
    vector<int> result;
    topoSort(degree, edges, result);

    cout << "TopologySort Result:";
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << "\t";
    }
    cout << endl;
}

/**
拓扑排序函数：输入顶点入度，边连接二维数组，排序结果
**/
void topoSort(vector<int> degree, const vector<vector<int> >& edges, vector<int>& toposort) {

    int n = degree.size();
    vector<int> result;
    queue<int> Q;
    //定点入度为0进队列
    for (int i = 0; i < n; ++i) {
        if (degree[i] == 0) {
            Q.push(i);
        }
    }
    int count = 0;
    while (!Q.empty()) {
        int v = Q.front();
        toposort.push_back(v);
        Q.pop();
        count++;
        for (int i = 0; i < edges[v].size(); ++i) {
            if ((--degree[edges[v][i]]) == 0) { //相邻顶点入度减一，若为0，加入队列
                Q.push(edges[v][i]);
            }
        }
    }
}

#endif // GRAPH_HPP
