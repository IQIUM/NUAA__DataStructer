#include <bits/stdc++.h>
using namespace std;

const int MAX = 12000;
const int line_max = 2000; //最多2000条公交路线

map<string, int> maps;
map<int, string> remaps;
vector<pair<int, vector<int>>> path;			 //存放转车点
vector<pair<pair<int, vector<int>>, int>> path2; //存放转车点

void menu();

class ArcNode
{
public:
	int id; //边的下一个id
	ArcNode *next;

	ArcNode(int id) : id(id), next(nullptr) {}
};

class VertexHead
{
public:
	int id; //表头id
	ArcNode *first;
	VertexHead() : first(nullptr) {}
};

//路线类
class Line
{
public:
	int no; //路线编号
};

//站点类
class Station
{
public:
	int id;		   //站点id
	string name;   //站点名称
	set<int> buss; //经过站点的公交车的路线
	Station() {}

	Station(string name, int busNo) : name(name) { buss.insert(busNo); }
};

//路线+站点
class LineBus
{
public:
	Line line;			  //路线
	vector<int> stations; //每一条路线的所有站点
};

class Graph
{
public:
	VertexHead heads[MAX];	  //所有的表头
	vector<LineBus> lines;	  //文件中的所有路线
	vector<Station> stations; //存储所有的站点
	vector<int> lines_no;	  //所有路线编号
	int line_num;			  //路线数
	int station_num;		  //站点数

	Graph()
	{
		for (int i = 0; i < MAX; ++i)
		{
			heads[i].id = i;
		}
	}

	void insertArc(int &s1, int &s2)
	{
		ArcNode *p = heads[s1].first;
		while (p != nullptr)
		{
			if (p->id == s2)
			{
				return;
			}
			p = p->next;
		}
		ArcNode *arc = new ArcNode(s2);
		arc->next = heads[s1].first;
		heads[s1].first = arc;
		ArcNode *arc2 = new ArcNode(s1);
		arc2->next = heads[s2].first;
		heads[s2].first = arc2;
	}
};

Graph *graph = new Graph();

/* 从文件中读取公交线路 */
void readFileRoutine()
{
	ifstream in("routine.txt");
	if (in.fail())
	{
		cout << "公交线路打开失败！" << endl;
		exit(0);
	}
	string bus;
	string stations;
	string station;
	stringstream ss;
	int count = 0;
	while (in.peek() != EOF)
	{
		LineBus cur_line;

		//获取每一条线路号
		getline(in, bus, ' ');
		int busNo = atoi(bus.substr(0, bus.size() - 1).c_str());
		cur_line.line.no = busNo;
		graph->lines_no.push_back(busNo);
		//获取该路线所有的站点
		getline(in, stations, '\n');
		while (stations[0] == ' ')
		{
			stations = stations.substr(1, stations.size() - 1);
		}
		ss.str(stations);

		while (getline(ss, station, ','))
		{
			// 1. 判断station是否已经出现在了图中
			bool flag = false;
			int index = -1;
			for (int i = 0; i < graph->stations.size(); ++i)
			{
				if (graph->stations[i].name == station)
				{
					flag = true;
					index = i;
					break;
				}
			}
			if (flag)
			{ //如果当前站点之前就出现过
				graph->stations[index].buss.insert(busNo);
				cur_line.stations.push_back(graph->stations[index].id);
				if (cur_line.stations.size() != 1)
				{ //说明是始发站
					graph->insertArc(cur_line.stations[cur_line.stations.size() - 1],
									 cur_line.stations[cur_line.stations.size() - 2]);
				}
			}
			else
			{
				Station s;
				count++;
				s.id = count;
				s.name = station;
				s.buss.insert(busNo);
				graph->stations.push_back(s);
				maps.insert(make_pair(station, count));
				remaps.insert(make_pair(count, station));
				cur_line.stations.push_back(count);
				if (cur_line.stations.size() != 1)
				{ //说明是始发站
					graph->insertArc(cur_line.stations[cur_line.stations.size() - 1],
									 cur_line.stations[cur_line.stations.size() - 2]);
				}
			}
		}
		graph->lines.push_back(cur_line);
		bus = "";
		ss.clear();
		ss.str("");
		stations = "";
		station = "";
	}
	in.close();
	graph->line_num = graph->lines_no.size();
	graph->station_num = graph->stations.size();
}

