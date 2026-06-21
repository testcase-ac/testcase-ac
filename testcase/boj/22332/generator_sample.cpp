#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static void applyRect(vector<vector<int>>& grid, int top, int left, int bottom, int right) {
    for (int row = top; row <= bottom; ++row) {
        for (int col = left; col <= right; ++col) {
            grid[row][col] ^= 1;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 5 + rnd.wnext(16, -2);
    vector<vector<int>> grid(n, vector<int>(n, 0));

    if (mode == 0) {
        int ops = rnd.next(1, 8);
        for (int i = 0; i < ops; ++i) {
            int r1 = rnd.next(0, n - 1);
            int r2 = rnd.next(r1, n - 1);
            int c1 = rnd.next(0, n - 1);
            int c2 = rnd.next(c1, n - 1);
            applyRect(grid, r1, c1, r2, c2);
        }
    } else if (mode == 1) {
        int rowStep = rnd.next(1, 3);
        int colStep = rnd.next(1, 3);
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                grid[row][col] = ((row / rowStep) + (col / colStep)) % 2;
            }
        }
    } else if (mode == 2) {
        int bands = rnd.next(1, min(5, n));
        for (int i = 0; i < bands; ++i) {
            if (rnd.next(0, 1) == 0) {
                int row = rnd.next(0, n - 1);
                applyRect(grid, row, 0, row, n - 1);
            } else {
                int col = rnd.next(0, n - 1);
                applyRect(grid, 0, col, n - 1, col);
            }
        }
    } else if (mode == 3) {
        int points = rnd.next(1, min(n * n, 12));
        for (int i = 0; i < points; ++i) {
            int row = rnd.next(0, n - 1);
            int col = rnd.next(0, n - 1);
            grid[row][col] ^= 1;
        }
    } else if (mode == 4) {
        int margin = rnd.next(0, n / 2 - 1);
        applyRect(grid, margin, margin, n - 1 - margin, n - 1 - margin);
        if (n - 2 * margin >= 5) {
            applyRect(grid, margin + 1, margin + 1, n - 2 - margin, n - 2 - margin);
        }
    } else {
        double blackProbability = rnd.next(0.15, 0.85);
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                grid[row][col] = rnd.next() < blackProbability;
            }
        }
    }

    println(n);
    for (int row = 0; row < n; ++row) {
        println(grid[row]);
    }

    return 0;
}
