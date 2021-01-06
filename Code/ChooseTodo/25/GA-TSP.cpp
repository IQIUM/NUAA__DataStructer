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
const int MAX = 100;            /* 定义最大的节点数 */
int speciesCapcity = 20;        /* 种群容量 */
int start = 0;                  /* 初始起点从A点开始 */
double PC = 0.9;                /* 假设交叉概率为0.75 */
double PM = 0.1;                /* 假设变异的概率为0.1 */
const int maxGenerations = 100; /* 假设最大的进化代数为1000 */
int cur_generation = 1;         /* 当前的代数 */
int max_generation = 10000;     /* 最大的代数为10000 */
bool isFound = false;

vector<Individual> pop; /* 总群 */
vector<int> villages;   /* 村子就采用数组标号 */

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

/* 个体 */
class Individual
{
public:
    vector<int> path;
    int weight;
    double fitness;   /* 适应度 */
    double p_fitness; /* 适应度概率(被选择的概率) */
    int gen;          /* 代数 */
};

Graph *graph = new Graph();

/* 图的构建初始化 */
void createGraph()
{
    ifstream in("data.txt", ios::in);
    if (in.fail())
    {
        cout << "文件打开失败！" << endl;
        exit(0);
    }
    /* 读取第一行所有节点的信息 */
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

/* 排序优化 */
bool myCompare(Individual &indi1, Individual &indi2)
{
    return indi1.fitness < indi2.fitness;
}

/* 计算每一条染色体的权值 */
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
 * @description:初始化种群,gen 代表第几代
 */
void initPop(int gen)
{
    for (int i = 0; i < speciesCapcity; i++)
    {
        Individual tmp;
        /* 随机排序 */
        tmp.path.push_back(start);
        random_shuffle(villages.begin(), villages.end());
        for (int i = 0; i < villages.size(); i++)
        {
            tmp.path.push_back(villages[i]);
        }
        tmp.path.push_back(start); /* 到这儿就构建了一个个体 */
        tmp.weight = sum(tmp);
        tmp.fitness = 1 / (float)tmp.weight;
        tmp.gen = gen;
        pop.push_back(tmp);
    }

    if (gen == 1)
    { /* 贪心初始化第一代 */

        Individual indi;
        map<int, bool> isVisited;
        indi.path.push_back(start);
        isVisited[start] = true; /* 起点访问 */

        for (int i = 0; i < villages.size(); i++)
        {                               /* 放入栈中次数 */
            int top = indi.path.back(); /* 栈顶元素 */
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
                { /* 如果没有说明没这个点 */
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

    /* 产生第二个孩子 */
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

/* 变异算子：顺序移位 */
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

/* 开始进化 */
vector<Individual> Evolution()
{

    vector<Individual> nextGeneration;       /* 每进化一代就重新生成一代 */
    sort(pop.begin(), pop.end(), myCompare); /* 排序找出最优的个体 */

    /* 最优解提前找到 */
    if (pop[0].weight == 36)
    {
        isFound = true;
    }
    /* 将最优解放到下一代 */
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
                        CrossOver(*it, *it2, nextGeneration); /* 交叉 */
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
        { /* 变异 */
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

    cout << "\n遗传算法模拟的最优结果为： ";
    for (int i = 0; i < pop[0].path.size(); i++)
    {
        cout << graph->vertexs[pop[0].path[i]] << "  ";
    }
    cout << ",  总权值为：  " << pop[0].weight << endl
         << endl;
    system("pause");
    return 0;
}