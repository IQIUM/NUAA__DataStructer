#include <bits/stdc++.h>
using namespace std;
int arr[1002] = {0};
vector<pair<int, int> > res;

bool myCompare(pair<int, int> p1, pair<int, int> p2) {
    if (p1.second == p2.second) {
        return p1.first < p2.first;
    }
    return p1.second > p2.second;
}

int main() {
    int n = 0;
    cin >> n;
    int *num = new int[n];
    for (int i = 0; i < n; i++) {
        int num = 0;
        cin >> num;
        arr[num]++;
    }
    /* 对数组进行数值从小到大排序 */
    for (int i = 0; i < 1002; i++) {
        if (arr[i] != 0) {
            res.push_back(make_pair(i, arr[i]));
        }
    }
    sort(res.begin(), res.end(), myCompare);

    for (int i = 0; i < res.size(); i++) {
        cout << res[i].first << " " << res[i].second << endl;
    }

    return 0;
}