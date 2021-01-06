/*
 * @Author            : IQIUM
 * @Github            : https://github.com/IQIUM
 * @Date              : 2021-01-06 18:48:36
 * @LastEditTime      : 2021-01-06 19:18:53
 * @FilePath          : \Code\MustTodo\8\HeapSort\src\heapSort.cpp
 * @Discription       : 
 * @Copyright 2021 IQIUM
 */
#include <bits/stdc++.h>
#include "../../src/publicMethod.h"
using namespace std;

int arr[50000];
const int counts = 50000;
vector<int> times;

void HeapSort();

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
        HeapSort();
        int end = getCurrentTime();
        filename = "../out/sample" + num + ".txt";
        writeFile(filename, arr);
        cout << "排序第 " << i << " 份样例所用时间为：  " << end - start
             << " 毫秒" << endl;
        times.push_back(end - start);
        ss.clear();
    }
    writeTime("堆排序", times);
    return 0;
}

/**
 * @description: 堆排序
 */
void HeapSort(int i, int length)
{
    int tmp = arr[i];
    for (int k = 2 * i + 1; k < length; k = 2 * k + 1)
    {
        if (k + 1 < length && arr[k] < arr[k + 1])
        {
            ++k;
        }
        if (tmp < arr[k])
        {
            arr[i] = arr[k];
            i = k;
        }
        else
        {
            break;
        }
    }
    arr[i] = tmp;
}

void HeapSort()
{
    int tmp = 0;
    for (int i = counts / 2 - 1; i >= 0; --i)
    {
        HeapSort(i, counts);
    }
    for (int j = counts - 1; j > 0; j--)
    {
        tmp = arr[j];
        arr[j] = arr[0];
        arr[0] = tmp;
        HeapSort(0, j);
    }
}
