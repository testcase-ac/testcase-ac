#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int h = 2;
    int w = 2;

    if (mode == 0) {
        h = rnd.next(2, 4);
        w = rnd.next(2, 5);
    } else if (mode == 1) {
        h = 2;
        w = rnd.next(2, 14);
    } else if (mode == 2) {
        h = rnd.next(2, 14);
        w = 2;
    } else if (mode == 3) {
        h = rnd.next(3, 8);
        w = rnd.next(3, 8);
    } else if (mode == 4) {
        h = rnd.next(2, 6);
        w = rnd.next(9, 18);
    } else if (mode == 5) {
        h = rnd.next(9, 18);
        w = rnd.next(2, 6);
    } else if (mode == 6) {
        h = rnd.next(10, 24);
        w = rnd.next(10, 24);
    } else {
        h = rnd.next(2, 30);
        w = rnd.next(2, 30);
    }

    vector<vector<int>> grid(h, vector<int>(w));
    int paletteSize = rnd.next(1, 3);
    int rowShift = rnd.next(0, 2);
    int colShift = rnd.next(0, 2);

    if (mode == 0) {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                grid[i][j] = rnd.next(0, paletteSize - 1);
            }
        }
    } else if (mode == 1 || mode == 2) {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                grid[i][j] = (i * rowShift + j * colShift + rnd.next(0, 1)) % 3;
            }
        }
    } else if (mode == 3 || mode == 4) {
        for (int i = 0; i < h; ++i) {
            int base = rnd.next(0, 2);
            for (int j = 0; j < w; ++j) {
                grid[i][j] = (base + j + rnd.next(0, 1)) % 3;
            }
        }
    } else if (mode == 5) {
        for (int j = 0; j < w; ++j) {
            int base = rnd.next(0, 2);
            for (int i = 0; i < h; ++i) {
                grid[i][j] = (base + i + rnd.next(0, 1)) % 3;
            }
        }
    } else {
        int dominant = rnd.next(0, 2);
        int rareA = (dominant + 1) % 3;
        int rareB = (dominant + 2) % 3;
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                int roll = rnd.next(0, 99);
                if (roll < 70) {
                    grid[i][j] = dominant;
                } else if (roll < 85) {
                    grid[i][j] = rareA;
                } else {
                    grid[i][j] = rareB;
                }
            }
        }
    }

    println(h, w);
    for (int i = 0; i < h; ++i) {
        println(grid[i]);
    }

    return 0;
}
