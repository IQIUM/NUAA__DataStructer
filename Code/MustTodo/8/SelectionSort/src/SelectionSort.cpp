#include <bits/stdc++.h>
#include "../../src/publicMethod.h"
using namespace std;

int arr[50000];
const int counts = 50000;
vector<int> times;

void Selection();

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

        readFile(filename, arr);
        int start = getCurrentTime();
        Selection();
        int end = getCurrentTime();
        filename = "../out/sample" + num + ".txt";
        writeFile(filename, arr);
        cout << "排序第 " << i << " 份样例所用时间为：  " << end - start
             << " 毫秒" << endl;
        ss.clear();
        times.push_back(end - start);
    }
    writeTime("选择排序", times);
    return 0;
}

/**
 * @description: 选择排序
 */
void Selection()
{
    for (int i = 0; i < counts; i++)
    {
        int k = i;
        for (int j = k + 1; j < counts; j++)
        {
            if (arr[j] < arr[k])
            {
                k = j;
            }
        }
        if (k != i)
        {
            int tmp = arr[i];
            arr[i] = arr[k];
            arr[k] = tmp;
        }
    }
}