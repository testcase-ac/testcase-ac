#include "testlib.h"
#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int h = rnd.next(1, 12);
    int w = rnd.next(1, 12);
    if (mode == 4) {
        h = rnd.next(1, 4);
        w = rnd.next(1, 4);
    } else if (mode == 5) {
        h = rnd.next(8, 20);
        w = rnd.next(8, 20);
    }

    vector<vector<int>> grid(h, vector<int>(w, 0));

    if (mode == 0) {
        int wallChance = rnd.next(0, 35);
        int maxLight = rnd.next(0, 20);
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (rnd.next(0, 99) < wallChance) {
                    grid[i][j] = -1;
                } else {
                    grid[i][j] = rnd.next(0, maxLight);
                }
            }
        }
    } else if (mode == 1) {
        int si = rnd.next(0, h - 1);
        int sj = rnd.next(0, w - 1);
        int c = rnd.next(1, 30);
        int wallChance = rnd.next(0, 20);
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (rnd.next(0, 99) < wallChance && (i != si || j != sj)) {
                    grid[i][j] = -1;
                } else {
                    grid[i][j] = max(0, c - abs(i - si) - abs(j - sj));
                }
            }
        }
    } else if (mode == 2) {
        int base = rnd.next(0, 12);
        int wallChance = rnd.next(5, 30);
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (rnd.next(0, 99) < wallChance) {
                    grid[i][j] = -1;
                } else {
                    grid[i][j] = max(0, base + i - j + rnd.next(-1, 1));
                }
            }
        }
    } else if (mode == 3) {
        int plateau = rnd.next(1, 25);
        int wallChance = rnd.next(0, 25);
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (rnd.next(0, 99) < wallChance) {
                    grid[i][j] = -1;
                } else if (rnd.next(0, 9) == 0) {
                    grid[i][j] = rnd.next(0, plateau);
                } else {
                    grid[i][j] = plateau;
                }
            }
        }
    } else if (mode == 4) {
        int values[] = {-1, 0, 1, 9999, 10000};
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                grid[i][j] = values[rnd.next(0, 4)];
            }
        }
    } else {
        int lights = rnd.next(1, 5);
        vector<int> li(lights), lj(lights), lc(lights);
        for (int k = 0; k < lights; ++k) {
            li[k] = rnd.next(0, h - 1);
            lj[k] = rnd.next(0, w - 1);
            lc[k] = rnd.next(1, 40);
        }
        int wallChance = rnd.next(0, 18);
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (rnd.next(0, 99) < wallChance) {
                    grid[i][j] = -1;
                    continue;
                }
                int best = 0;
                for (int k = 0; k < lights; ++k) {
                    best = max(best, lc[k] - abs(i - li[k]) - abs(j - lj[k]));
                }
                grid[i][j] = best;
            }
        }
    }

    println(h, w);
    for (int i = 0; i < h; ++i) {
        println(grid[i]);
    }

    return 0;
}
