#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static char flip(char ch) {
    return ch == 'R' ? 'B' : 'R';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int r = rnd.next(2, 15);
    int c = rnd.next(2, 15);

    if (mode == 1 && rnd.next(2) == 0) {
        r = rnd.next(2, 6);
        c = rnd.next(2, 6);
    } else if (mode == 2) {
        r = rnd.next(10, 15);
        c = rnd.next(10, 15);
    }

    vector<string> grid(r, string(c, 'R'));
    char base = rnd.next(2) ? 'R' : 'B';

    if (mode == 0) {
        double blueProb = rnd.next(0.15, 0.85);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                grid[i][j] = rnd.next() < blueProb ? 'B' : 'R';
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                grid[i][j] = ((i + j) % 2 == 0) ? base : flip(base);
            }
        }
    } else if (mode == 2) {
        bool byRows = rnd.next(2);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                int stripe = byRows ? i : j;
                grid[i][j] = (stripe % 2 == 0) ? base : flip(base);
            }
        }
    } else if (mode == 3) {
        int period = rnd.next(2, 5);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                grid[i][j] = ((i + j) % period == 0) ? flip(base) : base;
            }
        }
    } else if (mode == 4) {
        int flips = rnd.next(1, r * c / 2);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                grid[i][j] = base;
            }
        }
        for (int k = 0; k < flips; ++k) {
            int i = rnd.next(r);
            int j = rnd.next(c);
            grid[i][j] = flip(grid[i][j]);
        }
    } else if (mode == 5) {
        int splitRow = rnd.next(1, r - 1);
        int splitCol = rnd.next(1, c - 1);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                bool lowerRight = i >= splitRow && j >= splitCol;
                grid[i][j] = lowerRight ? flip(base) : base;
            }
        }
    } else {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                grid[i][j] = (i * 2 + j * 3 + rnd.next(3)) % 2 ? 'R' : 'B';
            }
        }
    }

    if (rnd.next(3) == 0) {
        grid[0][0] = grid[r - 1][c - 1];
    } else if (rnd.next(2) == 0) {
        grid[r - 1][c - 1] = flip(grid[0][0]);
    }

    println(r, c);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
