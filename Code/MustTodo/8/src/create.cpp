#include <bits/stdc++.h>
using namespace std;

int main()
{
    cout << "开始生成随机数!" << endl;

    int array[50000];
    srand((unsigned int)time(NULL));
    //1. 生成顺序样本

    ofstream in_seq("../samples/sample1.txt", ios::out | ios::trunc);
    if (in_seq.fail())
    {
        cout << "[Error]  顺序文件创建失败!" << endl;
        exit(0);
    }
    for (int i = 1; i <= 50000; i++)
    {
        in_seq << i << " ";
    }
    in_seq.close();

    //2. 生成逆序样本
    ofstream in_unseq("../samples/sample2.txt", ios::out | ios::trunc);
    if (in_unseq.fail())
    {
        cout << "[Error]  顺序文件创建失败!" << endl;
        exit(0);
    }
    for (int i = 50000; i >= 1; i--)
    {
        in_unseq << i << " ";
    }
    in_unseq.close();

    //3. 生成随机数
    for (int i = 2; i < 10; i++)
    {
        stringstream ss;
        string filename = "../samples/sample";
        ss << i + 1;
        string num;
        ss >> num;
        filename += num + ".txt";
        ofstream out(filename, ios::out | ios::trunc);
        if (out.fail())
        {
            cout << "[Error]  文件创建失败!" << endl;
            exit(0);
        }
        ss.clear();

        string res = "";
        string tmp;
        for (int j = 0; j < 50000; j++)
        {
            array[j] = rand();
            ss << array[j];
            ss >> tmp;
            res += tmp + " ";
            ss.clear();
            tmp = "";
        }
        res += "\n";
        out << res;
        out.close();
    }
    cout << "随机数生成完成!" << endl;

    return 0;
}