#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> randomRow(int m, int lo, int hi) {
    vector<int> row(m);
    for (int j = 0; j < m; ++j) row[j] = rnd.next(lo, hi);
    return row;
}

static vector<int> alternatingRow(int m, int a, int b) {
    vector<int> row(m);
    for (int j = 0; j < m; ++j) row[j] = (j % 2 == 0 ? a : b);
    return row;
}

static vector<int> monotoneRow(int m, bool increasing, int start, int step) {
    vector<int> row(m);
    for (int j = 0; j < m; ++j) {
        int offset = increasing ? j : m - 1 - j;
        row[j] = min(1000, start + offset * step);
    }
    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 8);
    int m = rnd.next(1, 8);
    vector<vector<int>> a;

    if (mode == 0) {
        n = rnd.next(1, 6);
        m = rnd.next(1, 7);
        int hi = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) a.push_back(randomRow(m, 1, hi));
    } else if (mode == 1) {
        n = rnd.next(1, 5) * 2;
        m = rnd.next(1, 8);
        for (int i = 0; i < n; i += 2) {
            vector<int> row = randomRow(m, 1, rnd.next(3, 30));
            a.push_back(row);
            a.push_back(row);
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        n = rnd.next(1, 7);
        m = rnd.next(2, 9);
        for (int i = 0; i < n; ++i) {
            bool increasing = rnd.next(0, 1);
            int start = rnd.next(1, 12);
            int step = rnd.next(1, 6);
            a.push_back(monotoneRow(m, increasing, start, step));
        }
    } else if (mode == 3) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(1, 1000);
            int y = rnd.next(1, 1000);
            a.push_back(alternatingRow(m, x, y));
        }
    } else if (mode == 4) {
        n = rnd.next(1, 4);
        m = rnd.next(8, 20);
        for (int i = 0; i < n; ++i) a.push_back(randomRow(m, 1, 1000));
    } else if (mode == 5) {
        n = rnd.next(8, 20);
        m = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) a.push_back(randomRow(m, 1, 1000));
    } else if (mode == 6) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            vector<int> row(m);
            for (int j = 0; j < m; ++j) row[j] = rnd.any(vector<int>{1, 2, 999, 1000});
            a.push_back(row);
        }
    } else {
        n = rnd.next(1, 6);
        m = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int base = rnd.next(1, 15);
            vector<int> row(m);
            for (int j = 0; j < m; ++j) row[j] = max(1, base + rnd.next(-2, 2));
            a.push_back(row);
        }
    }

    println(n, m);
    for (const auto& row : a) println(row);

    return 0;
}
