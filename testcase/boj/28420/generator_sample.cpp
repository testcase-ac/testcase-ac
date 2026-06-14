#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int valueForMode(int mode, int i, int j, int n, int m, int a, int b, int c) {
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return 1 + ((i * 3 + j * 5) % 20);
    if (mode == 2) return ((i / max(1, a) + j / max(1, b)) % 2 == 0) ? 1 : 20;
    if (mode == 3) return 1 + min(19, abs(i - n / 2) + abs(j - m / 2));
    if (mode == 4) return (i <= a || j <= c || i > n - c || j > m - b) ? 1 : 20;
    return rnd.next(1, 6);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m;
    if (mode == 0) {
        n = rnd.next(2, 6);
        m = rnd.next(2, 6);
    } else if (mode == 1) {
        n = rnd.next(7, 18);
        m = rnd.next(7, 18);
    } else if (mode == 2) {
        n = rnd.next(10, 30);
        m = rnd.next(10, 30);
    } else if (mode == 3) {
        n = rnd.next(2, 12);
        m = rnd.next(20, 45);
    } else if (mode == 4) {
        n = rnd.next(20, 45);
        m = rnd.next(2, 12);
    } else {
        n = rnd.next(12, 35);
        m = rnd.next(12, 35);
    }

    int maxSize = min(n / 2, m / 2);
    int a, b, c;
    if (mode == 0) {
        a = b = c = 1;
    } else if (mode == 1) {
        a = rnd.next(1, maxSize);
        b = rnd.next(1, maxSize);
        c = rnd.next(1, maxSize);
    } else if (mode == 2) {
        a = rnd.next(max(1, maxSize - 2), maxSize);
        b = rnd.next(1, maxSize);
        c = rnd.next(1, maxSize);
    } else if (mode == 3) {
        a = rnd.next(1, maxSize);
        b = rnd.next(max(1, maxSize - 1), maxSize);
        c = rnd.next(1, maxSize);
    } else if (mode == 4) {
        a = rnd.next(1, maxSize);
        b = rnd.next(1, maxSize);
        c = rnd.next(max(1, maxSize - 1), maxSize);
    } else {
        a = rnd.next(1, maxSize);
        b = rnd.next(1, maxSize);
        c = rnd.next(1, maxSize);
    }

    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            grid[i][j] = valueForMode(mode, i, j, n, m, a, b, c);
        }
    }

    if (mode == 5) {
        int r = rnd.next(0, n - 1);
        int col = rnd.next(0, m - 1);
        int height = rnd.next(1, min(n - r, max(1, a + max(b, c))));
        int width = rnd.next(1, min(m - col, max(1, a + b + c)));
        for (int i = r; i < r + height; ++i) {
            for (int j = col; j < col + width; ++j) {
                grid[i][j] = rnd.next(1, 3);
            }
        }
    }

    println(n, m);
    println(a, b, c);
    for (const vector<int>& row : grid) {
        println(row);
    }

    return 0;
}
