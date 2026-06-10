#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else if (mode == 2) {
        n = rnd.next(4, 8);
    } else {
        n = rnd.next(6, 14);
    }

    vector<vector<int>> w(n, vector<int>(n));
    int lo = rnd.next(1, 5);
    int hi = rnd.next(lo, 9);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mode == 0) {
                w[i][j] = rnd.next(0, 9);
            } else if (mode == 1) {
                w[i][j] = rnd.next() < 0.65 ? 0 : rnd.next(lo, hi);
            } else if (mode == 2) {
                w[i][j] = rnd.next() < 0.20 ? 0 : rnd.next(lo, hi);
            } else if (mode == 3) {
                w[i][j] = (i == j || i + j == n - 1) ? rnd.next(lo, hi) : 0;
            } else if (mode == 4) {
                int block = max(1, n / rnd.next(2, 4));
                w[i][j] = ((i / block + j / block) % 2 == 0) ? rnd.next(lo, hi) : 0;
                if (rnd.next() < 0.15) {
                    w[i][j] = 0;
                }
            } else {
                w[i][j] = rnd.next() < 0.45 ? 0 : rnd.next(lo, hi);
                if ((i == 0 || j == 0 || i == n - 1 || j == n - 1) && rnd.next() < 0.70) {
                    w[i][j] = rnd.next(lo, hi);
                }
            }
        }
    }

    int zeroCount = 0;
    for (const auto& row : w) {
        zeroCount += count(row.begin(), row.end(), 0);
    }

    int kLimit = rnd.next(1, 30);
    int k;
    if (zeroCount == 0) {
        k = rnd.next(1, kLimit);
    } else if (mode == 1 || mode == 3) {
        k = rnd.next(1, min(kLimit, max(1, zeroCount / 2)));
    } else {
        k = rnd.next(1, min(kLimit, zeroCount + 5));
    }

    vector<int> d(k);
    int blueprintMode = rnd.next(0, 3);
    for (int i = 0; i < k; ++i) {
        if (blueprintMode == 0) {
            d[i] = rnd.next(1, 9);
        } else if (blueprintMode == 1) {
            d[i] = rnd.next(6, 9);
        } else if (blueprintMode == 2) {
            d[i] = rnd.next(1, 4);
        } else {
            d[i] = (i % 2 == 0) ? rnd.next(8, 9) : rnd.next(1, 2);
        }
    }
    shuffle(d.begin(), d.end());

    println(n);
    for (const auto& row : w) {
        println(row);
    }
    println(k);
    println(d);

    return 0;
}
