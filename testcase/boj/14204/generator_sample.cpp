#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

vector<vector<int>> sortedTable(int n, int m) {
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] = i * m + j + 1;
        }
    }
    return a;
}

void permuteRows(vector<vector<int>>& a) {
    shuffle(a.begin(), a.end());
}

void permuteColumns(vector<vector<int>>& a) {
    int m = int(a[0].size());
    vector<int> p(m);
    iota(p.begin(), p.end(), 0);
    shuffle(p.begin(), p.end());

    for (auto& row : a) {
        vector<int> old = row;
        for (int j = 0; j < m; ++j) {
            row[j] = old[p[j]];
        }
    }
}

void randomPermutation(vector<vector<int>>& a) {
    int n = int(a.size());
    int m = int(a[0].size());
    vector<int> values(n * m);
    iota(values.begin(), values.end(), 1);
    shuffle(values.begin(), values.end());

    int at = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] = values[at++];
        }
    }
}

void swapTwoCells(vector<vector<int>>& a) {
    int n = int(a.size());
    int m = int(a[0].size());
    int x1 = rnd.next(n);
    int y1 = rnd.next(m);
    int x2 = rnd.next(n);
    int y2 = rnd.next(m);
    while (x1 == x2 && y1 == y2) {
        x2 = rnd.next(n);
        y2 = rnd.next(m);
    }
    swap(a[x1][y1], a[x2][y2]);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 8);
    int m = rnd.next(1, 8);

    if (mode == 2) {
        n = 1;
        m = rnd.next(1, 25);
    } else if (mode == 3) {
        n = rnd.next(1, 25);
        m = 1;
    } else if (mode == 5 && rnd.next(4) == 0) {
        n = rnd.next(20, 50);
        m = rnd.next(1, 3);
    }

    vector<vector<int>> a = sortedTable(n, m);

    if (mode == 0) {
        if (rnd.next(2)) {
            permuteRows(a);
        }
        if (rnd.next(2)) {
            permuteColumns(a);
        }
    } else if (mode == 1) {
        permuteColumns(a);
        permuteRows(a);
    } else if (mode == 2 || mode == 3) {
        if (rnd.next(3) == 0) {
            randomPermutation(a);
        } else if (n * m > 1) {
            permuteRows(a);
            permuteColumns(a);
        }
    } else if (mode == 4) {
        randomPermutation(a);
    } else {
        permuteRows(a);
        permuteColumns(a);
        if (n * m > 1) {
            swapTwoCells(a);
        }
    }

    println(n, m);
    for (const auto& row : a) {
        println(row);
    }

    return 0;
}
