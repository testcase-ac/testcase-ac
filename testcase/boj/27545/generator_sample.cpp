#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int h;
    int w;
    if (mode == 0) {
        h = 1;
        w = rnd.next(2, 18);
    } else if (mode == 1) {
        h = 2;
        w = rnd.next(2, 16);
    } else {
        h = rnd.next(3, 9);
        w = rnd.next(2, 14);
    }

    vector<vector<int>> a(h, vector<int>(w));
    vector<int> palette;
    int paletteSize = rnd.next(2, 8);
    for (int i = 0; i < paletteSize; ++i) {
        if (i == 0 && rnd.next(0, 3) == 0) {
            palette.push_back(1);
        } else if (i == 1 && rnd.next(0, 3) == 0) {
            palette.push_back(1000000000);
        } else {
            palette.push_back(rnd.next(1, 1000000000));
        }
    }

    if (mode == 0) {
        int value = rnd.any(palette);
        for (int j = 0; j < w; ++j) {
            if (j == 0 || rnd.next(0, 99) < 45) {
                value = rnd.any(palette);
            }
            a[0][j] = value;
        }
    } else if (mode == 1) {
        for (int j = 0; j < w; ++j) {
            int top = rnd.any(palette);
            int bottom = (rnd.next(0, 99) < 55) ? top : rnd.any(palette);
            a[0][j] = top;
            a[1][j] = bottom;
            if (j > 0 && rnd.next(0, 99) < 35) {
                a[0][j] = a[0][j - 1];
            }
            if (j > 0 && rnd.next(0, 99) < 35) {
                a[1][j] = a[1][j - 1];
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < h; ++i) {
            int value = rnd.any(palette);
            for (int j = 0; j < w; ++j) {
                if (j == 0 || rnd.next(0, 99) < 25) {
                    value = rnd.any(palette);
                }
                a[i][j] = value;
            }
        }
    } else if (mode == 3) {
        for (int j = 0; j < w; ++j) {
            int value = rnd.any(palette);
            for (int i = 0; i < h; ++i) {
                if (i == 0 || rnd.next(0, 99) < 25) {
                    value = rnd.any(palette);
                }
                a[i][j] = value;
            }
        }
    } else if (mode == 4) {
        int blockH = rnd.next(1, min(3, h));
        int blockW = rnd.next(1, min(4, w));
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                int key = (i / blockH + 2 * (j / blockW) + rnd.next(0, 1)) % paletteSize;
                a[i][j] = palette[key];
            }
        }
    } else {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (rnd.next(0, 99) < 70) {
                    a[i][j] = palette[(i + j) % paletteSize];
                } else {
                    a[i][j] = rnd.any(palette);
                }
            }
        }
    }

    println(h, w);
    for (int i = 0; i < h; ++i) {
        println(a[i]);
    }

    return 0;
}
