#include "B-Tree.h"
#include <bits/stdc++.h>
#include "windows.h"
using namespace std;
vector<int> initNodes; //��ʼ���ļ��ж�ȡ������
void readFile();
void menu();
int main()
{
    BTree *btree = NULL;
    int key = -1;

    menu();
    while (1)
    {
        cout << "\n\t��ѡ����Ҫ��������ţ�  ";
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
            cout << "��������Ҫ����Ĺؼ��֣�  ";
            cin >> key;
            btree->insert(key);
            break;
        case 3:
            cout << "��������Ҫ��ѯ�Ĺؼ��֣�  ";
            cin >> key;
            if (btree->contain(key))
            {

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_GREEN);
                cout << "\n"
                     << key << "  ��B����" << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED |
                                            FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED);
                cout << "\n"
                     << key << "  ����B����" << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED |
                                            FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            cout << "\t��ѯ���!" << endl;
            break;
        case 4:
            cout << "��ʼ��α���B��\n";
            btree->btree_level_traverse();
            cout << "\n������ϣ���" << endl;
            break;
        case 5:
            cout << "\n\tллʹ�ã�" << endl;
            exit(0);
        default:
            break;
        }
    }

    return 0;
}

/**
 * @description: ���ļ��ж�ȡ����
 */
void readFile()
{
    cout << "���ڴ��ļ��ж�ȡ�ڵ���Ϣ��........\n";
    ifstream in("data.txt", ios::in);
    if (in.fail())
    {
        cout << "[Error] �ļ���ʧ�ܣ�" << endl;
        exit(0);
    }
    while (!in.eof())
    {
        string str;
        getline(in, str, ' ');
        initNodes.push_back(atoi(str.c_str()));
    }
    in.close();
    cout << "�ļ���ȡ��ϣ���" << endl;
}

void menu()
{
    cout << "**********************************************" << endl;
    cout << "**                                          **" << endl;
    cout << "**                                          **" << endl;
    cout << "**            ��ӭʹ��B������ϵͳ           **" << endl;
    cout << "**                                          **" << endl;
    cout << "**            [1] B����ʼ��                 **" << endl;
    cout << "**            [2] ��ӹؼ���                **" << endl;
    cout << "**            [3] ��ѯ�ؼ���                **" << endl;
    cout << "**            [4] B����ѯ                   **" << endl;
    cout << "**            [5] �˳�                      **" << endl;
    cout << "**                                          **" << endl;
    cout << "**                                          **" << endl;
    cout << "**********************************************" << endl;
}