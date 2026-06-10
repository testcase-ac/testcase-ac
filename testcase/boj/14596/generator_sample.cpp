#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampPixel(int value) {
    return max(0, min(255, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int h = rnd.next(1, 10);
    int w = rnd.next(1, 10);

    if (mode == 1) {
        h = rnd.next(1, 3);
        w = rnd.next(1, 10);
    } else if (mode == 2) {
        h = rnd.next(8, 10);
        w = rnd.next(1, 4);
    } else if (mode == 3) {
        h = rnd.next(4, 10);
        w = rnd.next(4, 10);
    }

    vector<vector<int>> b1(h, vector<int>(w));
    vector<vector<int>> b2(h, vector<int>(w));

    if (mode == 0) {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                b1[i][j] = rnd.next(0, 255);
                b2[i][j] = rnd.next(0, 255);
            }
        }
    } else if (mode == 1) {
        int base = rnd.next(0, 255);
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                b1[i][j] = clampPixel(base + rnd.next(-8, 8));
                b2[i][j] = clampPixel(b1[i][j] + rnd.next(-2, 2));
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < h; ++i) {
            int split = rnd.next(0, w - 1);
            for (int j = 0; j < w; ++j) {
                int low = rnd.next(0, 30);
                int high = rnd.next(225, 255);
                b1[i][j] = j <= split ? low : high;
                b2[i][j] = j <= split ? high : low;
            }
        }
    } else if (mode == 3) {
        int seam = rnd.next(0, w - 1);
        for (int i = 0; i < h; ++i) {
            seam += rnd.next(-1, 1);
            seam = max(0, min(w - 1, seam));
            for (int j = 0; j < w; ++j) {
                int value = rnd.next(20, 235);
                int penalty = min(255, 30 + 35 * abs(j - seam) + rnd.next(0, 20));
                b1[i][j] = value;
                b2[i][j] = j == seam ? clampPixel(value + rnd.next(-1, 1))
                                      : clampPixel(value + (rnd.next(0, 1) ? penalty : -penalty));
            }
        }
    } else {
        int rowStep = rnd.next(0, 12);
        int colStep = rnd.next(0, 12);
        int offset = rnd.next(-40, 40);
        int base = rnd.next(0, 255);
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                b1[i][j] = (base + rowStep * i + colStep * j) % 256;
                b2[i][j] = clampPixel(b1[i][j] + offset + rnd.next(-10, 10));
            }
        }
    }

    println(h, w);
    for (int i = 0; i < h; ++i) {
        println(b1[i]);
    }
    for (int i = 0; i < h; ++i) {
        println(b2[i]);
    }

    return 0;
}
