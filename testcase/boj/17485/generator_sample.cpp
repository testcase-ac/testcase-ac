#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampFuel(int x) {
    return max(1, min(100, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 2;
    int m = 2;

    if (mode == 0) {
        n = rnd.next(2, 4);
        m = rnd.next(2, 4);
    } else if (mode == 1) {
        n = rnd.next(2, 9);
        m = rnd.next(2, 3);
    } else if (mode == 2) {
        n = rnd.next(2, 3);
        m = rnd.next(2, 10);
    } else if (mode == 3) {
        n = rnd.next(4, 9);
        m = rnd.next(4, 9);
    } else if (mode == 4) {
        n = rnd.next(5, 12);
        m = rnd.next(2, 8);
    } else {
        n = rnd.next(2, 10);
        m = rnd.next(2, 10);
    }

    vector<vector<int>> a(n, vector<int>(m));

    if (mode == 0) {
        int value = rnd.next(1, 100);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i][j] = value;
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i][j] = (i + j) % 2 == 0 ? rnd.next(1, 8) : rnd.next(85, 100);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i][j] = (j % 3 == i % 3) ? rnd.next(1, 12) : rnd.next(45, 100);
    } else if (mode == 3) {
        int cheapCol = rnd.next(0, m - 1);
        for (int i = 0; i < n; ++i) {
            cheapCol += rnd.next(-1, 1);
            cheapCol = max(0, min(m - 1, cheapCol));
            for (int j = 0; j < m; ++j) {
                int distance = abs(j - cheapCol);
                a[i][j] = clampFuel(rnd.next(1, 7) + distance * rnd.next(12, 22));
            }
        }
    } else if (mode == 4) {
        int base = rnd.next(1, 35);
        int rowStep = rnd.next(0, 10);
        int colStep = rnd.next(-8, 8);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i][j] = clampFuel(base + i * rowStep + j * colStep + rnd.next(0, 9));
    } else if (mode == 5) {
        int lo = rnd.next(1, 80);
        int hi = rnd.next(lo, 100);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i][j] = rnd.next(lo, hi);
    } else {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i][j] = rnd.wnext(100, rnd.next(-3, 3)) + 1;
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
