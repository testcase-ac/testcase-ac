#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int w = rnd.next(1, 12);
    int l = rnd.next(1, 12);
    if (mode == 4) {
        w = rnd.next(2, 10);
        l = rnd.next(2, 10);
    }

    vector<vector<int>> h(l, vector<int>(w, 0));
    int base = rnd.next(0, 9999);

    if (mode == 0) {
        for (int r = 0; r < l; ++r) {
            for (int c = 0; c < w; ++c) {
                h[r][c] = base;
            }
        }
    } else if (mode == 1) {
        int rowStep = rnd.next(-20, 20);
        int colStep = rnd.next(-20, 20);
        if (rowStep == 0 && colStep == 0) {
            colStep = 1;
        }
        int offset = 250;
        for (int r = 0; r < l; ++r) {
            for (int c = 0; c < w; ++c) {
                h[r][c] = offset + r * rowStep + c * colStep;
            }
        }
    } else if (mode == 2) {
        int cr = rnd.next(0, l - 1);
        int cc = rnd.next(0, w - 1);
        int step = rnd.next(1, 30);
        bool peak = rnd.next(0, 1);
        for (int r = 0; r < l; ++r) {
            for (int c = 0; c < w; ++c) {
                int dist = abs(r - cr) + abs(c - cc);
                h[r][c] = peak ? 5000 - dist * step : 5000 + dist * step;
            }
        }
    } else if (mode == 3) {
        int low = rnd.next(0, 20);
        int high = rnd.next(9970, 9999);
        for (int r = 0; r < l; ++r) {
            for (int c = 0; c < w; ++c) {
                h[r][c] = ((r + c) % 2 == 0) ? low : high;
            }
        }
    } else if (mode == 4) {
        int blocksR = rnd.next(1, min(l, 4));
        int blocksC = rnd.next(1, min(w, 4));
        for (int r = 0; r < l; ++r) {
            for (int c = 0; c < w; ++c) {
                int br = r * blocksR / l;
                int bc = c * blocksC / w;
                h[r][c] = 100 * (br * blocksC + bc) + rnd.next(0, 2);
            }
        }
    } else {
        int lo = rnd.next(0, 9990);
        int hi = rnd.next(lo, min(9999, lo + rnd.next(0, 9)));
        for (int r = 0; r < l; ++r) {
            for (int c = 0; c < w; ++c) {
                h[r][c] = rnd.next(lo, hi);
            }
        }
    }

    for (int r = 0; r < l; ++r) {
        for (int c = 0; c < w; ++c) {
            h[r][c] = max(0, min(9999, h[r][c]));
        }
    }

    println(w, l);
    for (int r = 0; r < l; ++r) {
        println(h[r]);
    }

    return 0;
}
