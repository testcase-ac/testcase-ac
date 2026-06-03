#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int randomWeight(int mode, int i, int j, int n, int m, int x, int y) {
    if (mode == 0) return rnd.next(0, 100);
    if (mode == 1) return ((i + j) % 2 == 0) ? rnd.next(70, 100) : rnd.next(0, 20);
    if (mode == 2) return min(100, abs(i - x) * rnd.next(6, 14) + abs(j - y) * rnd.next(6, 14));
    if (mode == 3) return (i == x || j == y) ? rnd.next(60, 100) : rnd.next(0, 35);
    if (mode == 4) return rnd.next(0, 4) == 0 ? rnd.next(80, 100) : rnd.next(0, 25);
    return (i * 17 + j * 31 + n + m) % 101;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int shape = rnd.next(0, 6);
    int n, m;
    if (shape == 0) {
        n = 1;
        m = 1;
    } else if (shape == 1) {
        n = 1;
        m = rnd.next(2, 50);
    } else if (shape == 2) {
        n = rnd.next(2, 50);
        m = 1;
    } else if (shape == 3) {
        n = rnd.next(2, 6);
        m = rnd.next(2, 6);
    } else if (shape == 4) {
        n = rnd.next(7, 12);
        m = rnd.next(7, 12);
    } else if (shape == 5) {
        n = rnd.next(2, 4);
        m = rnd.next(20, 50);
    } else {
        n = rnd.next(20, 50);
        m = rnd.next(2, 4);
    }

    int x = rnd.next(0, n - 1);
    int y = rnd.next(0, m - 1);
    int pMode = rnd.next(0, 4);
    int p;
    if (pMode == 0) {
        p = 0;
    } else if (pMode == 1) {
        p = rnd.next(1, 4);
    } else if (pMode == 2) {
        p = rnd.next(5, 12);
    } else if (pMode == 3) {
        p = rnd.next(13, 20);
    } else {
        p = rnd.any(vector<int>{0, 1, 2, 19, 20});
    }

    int weightMode = rnd.next(0, 5);
    vector<vector<int>> w(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            w[i][j] = randomWeight(weightMode, i, j, n, m, x, y);
        }
    }

    if (rnd.next(0, 3) == 0) {
        w[x][y] = rnd.any(vector<int>{0, 1, 99, 100});
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(w[i]);
    }
    println(x, y, p);

    return 0;
}
