#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int dist1(int r1, int c1, int r2, int c2) {
    return abs(r1 - r2) + abs(c1 - c2);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = 1, m = 1;
    if (mode == 0) {
        n = 1;
        m = rnd.next(2, 18);
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = n;
    } else if (mode == 3) {
        n = rnd.next(3, 10);
        m = rnd.next(3, 10);
    } else if (mode == 4) {
        n = rnd.next(4, 14);
        m = rnd.next(4, 14);
    } else {
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
    }

    int rf = rnd.next(1, n);
    int cf = rnd.next(1, m);
    int rh = rnd.next(1, n);
    int ch = rnd.next(1, m);
    if (mode == 2 && rnd.next(2) == 0) {
        rh = rf;
        ch = cf;
    }

    vector<vector<int>> a(n, vector<int>(m, 1));
    int fillMode = rnd.next(5);
    int maxDim = max(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int value = 1;
            if (fillMode == 0) {
                value = 1;
            } else if (fillMode == 1) {
                value = maxDim + rnd.next(0, 6);
            } else if (fillMode == 2) {
                value = rnd.next(1, max(1, maxDim));
            } else if (fillMode == 3) {
                value = (i + j) % max(1, maxDim) + 1;
            } else {
                int toHome = dist1(i + 1, j + 1, rh, ch);
                value = max(1, min(1000, toHome + rnd.next(-1, 1)));
            }
            a[i][j] = min(1000, max(1, value));
        }
    }

    if (rnd.next(2) == 0) {
        a[rf - 1][cf - 1] = max(1, dist1(rf, cf, rh, ch));
    }
    if (n > 1 && rnd.next(2) == 0) {
        int col = rnd.next(0, m - 1);
        for (int i = 0; i < n; ++i) a[i][col] = 1;
    }
    if (m > 1 && rnd.next(2) == 0) {
        int row = rnd.next(0, n - 1);
        for (int j = 0; j < m; ++j) a[row][j] = 1;
    }

    println(n, m);
    println(rf, cf, rh, ch);
    for (int i = 0; i < n; ++i) println(a[i]);

    return 0;
}
