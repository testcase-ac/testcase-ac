#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = rnd.next(3, 32);
    } else if (mode == 1) {
        n = rnd.next(3, 10);
    } else if (mode == 5) {
        n = rnd.next(20, 32);
    } else {
        n = rnd.next(5, 18);
    }

    vector<vector<int>> grid(n, vector<int>(n, 0));

    if (mode == 1) {
        double wallProb = rnd.next(0.05, 0.45);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                grid[r][c] = rnd.next() < wallProb;
            }
        }
    } else if (mode == 2) {
        double wallProb = rnd.next(0.25, 0.70);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                grid[r][c] = rnd.next() < wallProb;
            }
        }
        int turnRow = rnd.next(1, n - 1);
        for (int c = 0; c < n; ++c) grid[0][c] = 0;
        for (int r = 0; r <= turnRow; ++r) grid[r][n - 1] = 0;
        for (int c = 1; c < n; ++c) grid[turnRow][c] = 0;
    } else if (mode == 3) {
        for (int r = 1; r < n; ++r) {
            int gap = rnd.next(n);
            for (int c = 0; c < n; ++c) {
                if ((r + c) % 3 == 0 && c != gap) grid[r][c] = 1;
            }
        }
    } else if (mode == 4) {
        int phase = rnd.next(2);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (((r + c + phase) % 2) == 0 && rnd.next(100) < 75) {
                    grid[r][c] = 1;
                }
            }
        }
    } else if (mode == 5) {
        double wallProb = rnd.next(0.0, 0.12);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                grid[r][c] = rnd.next() < wallProb;
            }
        }
    }

    grid[0][0] = 0;
    grid[0][1] = 0;

    println(n);
    for (const auto& row : grid) {
        println(row);
    }

    return 0;
}
