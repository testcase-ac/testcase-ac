#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_G = 2000000;

int clampedHeight(long long value) {
    return static_cast<int>(max(0LL, min<long long>(MAX_G, value)));
}

vector<vector<int>> makeGrid(int r, int c, int mode) {
    vector<vector<int>> g(r, vector<int>(c, 0));

    if (mode == 0) {
        int hi = rnd.next(0, 12);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                g[i][j] = rnd.next(0, hi);
            }
        }
    } else if (mode == 1) {
        int peakR = rnd.next(0, r - 1);
        int peakC = rnd.next(0, c - 1);
        int peak = rnd.next(8, 40);
        if (rnd.next(4) == 0) peak = MAX_G;
        int slope = rnd.next(0, 3);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                int dist = abs(i - peakR) + abs(j - peakC);
                g[i][j] = clampedHeight(peak - 1LL * slope * dist);
            }
        }
    } else if (mode == 2) {
        int base = rnd.next(0, 20);
        int step = rnd.next(0, 6);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                g[i][j] = clampedHeight(base + 1LL * step * (i + j));
            }
        }
    } else if (mode == 3) {
        int low = rnd.next(0, 5);
        int high = rnd.next(10, 50);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                g[i][j] = ((i + j + rnd.next(2)) % 2 == 0) ? low : high;
            }
        }
    } else {
        int high = rnd.next(20, 80);
        if (rnd.next(5) == 0) high = MAX_G;
        int low = rnd.next(0, 3);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                bool border = i == 0 || i == r - 1 || j == 0 || j == c - 1;
                g[i][j] = border ? high : low;
            }
        }
    }

    return g;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int r = rnd.next(1, 8);
        int c = rnd.next(1, 8);

        if (mode == 3 && r == 1 && c == 1) {
            c = 2;
        }
        if (rnd.next(6) == 0) {
            if (rnd.next(2) == 0) r = 1;
            else c = 1;
        }

        vector<vector<int>> g = makeGrid(r, c, mode);

        println(r, c);
        for (int i = 0; i < r; ++i) {
            println(g[i]);
        }
    }

    return 0;
}
