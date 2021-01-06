#include <bits/stdc++.h>
#include "../../src/publicMethod.h"
using namespace std;

int arr[50000];
const int counts = 50000;
vector<int> times;
void ShellSort();

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
        ShellSort();
        int end = getCurrentTime();
        filename = "../out/sample" +
                   num + ".txt";
        writeFile(filename, arr);
        cout << "ÅÅÐòµÚ " << i << " ·ÝÑùÀýËùÓÃÊ±¼äÎª£º  " << end - start
             << " ºÁÃë" << endl;
        times.push_back(end - start);
    }
    writeTime("Ï£¶ûÅÅÐò", times);
    return 0;
}

/**
 * @description: Ï£¶ûÅÅÐò
 */
void ShellSort()
{
    for (int gap = counts / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < counts; i++)
        {
            int j = i;
            int temp = arr[j];
            if (arr[j] < arr[j - gap])
            {
                while (j - gap >= 0 && temp < arr[j - gap])
                {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                arr[j] = temp;
            }
        }
    }
}