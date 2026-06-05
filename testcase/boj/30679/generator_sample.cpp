#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int>> randomGrid(int n, int m, int lo, int hi) {
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] = rnd.next(lo, hi);
        }
    }
    return a;
}

void printGrid(const vector<vector<int>>& a) {
    println((int)a.size(), (int)a[0].size());
    for (const auto& row : a) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m;
    vector<vector<int>> a;

    if (mode == 0) {
        n = rnd.next(1, 6);
        m = rnd.next(1, 6);
        int maxValue = min(n, m);
        a = randomGrid(n, m, 1, maxValue);
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        m = rnd.next(2, 10);
        a.assign(n, vector<int>(m, 1));
        int maxValue = min(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next(0, 4) == 0) {
                    a[i][j] = rnd.next(1, maxValue);
                }
            }
        }
    } else if (mode == 2) {
        if (rnd.next(0, 1) == 0) {
            n = 1;
            m = rnd.next(1, 100);
        } else {
            n = rnd.next(1, 100);
            m = 1;
        }
        a.assign(n, vector<int>(m, 1));
    } else if (mode == 3) {
        n = rnd.next(2, 15);
        m = rnd.next(2, 15);
        int maxValue = min(n, m);
        a.assign(n, vector<int>(m, 1));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int span = 1 + ((i + j + rnd.next(0, maxValue - 1)) % maxValue);
                a[i][j] = span;
            }
        }
    } else if (mode == 4) {
        n = rnd.next(8, 25);
        m = rnd.next(8, 25);
        int maxValue = min(n, m);
        a = randomGrid(n, m, 1, maxValue);
        for (int i = 0; i < n; ++i) {
            a[i][0] = rnd.next(1, maxValue);
        }
    } else {
        n = rnd.next(20, 100);
        m = rnd.next(20, 100);
        int maxValue = min(n, m);
        int upper = rnd.next(1, maxValue);
        a = randomGrid(n, m, 1, upper);
    }

    printGrid(a);
    return 0;
}