/* 获取两个站点之间路线的交集 */
bool intersection(int start_id, int end_id)
{
	vector<int> inter(line_max);
	int s_index = -1;
	int e_index = -1;
	for (size_t i = 0; i < graph->stations.size(); i++)
	{
		if (s_index != -1 && e_index != -1)
		{
			break;
		}
		else
		{
			if (graph->stations[i].id == start_id)
			{
				s_index = i;
			}
			else if (graph->stations[i].id == end_id)
			{
				e_index = i;
			}
		}
	}
	auto it =
		set_intersection(graph->stations[s_index].buss.begin(),
						 graph->stations[s_index].buss.end(),
						 graph->stations[e_index].buss.begin(),
						 graph->stations[e_index].buss.end(), inter.begin());
	inter.resize(it - inter.begin());
	if (inter.empty())
	{
		return false;
	}
	else
	{
		path.push_back(make_pair(start_id, inter));
		path2.push_back(make_pair(make_pair(start_id, inter), end_id));
		return true;
	}
}

int min(int dist[], bool flag[], int size)
{
	int min = MAX;
	int min_index = -1;
	for (int i = 1; i <= size; ++i)
	{
		if (!flag[i] && dist[i] < min)
		{
			min = dist[i];
			min_index = i;
		}
	}
	return min_index;
}

void show(stack<int> line, string start, string end)
{
	vector<vector<int>> buss;
	int *stations = new int[line.size()];
	int count = 0;
	while (!line.empty())
	{
		int top = line.top();
		line.pop();
		stations[count] = top;
		if (line.empty())
		{
			continue;
		}
		int next = line.top();
		vector<int> tmp;
		for (set<int>::iterator it1 = graph->stations[top].buss.begin();
			 it1 != graph->stations[top].buss.end(); ++it1)
		{
			for (set<int>::iterator it2 = graph->stations[next].buss.begin();
				 it2 != graph->stations[next].buss.end(); ++it2)
			{
				if (*it1 == *it2)
				{
					tmp.push_back(*it1);
				}
			}
		}
		buss.push_back(tmp);
		++count;
	}

	/* 输出最终路线 */
	int cur_line = buss[0][0];
	cout << "从 " << start << " 到 " << end << " 的路线如下：  \n";
	int pre_line = cur_line;
	for (int i = 0; i < count; ++i)
	{

		bool flag = false;
		for (int j = 0; j < buss[i].size(); ++j)
		{
			if (buss[i][j] == cur_line)
			{
				flag = true;
				break;
			}
		}

		if (!flag)
		{
			if (buss[i].size() > 0)
			{
				cur_line = buss[i][0];
				cout << "\t乘坐： " << pre_line << " 号公交到 "
					 << graph->stations[i].name << " \n";
				pre_line = cur_line;
			}
		}
	}
	cout << "\t乘坐： " << pre_line << " 号公交到 " << end << " \n";
}

void Dijkstra(string start, string end)
{
	int start_id = maps[start];
	int end_id = maps[end];
	int size = graph->stations.size();
	int *dist = new int[size + 1];
	int *p = new int[size + 1];
	bool *flag = new bool[size + 1];
	for (int i = 0; i <= size; ++i)
	{ /*1. 初始化*/
		flag[i] = false;
		dist[i] = MAX;
		p[i] = 0;
	}

	ArcNode *ptr = graph->heads[start_id].first;
	while (ptr != NULL)
	{
		dist[ptr->id] = 1;
		p[ptr->id] = start_id;
		ptr = ptr->next;
	}

	flag[start_id] = true;
	for (size_t i = 1; i < size; i++)
	{
		if (flag[end_id])
		{
			break;
		}
		int min_index = min(dist, flag, size);
		flag[min_index] = true;
		int min_dist = dist[min_index];
		/* 更新 */
		if (min_dist < MAX)
		{
			for (size_t j = 1; j <= size; j++)
			{
				if (!flag[j])
				{
					int distance = MAX;
					ArcNode *ptr = graph->heads[min_index].first;
					while (ptr != nullptr)
					{
						if (ptr->id == j)
						{
							distance = 1;
							break;
						}
						ptr = ptr->next;
					}
					if (!flag[j] && distance != MAX && min_dist + distance < dist[j])
					{
						dist[j] = min_dist + distance;
						p[j] = min_index;
					}
				}
			}
		}
	}
	int cur_index = end_id;
	int pre_index = p[cur_index];
	stack<int> line;
	while (pre_index != cur_index)
	{
		line.push(cur_index);
		cur_index = pre_index;
		pre_index = p[pre_index];
	}
	line.push(start_id);
	show(line, remaps[start_id], remaps[end_id]);
	delete[] dist;
	delete[] p;
	delete[] flag;
}

