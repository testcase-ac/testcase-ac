#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int clampCell(int value) {
    return max(1, min(15, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int shapeMode = rnd.next(6);
    int n, m;
    if (shapeMode == 0) {
        n = rnd.next(2, 4);
        m = rnd.next(2, 4);
    } else if (shapeMode == 1) {
        n = rnd.next(2, 5);
        m = rnd.next(6, 8);
    } else if (shapeMode == 2) {
        n = rnd.next(12, 20);
        m = rnd.next(2, 4);
    } else if (shapeMode == 3) {
        n = rnd.next(6, 12);
        m = rnd.next(5, 8);
    } else if (shapeMode == 4) {
        n = 20;
        m = rnd.next(2, 8);
    } else {
        n = rnd.next(2, 20);
        m = 8;
    }

    int cutMode = rnd.next(5);
    int a, b;
    if (cutMode == 0) {
        a = 1;
        b = 1;
    } else if (cutMode == 1) {
        a = n - 1;
        b = m - 1;
    } else if (cutMode == 2) {
        a = rnd.next(1, min(n - 1, 3));
        b = rnd.next(1, min(m - 1, 3));
    } else if (cutMode == 3) {
        a = rnd.next(max(1, n - 4), n - 1);
        b = rnd.next(max(1, m - 3), m - 1);
    } else {
        a = rnd.next(1, n - 1);
        b = rnd.next(1, m - 1);
    }

    vector<vector<int>> grid(n, vector<int>(m));
    int pattern = rnd.next(7);
    int base = rnd.next(1, 15);
    int rowStep = rnd.next(0, 3);
    int colStep = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int value;
            if (pattern == 0) {
                value = base;
            } else if (pattern == 1) {
                value = base + i * rowStep + j * colStep;
            } else if (pattern == 2) {
                value = ((i + j) % 2 == 0) ? rnd.next(10, 15) : rnd.next(1, 6);
            } else if (pattern == 3) {
                value = (i % 2 == 0) ? rnd.next(8, 15) : rnd.next(1, 7);
            } else if (pattern == 4) {
                value = (j % 2 == 0) ? rnd.next(8, 15) : rnd.next(1, 7);
            } else if (pattern == 5) {
                int rowBand = i / rnd.next(1, 4);
                int colBand = j / rnd.next(1, 3);
                value = 1 + ((rowBand * 5 + colBand * 3 + base) % 15);
            } else {
                int low = rnd.next(1, 10);
                int high = rnd.next(low, 15);
                value = rnd.next(low, high);
            }
            grid[i][j] = clampCell(value);
        }
    }

    println(n, m);
    println(a, b);
    for (const auto& row : grid) {
        println(row);
    }

    return 0;
}
