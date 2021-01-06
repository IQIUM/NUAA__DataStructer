/***
 * @Author         : IQIUM
 * @Date           : 2020-11-28 12:17:37
 * @LastEditors    : IQIUM
 * @LastEditTime   : 2020-11-28 13:49:55
 * @FilePath       : \CouseDesign\MustTodo\2\MazeProblem.cpp
 */
#include "windows.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stack>
using namespace std;

const int MAX = 100;
int row = 0;
int col = 0;

// 坐标类
class Point
{
public:
    int x;
    int y;
    Point(int x, int y) : x(x), y(y) {}
    bool operator=(Point tmp) { return this->x == tmp.x && this->y == tmp.y; }
};

int maze[MAX][MAX];
// Point path[MAX];
stack<Point> st;

/*
 * @Description: 打印走迷宫的轨迹 1表示墙壁
 * @return: void
 */
void print()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (maze[i][j] == 1)
            {
                cout << "■"
                     << " ";
            }
            else if (maze[i][j] == 0 || maze[i][j] == 3)
            {
                cout << "  ";
            }
            else if (maze[i][j] == 2)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED);
                cout << "★"
                     << " ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED |
                                            FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else if (maze[i][j] == -1)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY |
                                            FOREGROUND_GREEN);
                cout << "☆"
                     << " ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED |
                                            FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
        }
        cout << endl;
    }
}

/*
 * @Description: 矩阵的初始化
 * @return: void
 */
void initMaze()
{
    ifstream in("maze2.txt", ios::in);
    if (in.fail())
    {
        cout << "文件打开失败，请检查文件名重试！ \n";
        exit(0);
    }
    string row_c;
    string col_c;
    in >> row_c;
    in >> col_c;
    row = atoi(row_c.c_str());
    col = atoi(col_c.c_str());
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            in >> maze[i + 1][j + 1];
        }
    }
    /* 把图加上墙 */
    for (int j = 0; j < col + 2; j++)
    {
        maze[0][j] = 1;
    }
    for (int j = 0; j < col + 2; j++)
    {
        maze[row + 1][j] = 1;
    }
    for (int i = 0; i < row + 2; i++)
    {
        maze[i][0] = 1;
    }
    for (int i = 0; i < row + 2; i++)
    {
        maze[i][col + 1] = 1;
    }

    row += 2;
    col += 2;

    in.close();
}

void getPath(int entryx, int entryy, int exitx, int exity)
{

    st.push(Point(entryx, entryy));
    maze[entryx][entryy] = -1;
    while (!st.empty())
    {
        Point tmp = st.top();

        int x = tmp.x;
        int y = tmp.y;

        /* 策略：右下左上 */
        if (x == exitx && y == exity)
        {
            return;
        }

        if (maze[x][y + 1] == 0)
        { /* 上 */
            st.push(Point(x, y + 1));
            maze[x][y + 1] = 2;
        }
        else if (maze[x + 1][y] == 0)
        { /* 右 */
            st.push(Point(x + 1, y));
            maze[x + 1][y] = 2;
        }
        else if (maze[x][y - 1] == 0)
        { /* 左 */
            st.push(Point(x, y - 1));
            maze[x][y - 1] = 2;
        }
        else if (maze[x - 1][y] == 0)
        { /* 下 */
            st.push(Point(x - 1, y));
            maze[x - 1][y] = 2;
        }
        else
        {
            maze[x][y] = 2;
            st.pop();
            maze[x][y] = 3;
        }
    }
}

bool test()
{
    cout << "请输入迷宫入口坐标： ";
    int entryx = -1, entryy = -1;
    cin >> entryx >> entryy;
    cout << "请输入迷宫出口坐标： ";
    int exitx = -1, exity = -1;
    cin >> exitx >> exity;
    if (maze[entryx][entryy] == 1)
    {
        cout << "输入起点有误，请尝试重新输入！" << endl;
        return false;
    }
    if (maze[exitx][exity] == 1)
    {
        cout << "输入起点有误，请尝试重新输入！" << endl;
        return false;
    }
    getPath(entryx, entryy, exitx, exity);
    maze[exitx][exity] = -1;
    cout << endl;
    return true;
}

int main()
{
    initMaze();
    print();
    if (test())
    {
        system("cls");
        print();
        system("pause");
    }
    return 0;
}