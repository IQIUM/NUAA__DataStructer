/***
 * @Author         : IQIUM
 * @Date           : 2020-12-09 21:11:40
 * @LastEditors    : IQIUM
 * @LastEditTime   : 2020-12-09 21:12:22
 * @FilePath       : \Mine\GA-TSP.cpp
 */
#include <bits/stdc++.h>

class Individual;

using namespace std;
const int INF = 10000;
const int MAX = 100;            /* �������Ľڵ��� */
int speciesCapcity = 20;        /* ��Ⱥ���� */
int start = 0;                  /* ��ʼ����A�㿪ʼ */
double PC = 0.9;                /* ���轻�����Ϊ0.75 */
double PM = 0.1;                /* �������ĸ���Ϊ0.1 */
const int maxGenerations = 100; /* �������Ľ�������Ϊ1000 */
int cur_generation = 1;         /* ��ǰ�Ĵ��� */
int max_generation = 10000;     /* ���Ĵ���Ϊ10000 */
bool isFound = false;

vector<Individual> pop; /* ��Ⱥ */
vector<int> villages;   /* ���ӾͲ��������� */

int testcount = 0;

class Graph
{
public:
    char vertexs[MAX];
    int arcs[MAX][MAX];
    int vertexNum;
    int arcNum;
    Graph() : vertexNum(0), arcNum(0)
    {
        for (int i = 0; i < MAX; i++)
        {
            for (int j = 0; j < MAX; j++)
            {
                arcs[i][j] = INF;
            }
        }
    }
};

/* ���� */
class Individual
{
public:
    vector<int> path;
    int weight;
    double fitness;   /* ��Ӧ�� */
    double p_fitness; /* ��Ӧ�ȸ���(��ѡ��ĸ���) */
    int gen;          /* ���� */
};

Graph *graph = new Graph();

/* ͼ�Ĺ�����ʼ�� */
void createGraph()
{
    ifstream in("data.txt", ios::in);
    if (in.fail())
    {
        cout << "�ļ���ʧ�ܣ�" << endl;
        exit(0);
    }
    /* ��ȡ��һ�����нڵ����Ϣ */
    string line;
    getline(in, line, '\n');
    string buffer;
    stringstream ss(line);
    int count = 0;
    while (getline(ss, buffer, ' '))
    {
        graph->vertexs[count] = buffer[0];
        count++;
    }
    graph->vertexNum = count;
    ss.clear();

    while (!in.eof())
    {
        getline(in, line, '\n');
        ss.str(line);
        int x = line[0] - '0';
        int y = line[2] - '0';
        int count = 0;
        while (getline(ss, buffer, ' '))
        {
        }
        int weight = atoi(buffer.c_str());
        graph->arcs[x][y] = weight;
        graph->arcs[y][x] = weight;
        ss.clear();
    }

    in.close();
}

/* �����Ż� */
bool myCompare(Individual &indi1, Individual &indi2)
{
    return indi1.fitness < indi2.fitness;
}

/* ����ÿһ��Ⱦɫ���Ȩֵ */
int sum(Individual &indi)
{
    int sum = 0;
    for (int i = 0; i < indi.path.size() - 1; i++)
    {
        sum += graph->arcs[indi.path[i]][indi.path[i + 1]];
    }
    return sum;
}

int getNearest(int top, map<int, bool> &isVisited)
{
    int min = INT_MAX;
    int min_index = -1;
    for (int i = 0; i < villages.size(); i++)
    {

        if (isVisited[villages[i] == 0])
        {
            if (graph->arcs[top][villages[i]] < min)
            {
                min = graph->arcs[top][villages[i]];
                min_index = villages[i];
            }
        }
    }
    return min_index;
}

/***
 * @description:��ʼ����Ⱥ,gen ����ڼ���
 */
void initPop(int gen)
{
    for (int i = 0; i < speciesCapcity; i++)
    {
        Individual tmp;
        /* ������� */
        tmp.path.push_back(start);
        random_shuffle(villages.begin(), villages.end());
        for (int i = 0; i < villages.size(); i++)
        {
            tmp.path.push_back(villages[i]);
        }
        tmp.path.push_back(start); /* ������͹�����һ������ */
        tmp.weight = sum(tmp);
        tmp.fitness = 1 / (float)tmp.weight;
        tmp.gen = gen;
        pop.push_back(tmp);
    }

    if (gen == 1)
    { /* ̰�ĳ�ʼ����һ�� */

        Individual indi;
        map<int, bool> isVisited;
        indi.path.push_back(start);
        isVisited[start] = true; /* ������ */

        for (int i = 0; i < villages.size(); i++)
        {                               /* ����ջ�д��� */
            int top = indi.path.back(); /* ջ��Ԫ�� */
            int min = INT_MAX;
            int min_index = -1;
            for (int j = 0; j < villages.size(); j++)
            {
                bool flag = false;
                for (map<int, bool>::iterator it = isVisited.begin();
                     it != isVisited.end(); ++it)
                {
                    if (it->first == villages[j])
                    {
                        flag = true;
                        break;
                    }
                }
                if (!flag)
                { /* ���û��˵��û����� */
                    if (graph->arcs[villages[j]][top] < min)
                    {
                        min = graph->arcs[villages[j]][top];
                        min_index = villages[j];
                    }
                }
            }
            indi.path.push_back(min_index);
            isVisited[min_index] = true;
        }
        indi.path.push_back(start);
        indi.weight = sum(indi);
        indi.fitness = 1 / (float)indi.weight;
        indi.gen = gen;
        pop[0] = indi;
    }
}

