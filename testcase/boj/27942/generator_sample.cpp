#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 4;
    } else if (mode == 1) {
        n = 6;
    } else {
        n = 2 * rnd.next(2, 11);
    }

    vector<vector<int>> a(n, vector<int>(n, 0));
    int centerLo = n / 2 - 1;
    int centerHi = n / 2;

    auto inCenter = [&](int r, int c) {
        return centerLo <= r && r <= centerHi && centerLo <= c && c <= centerHi;
    };

    int low = rnd.next(-25, 0);
    int high = rnd.next(1, 25);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (inCenter(r, c)) continue;

            if (mode == 0) {
                a[r][c] = rnd.next(-3, 3);
            } else if (mode == 1) {
                int dist = max(abs(r - centerLo), abs(c - centerLo));
                a[r][c] = (dist % 2 == 0 ? high : low);
            } else if (mode == 2) {
                a[r][c] = (r < n / 2 ? rnd.next(0, 25) : rnd.next(-25, 12));
            } else if (mode == 3) {
                a[r][c] = (c >= n / 2 ? rnd.next(0, 25) : rnd.next(-25, 12));
            } else if (mode == 4) {
                a[r][c] = rnd.next(-25, 25);
            } else {
                int stripe = (r + c + rnd.next(0, 2)) % 3;
                a[r][c] = stripe == 0 ? rnd.next(10, 25) : rnd.next(-25, 8);
            }
        }
    }

    int rings = rnd.next(0, n / 2 - 1);
    for (int d = 1; d <= rings; ++d) {
        int top = centerLo - d;
        int bottom = centerHi + d;
        int left = centerLo - d;
        int right = centerHi + d;
        int bias = rnd.next(-10, 15);

        if (top >= 0) {
            for (int c = left + 1; c < right; ++c) {
                if (!inCenter(top, c)) a[top][c] = clamp(a[top][c] + bias, -25, 25);
            }
        }
        if (bottom < n) {
            for (int c = left + 1; c < right; ++c) {
                if (!inCenter(bottom, c)) a[bottom][c] = clamp(a[bottom][c] - bias, -25, 25);
            }
        }
        if (left >= 0) {
            for (int r = top; r <= bottom; ++r) {
                if (!inCenter(r, left)) a[r][left] = clamp(a[r][left] + rnd.next(-8, 12), -25, 25);
            }
        }
        if (right < n) {
            for (int r = top; r <= bottom; ++r) {
                if (!inCenter(r, right)) a[r][right] = clamp(a[r][right] + rnd.next(-12, 8), -25, 25);
            }
        }
    }

    println(n);
    for (int r = 0; r < n; ++r) {
        println(a[r]);
    }

    return 0;
}
