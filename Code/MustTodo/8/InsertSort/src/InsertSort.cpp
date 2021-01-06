#include <bits/stdc++.h>
#include "../../src/publicMethod.h"
using namespace std;

int arr[50000];
const int counts = 50000;
vector<int> times;
void InsertSort();
void writeTime();

int main()
{
    stringstream ss;
    for (int i = 1; i <= 10; i++)
    {
        ss << i;
        string num;
        ss >> num;
        string filename = "../../samples/sample" +
                          num + ".txt";

        ss.clear();
        readFile(filename, arr);
        int start = getCurrentTime();
        InsertSort();
        int end = getCurrentTime();
        filename = "../out/sample" + num + ".txt";
        writeFile(filename, arr);
        cout << "����� " << i << " ����������ʱ��Ϊ��  " << end - start
             << " ����" << endl;
        times.push_back(end - start);
    }
    string sortname = "��������";
    writeTime(sortname, times);
    return 0;
}

/**
 * @description: ��������
 */
void Insert(int num, int length)
{
    int i = 0;
    for (i = length - 1; i >= 0; i--)
    {
        if (num < arr[i])
        {
            arr[i + 1] = arr[i];
        }
        else
        {
            break;
        }
    }
    arr[i + 1] = num;
}

void InsertSort()
{
    int length = 1;
    for (int i = 1; i < counts; i++)
    {
        Insert(arr[i], length);
        length++;
    }
}
