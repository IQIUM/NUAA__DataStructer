#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000; //最大节点数
const int INF = 1000000;

/* 定义一个辅助素组closest来记录中间位置 */
class Close
{
public:
    int lowcost;
    int vexcode;
};

//图 类
class Graph
{
public:
    int vertex_num; //节点的个数
    int arc_num;    //边数
    float matrix[MAX][MAX];
    char vertex[MAX]; //节点符号
    Graph()
    {
        vertex_num = 0;
        arc_num = 0;
        for (int i = 0; i < MAX; i++)
        {
            for (int j = 0; j < MAX; j++)
            {
                matrix[i][j] = INF;
            }
        }
    }
};

Graph *graph = new Graph();

/* 定义边 */
class Edge
{
public:
    Edge() {}
    Edge(int u, int v, float weight) : u(u), v(v), weight(weight) {}
    int u;
    int v;
    float weight;
};

ostream &operator<<(ostream &cout, Edge &edge)
{
    cout << "起始点： " << graph->vertex[edge.u] << "--  "
         << "权值：" << edge.weight << "  ---"
         << "终止点 " << graph->vertex[edge.v] << endl;
    return cout;
}

vector<Edge> edges;

void readGraphFromFile()
{
    const string filename = "graph.txt";
    ifstream in(filename, ios::in);
    if (in.fail())
    {
        cout << "[Error] graph.txt 文件打开失败！" << endl;
        exit(0);
    }
    string line;
    getline(in, line, '\n');

    graph->vertex_num = line[0] - '0';
    int count = 0;
    for (int i = 2; i < line.length(); i += 2)
    {
        graph->vertex[count++] = line[i];
    }
    while (!in.eof())
    {
        line = "";
        getline(in, line, '\n');
        graph->arc_num++;
        int x = line[0] - '0';
        int y = line[2] - '0';
        float weight = atof(line.substr(4, line.size() - 4).c_str());
        graph->matrix[x][y] = weight;
        graph->matrix[y][x] = weight;
        edges.push_back(Edge(x, y, weight));
    }
    in.close();
}

void show(vector<Edge> &tree)
{
    float sum = 0;
    for (int i = 0; i < tree.size(); i++)
    {
        cout << tree[i];
        sum += tree[i].weight;
    }
    cout << "\n\t总权值为：  " << sum << endl;
}

/**
 * cur: 随机访问的第一个顶点
 **/
void Prime(int cur)
{
    vector<Edge> edges;
    Close closest[graph->vertex_num];
    /* 初始化中间结果 */
    for (int i = 0; i < graph->vertex_num; ++i)
    {
        closest[i].vexcode = 0;
        closest[i].lowcost = graph->matrix[0][i];
    }
    /* 正式开始Prime算法 */
    closest[cur].lowcost = 0;
    int count = 1;
    while (count < graph->vertex_num)
    {
        int minWeight = INF;
        int minIndex = -1;

        for (int i = 0; i < graph->vertex_num; ++i)
        {
            if (closest[i].lowcost < minWeight && closest[i].lowcost != 0)
            {
                minWeight = closest[i].lowcost;
                minIndex = i;
            }
        }

        closest[minIndex].lowcost = 0;
        ++count;
        /* 更行closest数组 */
        for (int i = 0; i < graph->vertex_num; ++i)
        {
            if (graph->matrix[minIndex][i] != INF &&
                graph->matrix[minIndex][i] < closest[i].lowcost)
            {
                closest[i].lowcost = graph->matrix[minIndex][i];
                closest[i].vexcode = minIndex;
            }
        }
        edges.push_back(
            Edge(closest[minIndex].vexcode, minIndex,
                 graph->matrix[minIndex][closest[minIndex].vexcode]));
    }
    show(edges);
}

bool myCompare(Edge &e1, Edge &e2) { return e1.weight < e2.weight; }

int findS(int path[], int x)
{
    if (x == path[x])
    {
        return x;
    }
    return findS(path, path[x]);
}

void Kruskal()
{
    vector<Edge> res;
    sort(edges.begin(), edges.end(), myCompare);
    int *path = new int[graph->vertex_num];
    for (int i = 0; i < graph->vertex_num; i++)
    {
        path[i] = i;
    }
    for (int i = 0; i < edges.size(); i++)
    {
        int x = edges[i].u;
        int y = edges[i].v;
        if (findS(path, x) != findS(path, y))
        {
            path[findS(path, x)] = y;
            res.push_back(edges[i]);
        }
    }
    show(res);
    delete[] path;
}

int main()
{
    readGraphFromFile();
    cout << "\n使用Prime算法找到的最小生成树的边为：  \n";
    Prime(0);

    cout << "\n\n-------------------------------------------\n\n";
    cout << "使用Kruskal算法找到的最小生成树的边为：  \n";

    Kruskal();
    cout << "\n";
    delete graph;
    return 0;
}