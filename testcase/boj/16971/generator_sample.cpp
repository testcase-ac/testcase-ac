#include "testlib.h"
#include <vector>
using namespace std;

int nextValue(int mode, int i, int j, int n, int m) {
    if (mode == 0) {
        return rnd.next(-1000, 1000);
    }
    if (mode == 1) {
        return ((i + j) % 2 == 0) ? rnd.next(700, 1000) : rnd.next(-1000, -700);
    }
    if (mode == 2) {
        bool border = i == 0 || i == n - 1 || j == 0 || j == m - 1;
        if (border) return rnd.next(-1000, 1000);
        return rnd.next(-25, 25);
    }
    if (mode == 3) {
        bool corner = (i == 0 || i == n - 1) && (j == 0 || j == m - 1);
        bool edge = i == 0 || i == n - 1 || j == 0 || j == m - 1;
        if (corner) return rnd.next(800, 1000);
        if (edge) return rnd.next(-1000, -500);
        return rnd.next(500, 1000);
    }
    int base = rnd.any(vector<int>{-1000, -10, -1, 0, 1, 10, 1000});
    return rnd.next(max(-1000, base - 3), min(1000, base + 3));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int shape = rnd.next(0, 4);
    int n, m;
    if (shape == 0) {
        n = rnd.next(2, 4);
        m = rnd.next(2, 4);
    } else if (shape == 1) {
        n = 2;
        m = rnd.next(2, 12);
    } else if (shape == 2) {
        n = rnd.next(2, 12);
        m = 2;
    } else if (shape == 3) {
        n = rnd.next(3, 8);
        m = rnd.next(3, 8);
    } else {
        n = rnd.next(8, 18);
        m = rnd.next(8, 18);
    }

    int mode = rnd.next(0, 4);
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] = nextValue(mode, i, j, n, m);
        }
    }

    println(n, m);
    for (const auto& row : a) {
        println(row);
    }

    return 0;
}
