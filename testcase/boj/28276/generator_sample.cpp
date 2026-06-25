#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int r;
    int c;

    if (mode == 1) {
        r = 1;
        c = rnd.next(1, 24);
    } else if (mode == 2) {
        r = rnd.next(2, 10);
        c = 1;
    } else {
        r = rnd.next(1, 10);
        c = rnd.next(2, 16);
    }

    int w;
    if (c == 1 || mode == 0) {
        w = 0;
    } else if (mode == 3) {
        w = c - 1;
    } else if (mode == 4) {
        w = rnd.next(max(0, c / 2 - 1), c - 1);
    } else {
        w = rnd.next(0, c - 1);
    }

    vector<string> grid(r, string(c, '0'));

    if (mode == 0 || mode == 3) {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                grid[i][j] = '1';
            }
        }
    } else if (mode == 1) {
        for (int j = 0; j < c; ++j) {
            int pattern = rnd.next(0, 4);
            grid[0][j] = (pattern == 0 ? '0' : '1');
        }
    } else if (mode == 2) {
        for (int i = 0; i < r; ++i) {
            grid[i][0] = (rnd.next(0, 3) == 0 ? '0' : '1');
        }
    } else if (mode == 4) {
        int blockWidth = rnd.next(1, max(1, c / 3));
        int gap = rnd.next(1, 3);
        for (int j = 0; j < c; ++j) {
            bool inBlock = (j % (blockWidth + gap)) < blockWidth;
            for (int i = 0; i < r; ++i) {
                if (inBlock && rnd.next(0, 9) != 0) {
                    grid[i][j] = '1';
                }
            }
        }
    } else if (mode == 5) {
        int density = rnd.next(20, 85);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                grid[i][j] = (rnd.next(1, 100) <= density ? '1' : '0');
            }
        }
    } else {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                bool onDiagonal = (i + j + rnd.next(0, 1)) % 3 == 0;
                bool checker = ((i ^ j) & 1) == 0 && rnd.next(0, 4) != 0;
                grid[i][j] = (onDiagonal || checker ? '1' : '0');
            }
        }
    }

    if (rnd.next(0, 9) == 0) {
        int row = rnd.next(0, r - 1);
        int col = rnd.next(0, c - 1);
        grid[row][col] = '1';
    }

    println(r, c, w);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
