#include "B-Tree.h"
#include <bits/stdc++.h>
#include "windows.h"
using namespace std;
vector<int> initNodes; //初始从文件中读取的数据
void readFile();
void menu();
int main()
{
    BTree *btree = NULL;
    int key = -1;

    menu();
    while (1)
    {
        cout << "\n\t请选择你要操作的序号：  ";
        int num = -1;
        cin >> num;
        cout << "\n";
        switch (num)
        {
        case 1:
            if (btree != NULL)
            {
                delete btree;
                btree = NULL;
            }
            btree = new BTree();
            readFile();
            for (int i = 0; i < initNodes.size(); i++)
            {
                btree->insert(initNodes[i]);
            }
            break;
        case 2:
            cout << "请输入你要插入的关键字：  ";
            cin >> key;
            btree->insert(key);
            break;
        case 3:
            cout << "请输入你要查询的关键字：  ";
            cin >> key;
            if (btree->contain(key))
            {

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_GREEN);
                cout << "\n"
                     << key << "  在B树中" << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED |
                                            FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED);
                cout << "\n"
                     << key << "  不在B树中" << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED |
                                            FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            cout << "\t查询完毕!" << endl;
            break;
        case 4:
            cout << "开始层次遍历B树\n";
            btree->btree_level_traverse();
            cout << "\n遍历完毕！！" << endl;
            break;
        case 5:
            cout << "\n\t谢谢使用！" << endl;
            exit(0);
        default:
            break;
        }
    }

    return 0;
}

/**
 * @description: 从文件中读取数据
 */
void readFile()
{
    cout << "正在从文件中读取节点信息中........\n";
    ifstream in("data.txt", ios::in);
    if (in.fail())
    {
        cout << "[Error] 文件打开失败！" << endl;
        exit(0);
    }
    while (!in.eof())
    {
        string str;
        getline(in, str, ' ');
        initNodes.push_back(atoi(str.c_str()));
    }
    in.close();
    cout << "文件读取完毕！！" << endl;
}

void menu()
{
    cout << "**********************************************" << endl;
    cout << "**                                          **" << endl;
    cout << "**                                          **" << endl;
    cout << "**            欢迎使用B树构建系统           **" << endl;
    cout << "**                                          **" << endl;
    cout << "**            [1] B树初始化                 **" << endl;
    cout << "**            [2] 添加关键字                **" << endl;
    cout << "**            [3] 查询关键字                **" << endl;
    cout << "**            [4] B树查询                   **" << endl;
    cout << "**            [5] 退出                      **" << endl;
    cout << "**                                          **" << endl;
    cout << "**                                          **" << endl;
    cout << "**********************************************" << endl;
}