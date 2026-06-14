#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 5) {
        n = rnd.next(2, 12);
    } else {
        n = rnd.next(13, 30);
    }

    int t;
    if (mode == 2) {
        t = 0;
    } else if (mode == 7) {
        t = rnd.next(100, 500);
    } else {
        t = rnd.next(0, min(30, 500));
    }

    int r = rnd.next(1, n);
    int c = rnd.next(1, n);
    if (rnd.next(0, 4) == 0) {
        vector<pair<int, int>> targets = {{1, 1}, {1, n}, {n, 1}, {n, n}};
        auto target = rnd.any(targets);
        r = target.first;
        c = target.second;
    }

    vector<string> grid(n, string(n, '.'));

    if (mode == 0) {
        if (rnd.next(0, 1) == 1) grid[0][0] = '#';
    } else if (mode == 1) {
        // Empty grid: transformation has no usable warp moves.
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = '#';
            }
        }
    } else if (mode == 3) {
        int row = rnd.next(0, n - 1);
        int col = rnd.next(0, n - 1);
        for (int j = 0; j < n; ++j) grid[row][j] = '#';
        for (int i = 0; i < n; ++i) grid[i][col] = '#';
        if (rnd.next(0, 1) == 1) grid[0][0] = '#';
    } else if (mode == 4) {
        int parity = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i + j) % 2 == parity) grid[i][j] = '#';
            }
        }
    } else if (mode == 5) {
        int warpCount = rnd.next(1, min(n * n, max(2, n + 3)));
        for (int k = 0; k < warpCount; ++k) {
            grid[rnd.next(0, n - 1)][rnd.next(0, n - 1)] = '#';
        }
    } else if (mode == 6) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) grid[i][rnd.next(0, n - 1)] = '#';
        }
        for (int j = 0; j < n; ++j) {
            if (rnd.next(0, 2) == 0) grid[rnd.next(0, n - 1)][j] = '#';
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rnd.next(0, 99) < rnd.next(8, 35)) grid[i][j] = '#';
            }
        }
        grid[0][rnd.next(0, n - 1)] = '#';
        grid[r - 1][rnd.next(0, n - 1)] = '#';
        grid[rnd.next(0, n - 1)][c - 1] = '#';
    }

    println(n, t, r, c);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
