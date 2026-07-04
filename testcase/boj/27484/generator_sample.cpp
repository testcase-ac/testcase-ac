#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 22);
    int k;
    if (mode == 0) {
        k = 1;
    } else if (mode == 1) {
        k = n;
    } else {
        k = rnd.next(1, n);
    }

    vector<string> grid(n, string(n, 'W'));

    auto paintRect = [&](int r1, int c1, int r2, int c2, char ch) {
        r1 = max(r1, 0);
        c1 = max(c1, 0);
        r2 = min(r2, n - 1);
        c2 = min(c2, n - 1);
        for (int r = r1; r <= r2; ++r) {
            for (int c = c1; c <= c2; ++c) {
                grid[r][c] = ch;
            }
        }
    };

    if (mode == 0) {
        double blackProb = rnd.next(0.15, 0.55);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (rnd.next() < blackProb) grid[r][c] = 'B';
            }
        }
    } else if (mode == 1) {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (rnd.next(0, 1)) grid[r][c] = 'B';
            }
        }
    } else if (mode == 2) {
        grid.assign(n, string(n, 'B'));
    } else if (mode == 3) {
        grid.assign(n, string(n, 'W'));
    } else if (mode == 4) {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if ((r + c + rnd.next(0, 1)) % rnd.next(2, 4) == 0) {
                    grid[r][c] = 'B';
                }
            }
        }
    } else if (mode == 5) {
        int top = rnd.next(0, n - k);
        int left = rnd.next(0, n - k);
        paintRect(top, left, top + k - 1, left + k - 1, 'B');
        int extra = rnd.next(0, n);
        for (int i = 0; i < extra; ++i) {
            grid[rnd.next(n)][rnd.next(n)] = 'B';
        }
    } else if (mode == 6) {
        int rows = rnd.next(1, n);
        int cols = rnd.next(1, n);
        for (int i = 0; i < rows; ++i) {
            int r = rnd.next(n);
            int l = rnd.next(n);
            int rr = rnd.next(l, n - 1);
            paintRect(r, l, r, rr, 'B');
        }
        for (int i = 0; i < cols; ++i) {
            int c = rnd.next(n);
            int t = rnd.next(n);
            int b = rnd.next(t, n - 1);
            paintRect(t, c, b, c, 'B');
        }
    } else {
        int blockCount = rnd.next(1, 5);
        for (int i = 0; i < blockCount; ++i) {
            int h = rnd.next(1, min(n, k + 2));
            int w = rnd.next(1, min(n, k + 2));
            int r = rnd.next(0, n - h);
            int c = rnd.next(0, n - w);
            paintRect(r, c, r + h - 1, c + w - 1, 'B');
        }
    }

    println(n, k);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