void findLeastTransfer(string start, string end)
{
	//找到起始点和终点
	int start_id = maps[start];
	int end_id = maps[end];

	//设定转车阈值
	int N = 4;
	int n = 0;

	queue<pair<pair<int, int>, int>> que;
	que.push(make_pair(make_pair(start_id, 0), 0));
	int pre_level = 0;
	int preParent = 0;

	while (n < N)
	{
		int parent = que.front().second;
		start_id = que.front().first.first;
		int level = que.front().first.second;
		if (level != pre_level)
		{
			n++;
			pre_level = level;
		}
		que.pop();
		if (parent != 0)
		{
			intersection(parent, start_id);
		}
		bool flag = intersection(start_id, end_id);

		if (flag)
		{ //找到通路
			break;
		}
		else
		{ //没有找到
			if (!path.empty())
			{
				path.pop_back();
			}
			int s_index = -1;
			for (size_t i = 0; i < graph->stations.size(); i++)
			{
				if (graph->stations[i].id == start_id)
				{
					s_index = i;
					break;
				}
			}
			//把所有跟跟站点相关的站点都放入队列	d
			for (auto it = graph->stations[s_index].buss.begin(); it != graph->stations[s_index].buss.end(); ++it)
			{
				for (size_t i = 0; i < graph->lines.size(); i++)
				{
					if (graph->lines[i].line.no == *it)
					{
						for (size_t j = 0; j < graph->lines[i].stations.size(); j++)
						{
							if (graph->lines[i].stations[j] != start_id)
							{
								que.push(make_pair(make_pair(graph->lines[i].stations[j], level + 1), start_id));
							}
						}
					}
				}
			}
		}
	}

	if (n >= N)
	{
		cout << "从 " << start << " 到 " << end
			 << " 乘坐公交车需要大于10次转车，建议选择其它交通工具！";
		return;
	}
	if (path.size() == 0)
	{
		cout << "查询失败！" << endl;
		exit(0);
	}

	stack<pair<int, vector<int>>> final_res; //最终公交车的结果
	auto tmp = path2[path2.size() - 1];
	final_res.push(tmp.first);
	int index = path2.size() - 2;
	if (index >= 0)
	{
		int bef_end = tmp.first.first;
		for (int i = index; i >= 0; --i)
		{
			int i_index = -1;
			for (int j = i; j >= 0; --j)
			{
				if (path2[j].second == bef_end)
				{
					i_index = j;
				}
			}
			if (i_index != -1)
			{
				final_res.push(path2[i_index].first);
				bef_end = path2[i_index].first.first;
			}
			i = i_index;
			--i;
		}
	}
	cout << "\n从 " << start << " 到 " << end << " 的乘车路线如下： \n\t";
	auto t_start = final_res.top();
	final_res.pop();
	cout << "从 " << remaps[t_start.first] << " 乘坐： ";
	for (size_t j = 0; j < t_start.second.size(); j++)
	{
		cout << t_start.second[j] << "线";
		if (j != t_start.second.size() - 1)
		{
			cout << " 或 ";
		}
	}
	while (!final_res.empty())
	{
		auto t = final_res.top();

		cout << " 到 " << remaps[t.first] << ",然后乘坐: ";
		for (size_t j = 0; j < t.second.size(); j++)
		{
			cout << t.second[j] << "线";
			if (j != t.second.size() - 1)
			{
				cout << " 或 ";
			}
		}
		final_res.pop();
	}
	cout << " 到终点站： " << end;
}

bool check(string start, string end)
{
	return maps.find(start) != maps.end() && maps.find(end) != maps.end();
}

void enquiry(int num)
{
	string start;
	string end;
	cout << "\n请输入起点：  ";
	cin >> start;
	cout << "请输入终点：  ";
	cin >> end;
	if (check(start, end))
	{
		if (start == end)
		{
			cout << "输入的起始站点与终点一致！无需换乘！" << endl;
			return;
		}
		if (num == 1)
		{
			findLeastTransfer(start, end);
			path.clear();
		}
		else if (num == 2)
		{
			Dijkstra(start, end);
			path.clear();
		}
	}
	else
	{
		cout << "输入有误，请重新输入！" << endl;
	}
	cout << "\n\n";
}

int main()
{
	readFileRoutine();
	int num = 0;

	while (1)
	{
		system("cls");
		menu();
		cout << "\n\t请输入你要查询的方式：  ";
		cin >> num;
		switch (num)
		{
		case 1:
		{
			enquiry(1);
			system("pause");
			break;
		}
		case 2:
		{
			enquiry(2);
			system("pause");
			break;
		}
		case 3:
		{
			cout << "\n\t谢谢使用！" << endl;
			exit(0);
		}
		default:
			break;
		}
	}
	return 0;
}

void menu()
{
	cout << "**********************************************" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**            欢迎使用公交查询系统          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**            [1] 查询最少换乘路线          **" << endl;
	cout << "**            [2] 查询经过站点路线          **" << endl;
	cout << "**            [3] 退出                      **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**                                          **" << endl;
	cout << "**********************************************" << endl;
}
