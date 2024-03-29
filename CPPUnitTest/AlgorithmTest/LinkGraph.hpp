#ifndef __GRAPH_HPP_
#define __GRAPH_HPP_

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <stack>

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
    vector<int> degree;

    LinkGraph(int num) {
        V = new Vertex[num];
        vNum = num;
        degree.resize(num, 0);
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
        degree[end]++;
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
    void TopologySort();  /*使用DFS实现的拓扑排序*/
    void TopologySort_2(); /*使用入度为0算法实现的拓扑排序*/

private:
    void DFSVisit(int u, int& time);
};

/*DFS算法遍历*/
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

/*BFS算法遍历*/
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

/**
拓扑排序函数：利用顶点入度为0来计算
**/
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

/* 用于计算AOE网络关键路径的 拓扑排序，若GL无回路，则输出拓扑排序序列并返回1，若有回路返回0。 */
bool TopologicalSort(LinkGraph& graph, vector<int>& etv, stack<int>& s2)
{
    int count = 0;/* 用于统计输出顶点的个数 */
    stack<int> s1;
    /*添加入度为0的点*/
    for (int i = 0; i < graph.vNum; i++) {
        if (0 == graph.degree[i]){
            s1.push(i);
        }
    }

    cout << "TopologicalSort ..." << endl;
    while (!s1.empty())
    {
        int top = s1.top();
        s1.pop();
        cout << (top+1) << " -> ";
        count++; /* 输出i号顶点，并计数 */

        s2.push(top);

        for (Edge* pe = graph.V[top].head; NULL != pe; pe = pe->next)
        {
            int k = pe->end;
            /* 将i号顶点的邻接点的入度减1，如果减1后为0，则入栈 */
            if (0 == (--graph.degree[k])) {
                s1.push(k);
            }
            /* 求各顶点事件的最早发生时间etv值 */
            if ((etv[top] + pe->value) > etv[k]) {
                etv[k] = etv[top] + pe->value;
            }
        }
    }
    cout << endl;
    if (count < graph.vNum)
        return false;
    else
        return true;
}

/* 求关键路径,GL为有向网，输出G的各项关键活动 */
void CriticalPath(LinkGraph& graph)
{
    int ete, lte;/* 声明活动最早发生时间和最迟发生时间变量 */
    vector<int> etv(graph.vNum, 0); /* 事件最早(Earlist)发生时间数组 */
    vector<int> ltv(graph.vNum, 0); /* 事件最晚(Latest)发生时间数组 */
    stack<int> s2;

    TopologicalSort(graph, etv, s2);/* 求拓扑序列，计算数组etv和stack2的值 */

    cout << "etv : ";
    for (int i = 0; i < graph.vNum; i++) {
        cout << etv[i] << ' ';
    }
    cout << endl;

    for (int i = 0; i < graph.vNum; i++) {
        ltv[i] = etv[graph.vNum - 1];
    } /* 初始化 */

    while (!s2.empty())/* 出栈是求ltv */
    {
        int top = s2.top();
        s2.pop();

        /* 求各顶点事件的最迟发生时间ltv值 */
        for (Edge* pe = graph.V[top].head; NULL != pe; pe = pe->next)
        {
            int k = pe->end;
            if (ltv[k] - pe->value < ltv[top])
                ltv[top] = ltv[k] - pe->value;
        }
    }

    cout << "ltv : ";
    for (int i = 0; i < graph.vNum; i++) {
        cout << ltv[i] << ' ';
    }
    cout << endl;

    /* 求ete,lte和关键活动 */
    for (int j = 0; j < graph.vNum; j++)
    {
        for (Edge* pe = graph.V[j].head; NULL != pe; pe = pe->next)
        {
            int k = pe->end;
            ete = etv[j];/* 活动最早发生时间 */
            lte = ltv[k] - pe->value;/* 活动最迟发生时间 */
            if (ete == lte) { /* 两者相等即在关键路径上 */
                cout << "<v" << (j+1) << " - v"
                     << (k+1) << "> length: " << pe->value << endl;
            }
        }
    }
}

/**
 * Dijkstra算法:
**/
//vector<int>& dijkstra(LinkGraph& graph, int start) {
//    vector<int> dist(graph.vNum, INT_MAX);
//    if (start < 0 || start >= graph.vNum || dist.size() < graph.vNum) {
//        return;
//    }
//    queue<int> q;
//    q.push(start);
//    dist[start] = 0;

//    while (!q.empty()) {
//        int top = q.front();
//        q.pop();
//        int min = INT_MAX;
//        int next = -1;
//        for (Edge *head = graph.V[i].head; NULL != head; head = head->next) {
//            int k = head->end;
//            if (head->value + dist < dist[k]) {
//                dist[k] = head->value + dist;
//            }
//            if (dist[k] < min) {
//                next = k;
//                min = dist[k];
//            }
//        }
//        if (next == -1) {
//            break;
//        } else {
//            q.push(next);
//        }
//    }
//}

//void ShortestPath_DJS(unsigned int adjMat[][vexCounts],unsigned int s)
//{
//    vector<vertexdata> vexset; //已经找到最短路径的顶点集
//    vector<uint> dist(vexCounts); //没有被找的最短路径的顶点距离信息
//    vector<vector<vertexdata> > path(vexCounts); //每个顶点的最短路径信息
//    for (unsigned int i = 0; i < vexCounts; i++)
//    {
//        dist[i] = adjMat[s][i];  //初始化距离
//        if (dist[i] != INFINITE)//s是否有路径到达i
//        {
//            path[i].push_back(s);  //把保存最短路径
//            path[i].push_back(i);
//        }
//    }
//    vexset.push_back(s); //初始把顶点s加入vexset

//    for (unsigned int n = 1; n <= vexCounts-1; n++)
//    {
//        UINT min = INFINITE;
//        UINT k = INFINITE;
//        for (int i = 0; i < vexCounts;i++) //寻找下一条最短路径
//        {
//            if (find(vexset.rbegin(),vexset.rend(),i) == vexset.rend() && dist[i] < min)
//            {
//                k = i;
//                min = dist[i];
//            }
//        }
//        vexset.push_back(k); //把最短路径顶点加入vexset中
//        for (int i = 0; i < vexCounts;i++)  //更新dist
//        {
//            /*检测vexset中是否已经有顶点i,即i的最短路径是否已经找到。
//            如果没有找到，则判定是否需要更新最短路径*/
//            if (find(vexset.rbegin(), vexset.rend(), i) == vexset.rend()
//                && adjMat[k][i] != INFINITE && dist[k]+ adjMat[k][i] < dist[i])
//            {
//                dist[i] = dist[k] + adjMat[k][i];
//                path[i] = path[k];
//                path[i].push_back(i);
//            }
//        };
//        /*便于观察，输出每个顶点的最短路径经过的所有其他顶点及其距离*/
//        cout << "Path: ";
//        for (int i = 0; i < path[k].size();i++)
//        {
//            cout << vextex[path[k][i]] << ",";
//        }
//        cout << "     距离="<<dist[k]<<endl;
//    }
//}

#endif // GRAPH_HPP
