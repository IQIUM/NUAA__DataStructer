#include <bits/stdc++.h>
using namespace std;

int matrix[31][31];
int copyM[31][31];
int n = 0;
int m = 0;

struct Point {
    int x;
    int y;
    int data;
    Point(int i, int j, int value) : x(i), y(j), data(value) {}
};

queue<Point> q;

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
            copyM[i][j] = matrix[i][j];
        }
    }
}

void SetZero() {
    while (!q.empty()) {
        Point p = q.front();
        q.pop();
        int x = p.x;
        int y = p.y;
        copyM[x][y] = 0;
    }
}

void Elimination() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!q.empty()) {
                Point back = q.back();
                if (matrix[i][j] != back.data) {
                    if (q.size() >= 3) {
                        SetZero();
                    }
                    while (!q.empty()) {
                        q.pop();
                    }
                }
            }
            q.push(Point(i, j, matrix[i][j]));
        }
        if (q.size() >= 3) {
            SetZero();
        }
        while (!q.empty()) {
            q.pop();
        }
    }

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if (!q.empty()) {
                Point back = q.back();
                if (matrix[i][j] != back.data) {
                    if (q.size() >= 3) {
                        SetZero();
                    }
                    while (!q.empty()) {
                        q.pop();
                    }
                }
            }
            q.push(Point(i, j, matrix[i][j]));
        }
        if (q.size() >= 3) {
            SetZero();
        }
        while (!q.empty()) {
            q.pop();
        }
    }
}
void print() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << copyM[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    init();
    Elimination();
    print();
    return 0;
}