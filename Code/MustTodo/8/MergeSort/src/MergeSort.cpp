#include <bits/stdc++.h>
#include "../../src/publicMethod.h"
using namespace std;

int arr[50000];
const int counts = 50000;
vector<int> times;
void mergeSort();

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
        mergeSort();
        int end = getCurrentTime();
        filename = "../out/sample" +
                   num + ".txt";
        writeFile(filename, arr);
        cout << "排序第 " << i << " 份样例所用时间为：  " << end - start
             << " 毫秒" << endl;
        times.push_back(end - start);
    }
    writeTime("归并排序", times);
    return 0;
}

/**
 * @description: 归并排序的合并算法
 */
void merge(int left, int mid, int right, int tmp[])
{
    int i = left;
    int j = mid + 1;
    int t = 0;
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            tmp[t++] = arr[i++];
        }
        else
        {
            tmp[t++] = arr[j++];
        }
    }
    while (i <= mid)
    {
        tmp[t++] = arr[i++];
    }
    while (j <= right)
    {
        tmp[t++] = arr[j++];
    }
    t = 0;
    int tmpLeft = left;
    while (tmpLeft <= right)
    {
        arr[tmpLeft++] = tmp[t++];
    }
}

void mergeSort(int left, int right, int tmp[])
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        mergeSort(left, mid, tmp);
        mergeSort(mid + 1, right, tmp);
        merge(left, mid, right, tmp);
    }
}

void mergeSort()
{
    int *tmp = new int[counts]();
    mergeSort(0, counts - 1, tmp);
}
