#include <bits/stdc++.h>
#include "../../src/publicMethod.h"
using namespace std;

int arr[50000];
const int counts = 50000;
vector<int> times;
void radixSort();

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
        radixSort();
        int end = getCurrentTime();
        filename = "../out/sample" +
                   num + ".txt";
        writeFile(filename, arr);
        cout << "排序第 " << i << " 份样例所用时间为：  " << end - start
             << " 毫秒" << endl;
        times.push_back(end - start);
    }
    writeTime("基数排序", times);
    return 0;
}

/**
 * @description: 基数排序
 */
void radixSort()
{
    int max = arr[0];
    for (int i = 1; i < counts; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }
    int maxLength = 0;
    while (max)
    {
        max /= 10;
        maxLength++;
    }
    //设置一个二维数组为一个桶
    int **bucket;
    bucket = new int *[10];
    for (int i = 0; i < 10; i++)
    {
        bucket[i] = new int[counts]();
    }
    int *bucketElementCounts = new int[10]();

    for (int k = 0, n = 1; k < maxLength; k++, n *= 10)
    {
        for (int i = 0; i < counts; i++)
        {
            int digitOfElement = (arr[i] / n) % 10;
            bucket[digitOfElement][bucketElementCounts[digitOfElement]++] =
                arr[i];
        }
        int index = 0;
        for (int i = 0; i < 10; i++)
        {
            if (bucketElementCounts[i] > 0)
            {
                for (int j = 0; j < bucketElementCounts[i]; j++)
                {
                    arr[index++] = bucket[i][j];
                }
            }
            bucketElementCounts[i] = 0;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        delete[] bucket[i];
    }
    delete[] bucket;
    delete[] bucketElementCounts;
}