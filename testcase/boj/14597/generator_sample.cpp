#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

using Matrix = vector<vector<int>>;

int clampPixel(int value) {
    return max(0, min(255, value));
}

void printMatrix(const Matrix& image) {
    for (const auto& row : image) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int h = rnd.next(1, 12);
    int w = rnd.next(1, 12);

    if (mode == 0) {
        h = 1;
    } else if (mode == 1) {
        w = 1;
    } else if (rnd.next(0, 9) == 0) {
        h = rnd.next(13, 25);
        w = rnd.next(13, 25);
    }

    Matrix b1(h, vector<int>(w));
    Matrix b2(h, vector<int>(w));

    if (mode == 0 || mode == 1) {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                b1[i][j] = rnd.next(0, 255);
                b2[i][j] = rnd.next(0, 255);
            }
        }
    } else if (mode == 2) {
        int base = rnd.next(0, 255);
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                int drift = rnd.next(-3, 3);
                b1[i][j] = clampPixel(base + drift);
                b2[i][j] = b1[i][j];
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                int bit = (i + j + rnd.next(0, 1)) % 2;
                b1[i][j] = bit ? 0 : 255;
                b2[i][j] = bit ? 255 : 0;
            }
        }
    } else if (mode == 4) {
        int start = rnd.next(0, w - 1);
        vector<int> path(h);
        path[0] = start;
        for (int i = 1; i < h; ++i) {
            path[i] = clamp(path[i - 1] + rnd.next(-1, 1), 0, w - 1);
        }

        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                b1[i][j] = rnd.next(0, 255);
                int delta = abs(j - path[i]) <= 1 ? rnd.next(-2, 2) : rnd.next(80, 160);
                if (rnd.next(0, 1)) {
                    delta = -delta;
                }
                b2[i][j] = clampPixel(b1[i][j] + delta);
            }
        }
    } else {
        int rowStep = rnd.next(-12, 12);
        int colStep = rnd.next(-12, 12);
        int offset = rnd.next(-40, 40);
        int base = rnd.next(20, 235);
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                int noise1 = rnd.next(-10, 10);
                int noise2 = rnd.next(-10, 10);
                b1[i][j] = clampPixel(base + i * rowStep + j * colStep + noise1);
                b2[i][j] = clampPixel(base + offset - i * rowStep + j * colStep + noise2);
            }
        }
    }

    println(h, w);
    printMatrix(b1);
    printMatrix(b2);

    return 0;
}
