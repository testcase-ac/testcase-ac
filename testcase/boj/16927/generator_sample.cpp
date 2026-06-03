#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int ringLength(int n, int m, int layer) {
    int h = n - 2 * layer;
    int w = m - 2 * layer;
    return 2 * (h + w) - 4;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = 2;
        m = rnd.next(2, 12);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        m = 2;
    } else if (mode == 2) {
        int side = rnd.next(2, 10);
        if (side % 2 == 1) ++side;
        n = side;
        m = side;
    } else if (mode == 3) {
        n = rnd.next(3, 9);
        m = rnd.next(4, 12);
        if (min(n, m) % 2 == 1) {
            if (n <= m) ++n;
            else ++m;
        }
    } else if (mode == 4) {
        n = rnd.next(8, 18);
        m = rnd.next(8, 18);
        if (min(n, m) % 2 == 1) {
            if (n <= m) ++n;
            else ++m;
        }
    } else {
        vector<pair<int, int>> shapes = {
            {2, 3}, {2, 17}, {3, 2}, {4, 5}, {5, 4},
            {6, 7}, {7, 6}, {8, 17}, {10, 11}, {12, 13}
        };
        pair<int, int> shape = rnd.any(shapes);
        n = shape.first;
        m = shape.second;
    }
    if (min(n, m) % 2 == 1) {
        if (n < m) ++n;
        else ++m;
    }

    int outerCycle = ringLength(n, m, 0);
    int rMode = rnd.next(0, 5);
    int r;
    if (rMode == 0) {
        r = rnd.next(1, min(outerCycle + 3, 50));
    } else if (rMode == 1) {
        r = outerCycle;
    } else if (rMode == 2) {
        r = outerCycle + rnd.next(1, outerCycle);
    } else if (rMode == 3) {
        r = 1000000000 - rnd.next(0, 50);
    } else {
        r = rnd.next(1, 1000000000);
    }

    vector<vector<int>> a(n, vector<int>(m));
    int valueMode = rnd.next(0, 5);
    int base = rnd.next(1, 1000);
    int step = rnd.next(1, 17);
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < m; ++col) {
            if (valueMode == 0) {
                a[row][col] = base + row * m + col;
            } else if (valueMode == 1) {
                a[row][col] = 1 + ((row + col) % rnd.next(2, 5));
            } else if (valueMode == 2) {
                a[row][col] = rnd.next(1, 30);
            } else if (valueMode == 3) {
                a[row][col] = (row % 2 == 0) ? rnd.next(1, 20) : rnd.next(99999980, 100000000);
            } else if (valueMode == 4) {
                a[row][col] = min(100000000, base + (row + 1) * (col + 1) * step);
            } else {
                a[row][col] = rnd.any(vector<int>{1, 2, 3, 99999999, 100000000});
            }
        }
    }

    println(n, m, r);
    for (const auto& row : a) {
        println(row);
    }

    return 0;
}
