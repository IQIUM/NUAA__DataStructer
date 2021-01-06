#include <bits/stdc++.h>
#include "../../src/publicMethod.h"
using namespace std;
int arr[50000];
const int counts = 50000;
vector<int> times;
void QuickSort();

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
        QuickSort();
        int end = getCurrentTime();
        filename = "../out/sample" + num + ".txt";
        writeFile(filename, arr);
        cout << "排序第 " << i << " 份样例所用时间为：  " << end - start
             << " 毫秒" << endl;
        times.push_back(end - start);
    }
    writeTime("快速排序", times);

    return 0;
}

int partition(int low, int high)
{
    int tmp = arr[low];
    while (low < high)
    {
        while (low < high && tmp <= arr[high])
        {
            high--;
        }
        arr[low] = arr[high];
        while (low < high && tmp >= arr[low])
        {
            low++;
        }
        arr[high] = arr[low];
    }
    arr[low] = tmp;
    return low;
}

void QuickSort(int low, int high)
{
    if (low < high)
    {
        int pivot = partition(low, high);
        QuickSort(low, pivot - 1);
        QuickSort(pivot + 1, high);
    }
}
/**
 * @description: 快速排序
 */
void QuickSort() { QuickSort(0, counts - 1); }