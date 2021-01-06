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

// ������
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
 * @Description: ��ӡ���Թ��Ĺ켣 1��ʾǽ��
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
                cout << "��"
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
                cout << "��"
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
                cout << "��"
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
 * @Description: ����ĳ�ʼ��
 * @return: void
 */
void initMaze()
{
    ifstream in("maze2.txt", ios::in);
    if (in.fail())
    {
        cout << "�ļ���ʧ�ܣ������ļ������ԣ� \n";
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
    /* ��ͼ����ǽ */
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

        /* ���ԣ��������� */
        if (x == exitx && y == exity)
        {
            return;
        }

        if (maze[x][y + 1] == 0)
        { /* �� */
            st.push(Point(x, y + 1));
            maze[x][y + 1] = 2;
        }
        else if (maze[x + 1][y] == 0)
        { /* �� */
            st.push(Point(x + 1, y));
            maze[x + 1][y] = 2;
        }
        else if (maze[x][y - 1] == 0)
        { /* �� */
            st.push(Point(x, y - 1));
            maze[x][y - 1] = 2;
        }
        else if (maze[x - 1][y] == 0)
        { /* �� */
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
    cout << "�������Թ�������꣺ ";
    int entryx = -1, entryy = -1;
    cin >> entryx >> entryy;
    cout << "�������Թ��������꣺ ";
    int exitx = -1, exity = -1;
    cin >> exitx >> exity;
    if (maze[entryx][entryy] == 1)
    {
        cout << "������������볢���������룡" << endl;
        return false;
    }
    if (maze[exitx][exity] == 1)
    {
        cout << "������������볢���������룡" << endl;
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