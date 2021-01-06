#include <bits/stdc++.h>
#include "E:\\DataStructure\\CourseDesign\\CouseDesign\\Summary\\MustTodo\\8\\src\\publicMethod.h"
using namespace std;

int arr[50000];
const int counts = 50000;
vector<int> times;

void BubbleSort();

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
        BubbleSort();
        int end = getCurrentTime();
        filename = "../out/sample" + num + ".txt";
        writeFile(filename, arr);
        cout << "ÅÅÐòµÚ " << i << " ·ÝÑùÀýËùÓÃÊ±¼äÎª£º  " << end - start
             << " ºÁÃë" << endl;
        times.push_back(end - start);
    }
    writeTime("Ã°ÅÝÅÅÐò", times);
    return 0;
}

/**
 * @description: Ã°ÅÝÅÅÐò
 */
void BubbleSort()
{
    for (int i = 0; i < counts - 1; i++)
    {
        for (int j = 0; j < counts - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}