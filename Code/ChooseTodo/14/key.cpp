#include <bits/stdc++.h>
#include "windows.h"
using namespace std;
const int MAX = 1001;
int N = 0;
int K = 0;
int keys[MAX];

struct Record
{
    int num;  //钥匙编号
    int time; //借（还）时间
    int oper; //操作，借 ：1 , 还：2
    Record(int num, int time, int oper) : num(num), time(time), oper(oper) {}
};

bool myCompare(Record r1, Record r2)
{
    //先还后借
    if (r1.time == r2.time && r1.oper == 2 && r2.oper == 2)
    {
        return r1.num < r2.num;
    }
    else if (r1.time == r2.time && (r1.oper == 1 || r2.oper == 1))
    {
        if (r2.oper == 1)
        {
            return true;
        }
        else if (r1.oper == 1)
        {
            return false;
        }
    }
    return r1.time < r2.time;
}

vector<Record> records;

void test()
{
    for (int i = 0; i < records.size(); i++)
    {
        cout << records[i].num << "  " << records[i].time << "  "
             << records[i].oper << endl;
    }
}

void readFile()
{
    ifstream in("data.txt", ios::in);
    if (in.fail())
    {
        cout << "[Error] 文件打开失败！" << endl;
        exit(0);
    }
    string content = "";
    int w, s, c;
    stringstream ss;
    getline(in, content, '\n');
    N = atoi(content.substr(0, 1).c_str());
    K = atoi(content.substr(2, 1).c_str());
    while (getline(in, content, '\n'))
    {
        ss.str(content);
        string tmp = "";
        int arr[3];
        int count = 0;
        while (getline(ss, tmp, ' '))
        {
            arr[count++] = atoi(tmp.c_str());
        }
        w = arr[0];
        s = arr[1];
        c = arr[2];
        records.push_back(Record(w, s, 1));
        records.push_back(Record(w, s + c, 2));
        ss.clear();
    }
}
void print()
{
    for (int i = 1; i <= N; i++)
    {
        if (keys[i] == 0)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                    FOREGROUND_INTENSITY | FOREGROUND_RED);
            cout << "X"
                 << "  ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                    FOREGROUND_INTENSITY | FOREGROUND_RED |
                                        FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                    FOREGROUND_INTENSITY |
                                        FOREGROUND_GREEN);
            cout << keys[i] << "  ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                    FOREGROUND_INTENSITY | FOREGROUND_RED |
                                        FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
    }
    cout << "\n\n";
}

int main()
{
    for (int i = 1; i < MAX; i++)
    {
        keys[i] = i;
    }
    readFile();
    sort(records.begin(), records.end(), myCompare);
    cout << "\n";
    for (int i = 0; i < records.size(); i++)
    {
        if (records[i].oper == 1)
        {
            int j = 1;
            for (; j <= N; j++)
            {
                if (keys[j] == records[i].num)
                {
                    keys[j] = 0;
                    break;
                }
            }
            cout << "取出钥匙  " << records[i].num << "  后： ";
            print();
        }
        else if (records[i].oper == 2)
        {
            for (int j = 1; j <= N; j++)
            {
                if (keys[j] == 0)
                {
                    keys[j] = records[i].num;
                    break;
                }
            }
            cout << "归还钥匙  " << records[i].num << "  后： ";
            print();
        }
    }
    return 0;
}