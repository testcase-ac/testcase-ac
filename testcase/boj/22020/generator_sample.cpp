#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int h, w, s;
    int maxColor = 256;

    if (mode == 0) {
        h = 1;
        w = rnd.next(2, 20);
        s = rnd.next(1, w);
        maxColor = rnd.next(2, 12);
    } else if (mode == 1) {
        h = rnd.next(2, 6);
        w = rnd.next(2, 6);
        s = 1;
        maxColor = rnd.next(2, 20);
    } else if (mode == 2) {
        h = rnd.next(3, 10);
        w = rnd.next(3, 10);
        s = h * w;
        maxColor = rnd.next(2, 40);
    } else if (mode == 3) {
        h = rnd.next(5, 12);
        w = rnd.next(5, 12);
        int rectH = rnd.next(1, h);
        int rectW = rnd.next(1, w);
        s = rnd.next(1, rectH * rectW);
        maxColor = rnd.next(2, 8);
    } else if (mode == 4) {
        h = rnd.next(8, 18);
        w = rnd.next(8, 18);
        s = rnd.next(1, min(h * w, rnd.next(10, 80)));
        maxColor = rnd.next(30, 256);
    } else {
        h = rnd.next(2, 16);
        w = rnd.next(2, 16);
        s = rnd.next(1, h * w);
        maxColor = rnd.next(2, 256);
    }

    vector<vector<int>> a(h, vector<int>(w));
    int pattern = rnd.next(0, 4);

    if (pattern == 0) {
        int base = rnd.next(1, maxColor);
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                a[i][j] = base;
            }
        }
        int changes = rnd.next(1, max(1, h * w / 3));
        for (int k = 0; k < changes; ++k) {
            a[rnd.next(0, h - 1)][rnd.next(0, w - 1)] = rnd.next(1, maxColor);
        }
    } else if (pattern == 1) {
        for (int i = 0; i < h; ++i) {
            int rowColor = rnd.next(1, maxColor);
            for (int j = 0; j < w; ++j) {
                a[i][j] = rowColor;
            }
        }
    } else if (pattern == 2) {
        for (int j = 0; j < w; ++j) {
            int colColor = rnd.next(1, maxColor);
            for (int i = 0; i < h; ++i) {
                a[i][j] = colColor;
            }
        }
    } else if (pattern == 3) {
        int splitR = rnd.next(0, h - 1);
        int splitC = rnd.next(0, w - 1);
        int c1 = rnd.next(1, maxColor);
        int c2 = rnd.next(1, maxColor);
        int c3 = rnd.next(1, maxColor);
        int c4 = rnd.next(1, maxColor);
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (i <= splitR && j <= splitC) {
                    a[i][j] = c1;
                } else if (i <= splitR) {
                    a[i][j] = c2;
                } else if (j <= splitC) {
                    a[i][j] = c3;
                } else {
                    a[i][j] = c4;
                }
            }
        }
    } else {
        int low = rnd.next(1, maxColor);
        int high = rnd.next(low, maxColor);
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                a[i][j] = rnd.next(low, high);
            }
        }
    }

    println(h, w, s);
    for (int i = 0; i < h; ++i) {
        println(a[i]);
    }

    return 0;
}
