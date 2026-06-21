#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampHeight(int value) {
    return max(1, min(50, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int m, n;
    vector<vector<int>> height;

    if (mode == 0) {
        m = rnd.next(1, 5);
        n = rnd.next(1, 5);
        int h = rnd.next(1, 50);
        height.assign(m, vector<int>(n, h));
    } else if (mode == 1) {
        m = rnd.next(1, 8);
        n = rnd.next(1, 8);
        int base = rnd.next(1, 8);
        height.assign(m, vector<int>(n, 1));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                height[i][j] = clampHeight(base + i + j + rnd.next(0, 2));
            }
        }
    } else if (mode == 2) {
        m = rnd.next(2, 10);
        n = rnd.next(2, 10);
        int low = rnd.next(1, 5);
        int high = rnd.next(35, 50);
        height.assign(m, vector<int>(n, 1));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                height[i][j] = ((i + j) % 2 == 0 ? low : high);
            }
        }
    } else if (mode == 3) {
        m = rnd.next(3, 12);
        n = rnd.next(3, 12);
        height.assign(m, vector<int>(n, 1));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int edge = min(min(i, m - 1 - i), min(j, n - 1 - j));
                height[i][j] = clampHeight(2 + 3 * edge + rnd.next(0, 4));
            }
        }
    } else if (mode == 4) {
        m = rnd.next(1, 50);
        n = rnd.next(1, 50);
        if (rnd.next(0, 1) == 0) {
            m = rnd.any(vector<int>{1, 2, 49, 50});
        } else {
            n = rnd.any(vector<int>{1, 2, 49, 50});
        }
        height.assign(m, vector<int>(n, 1));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                height[i][j] = rnd.next(1, 50);
            }
        }
    } else if (mode == 5) {
        m = rnd.next(2, 15);
        n = rnd.next(2, 15);
        height.assign(m, vector<int>(n, 1));
        int ridgeRow = rnd.next(0, m - 1);
        int ridgeCol = rnd.next(0, n - 1);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int distance = abs(i - ridgeRow) + abs(j - ridgeCol);
                height[i][j] = clampHeight(50 - 4 * distance + rnd.next(-2, 2));
            }
        }
    } else {
        m = rnd.next(4, 18);
        n = rnd.next(4, 18);
        height.assign(m, vector<int>(n, 1));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int band = (2 * i + 3 * j + rnd.next(0, 5)) % 11;
                height[i][j] = rnd.next(1, 6) + band * rnd.next(1, 4);
            }
        }
    }

    println(m, n);
    for (int i = 0; i < m; ++i) {
        println(height[i]);
    }

    return 0;
}
