#include <bits/stdc++.h>
using namespace std;

void print(int arr[], int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int calculation(int roil[], int n, int sail[], int m)
{
    int result = 0;
    int pn = 0;             //正数:positive number
    int nn = min(n, m) - 1; //负数：negative number
    while (pn < n && pn < m && roil[pn] > 0 && sail[pn] > 0)
    {
        result += roil[pn] * sail[pn];
        pn++;
    }
    //尾部有点特殊，需要单独处理
    int a = n - 1;
    int b = m - 1;
    while (a >= 0 && b >= 0 && roil[a] < 0 && sail[b] < 0)
    {
        result += roil[a] * sail[b];
        a--;
        b--;
    }
    return result;
}
bool cmp(int a, int b)
{
    return a > b;
}

int main()
{
    int n = 0;
    int *roil = NULL;
    int m = 0;
    int *sail = NULL;
    cin >> n;
    roil = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> roil[i];
    }
    cin >> m;
    sail = new int[m];
    for (int i = 0; i < m; i++)
    {
        cin >> sail[i];
    }

    // QuickSort(sail, 0, m - 1);
    // QuickSort(roil, 0, n - 1);
    sort(sail, sail + m, cmp);
    sort(roil, roil + n, cmp);
    // print(roil, n);
    // print(sail, m);  
    cout << "最大回报为:  " << calculation(roil, n, sail, m) << endl;

    return 0;
}