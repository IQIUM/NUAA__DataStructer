#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000; //���ڵ���
const int INF = 1000000;

/* ����һ����������closest����¼�м�λ�� */
class Close
{
public:
    int lowcost;
    int vexcode;
};

//ͼ ��
class Graph
{
public:
    int vertex_num; //�ڵ�ĸ���
    int arc_num;    //����
    float matrix[MAX][MAX];
    char vertex[MAX]; //�ڵ����
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

/* ����� */
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
    cout << "��ʼ�㣺 " << graph->vertex[edge.u] << "--  "
         << "Ȩֵ��" << edge.weight << "  ---"
         << "��ֹ�� " << graph->vertex[edge.v] << endl;
    return cout;
}

vector<Edge> edges;

void readGraphFromFile()
{
    const string filename = "graph.txt";
    ifstream in(filename, ios::in);
    if (in.fail())
    {
        cout << "[Error] graph.txt �ļ���ʧ�ܣ�" << endl;
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
    cout << "\n\t��ȨֵΪ��  " << sum << endl;
}

/**
 * cur: ������ʵĵ�һ������
 **/
void Prime(int cur)
{
    vector<Edge> edges;
    Close closest[graph->vertex_num];
    /* ��ʼ���м��� */
    for (int i = 0; i < graph->vertex_num; ++i)
    {
        closest[i].vexcode = 0;
        closest[i].lowcost = graph->matrix[0][i];
    }
    /* ��ʽ��ʼPrime�㷨 */
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
        /* ����closest���� */
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
    cout << "\nʹ��Prime�㷨�ҵ�����С�������ı�Ϊ��  \n";
    Prime(0);

    cout << "\n\n-------------------------------------------\n\n";
    cout << "ʹ��Kruskal�㷨�ҵ�����С�������ı�Ϊ��  \n";

    Kruskal();
    cout << "\n";
    delete graph;
    return 0;
}