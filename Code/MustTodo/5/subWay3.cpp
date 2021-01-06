/***
 * @Author         : IQIUM
 * @Date           : 2020-12-12 21:01:52
 * @LastEditors    : IQIUM
 * @LastEditTime   : 2020-12-12 21:02:43
 * @FilePath       : \MustTodo\5\subWay3.cpp
 */
#include <bits/stdc++.h>
using namespace std;

const int MAX = 100002;
int n = 0;
int m = 0;

// ±ﬂ¿‡
class Edge
{
public:
    int start;
    int end;
    int weight;
    Edge(int start, int end, int weight)
        : start(start), end(end), weight(weight) {}
};
bool myCompare(Edge &e1, Edge &e2) { return e1.weight < e2.weight; }

vector<Edge> edges;
int path[MAX];

int findS(int i) { return i == path[i] ? i : findS(path[i]); }
int findX(int x)
{
    int p = x;
    while (p != path[p])
    {
        p = path[p];
    }
    while (p != x)
    {
        int tmp = path[x];
        path[x] = p;
        x = tmp;
    }
    return x;
}

int Solution()
{
    for (int i = 0; i < m; i++)
    {
        Edge tmp = edges[i];
        int end_head = findX(tmp.end);
        int start_head = findX(tmp.start);
        path[end_head] = start_head;
        if (findX(1) == findX(n))
        {
            return tmp.weight;
        }
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int start = 0, end = 0, weight = 0;
        cin >> start >> end >> weight;
        edges.push_back(Edge(start, end, weight));
    }
    sort(edges.begin(), edges.end(), myCompare);
    for (int i = 1; i <= n; i++)
    {
        path[i] = i;
    }

    cout << Solution();
    return 0;
}