Individual CrossOver(Individual &first, Individual &second,
                     vector<Individual> &nextG)
{
    int length = (int)((rand() % 100 / 100.0) * villages.size());
    Individual child1, child2;
    for (int i = 0; i < length; i++)
    {
        child1.path.push_back(first.path[i]);
    }
    for (int i = 0; i < second.path.size(); i++)
    {
        bool flag = false;
        for (int j = 0; j < child1.path.size(); j++)
        {
            if (second.path[i] == child1.path[j])
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            child1.path.push_back(second.path[i]);
        }
    }

    /* �����ڶ������� */
    for (int i = 0; i < first.path.size(); i++)
    {
        bool flag = false;
        for (int j = 0; j < length; j++)
        {
            if (first.path[i] == first.path[j])
            {
                flag = true;
                break;
            }
        }
        if (flag)
        {
            child2.path.push_back(first.path[i]);
        }
    }
    for (int i = 0; i < second.path.size(); i++)
    {
        bool flag = false;
        for (int j = 0; j < child2.path.size(); j++)
        {
            if (second.path[i] == child2.path[j])
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            child2.path.push_back(second.path[i]);
        }
    }

    child1.weight = sum(child1);
    child2.weight = sum(child2);
    child1.gen = first.gen++;
    child2.gen = second.gen++;

    nextG.push_back(child1);
    nextG.push_back(child2);
}

/* �������ӣ�˳����λ */
void mutation(Individual &cur)
{

    int bef = rand() % cur.path.size();
    int aft = rand() % cur.path.size();
    int &a = cur.path[bef];
    int &b = cur.path[aft];
    a = a ^ b;
    b = b ^ a;
    a = a ^ b;
}

/* ��ʼ���� */
vector<Individual> Evolution()
{

    vector<Individual> nextGeneration;       /* ÿ����һ������������һ�� */
    sort(pop.begin(), pop.end(), myCompare); /* �����ҳ����ŵĸ��� */

    /* ���Ž���ǰ�ҵ� */
    if (pop[0].weight == 36)
    {
        isFound = true;
    }
    /* �����Ž�ŵ���һ�� */
    nextGeneration.push_back(pop[0]);
    nextGeneration[0].gen++;

    for (int i = 0; i < pop.size(); i++)
    {
        if (i == 0)
        {
            pop[i].p_fitness = pop[i].fitness;
        }
        else
        {
            pop[i].p_fitness = pop[i].fitness + pop[i - 1].fitness;
        }
    }

    double total = 0;
    for (int i = 0; i < pop.size(); i++)
    {
        total += pop[i].p_fitness;
    }
    for (vector<Individual>::iterator it = pop.begin(); it != pop.end() - 1;
         ++it)
    {

        double first_selected = rand() % 10000 / 10000.0;
        if (first_selected < PC)
        {
            double second_selected = rand() % 10000 / 10000.0 * total;
            for (vector<Individual>::iterator it2 = pop.begin();
                 it2 != pop.end() - 1; ++it2)
            {
                if (it2 == pop.begin())
                {
                    if (second_selected < it2->p_fitness)
                    {
                        CrossOver(*it, *it2, nextGeneration); /* ���� */
                        break;
                    }
                }
            }
        }
        else
        {
            it->gen++;
            nextGeneration.push_back(*it);
        }
        if (rand() % 10000 / 10000.0 < PM)
        { /* ���� */
            mutation(*it);
            nextGeneration.push_back(*it);
        }
    }

    return nextGeneration;
}

int main()
{
    createGraph();
    for (int j = 0; j < graph->vertexNum; j++)
    {
        if (j != start)
        {
            villages.push_back(j);
        }
    }
    initPop(1);

    int sumWeight = 0;
    for (int i = 0; i < pop.size(); i++)
    {
        pop[i].weight = sum(pop[i]);
        sumWeight += pop[i].weight;
    }
    for (int i = 0; i < pop.size(); i++)
    {
        pop[i].fitness = pop[i].weight / (float)sumWeight;
    }

    while (!isFound && cur_generation <= maxGenerations)
    {
        pop = Evolution();
        cur_generation++;
    }

    cout << "\n�Ŵ��㷨ģ������Ž��Ϊ�� ";
    for (int i = 0; i < pop[0].path.size(); i++)
    {
        cout << graph->vertexs[pop[0].path[i]] << "  ";
    }
    cout << ",  ��ȨֵΪ��  " << pop[0].weight << endl
         << endl;
    system("pause");
    return 0;
}