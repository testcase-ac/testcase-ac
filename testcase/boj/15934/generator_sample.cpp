#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int r = 1;
    int c = 1;
    long long d = 1;
    long long w = 1;
    vector<vector<long long>> y;

    if (mode == 0) {
        r = rnd.next(1, 2);
        c = rnd.next(1, 6);
        d = rnd.next(1, 150);
        w = rnd.next(1, 150);
        y.assign(r, vector<long long>(c));
        long long base = rnd.next(1, 80);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                y[i][j] = base + rnd.next(0, 40);
            }
        }
    } else if (mode == 1) {
        r = rnd.next(2, 5);
        c = rnd.next(2, 5);
        d = rnd.next(1, 200);
        w = rnd.next(1, 200);
        y.assign(r, vector<long long>(c));
        long long low = rnd.next(1, 20);
        long long high = rnd.next(50, 200);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                y[i][j] = ((i + j) % 2 == 0 ? low : high) + rnd.next(0, 3);
            }
        }
    } else if (mode == 2) {
        r = rnd.next(3, 7);
        c = rnd.next(3, 7);
        d = rnd.next(1, 1000);
        w = rnd.next(1, 1000);
        y.assign(r, vector<long long>(c));
        vector<long long> levels = {1, rnd.next(2, 30), rnd.next(31, 100), rnd.next(101, 300)};
        sort(levels.begin(), levels.end());
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                y[i][j] = rnd.any(levels);
            }
        }
    } else if (mode == 3) {
        r = rnd.next(1, 6);
        c = rnd.next(1, 6);
        d = rnd.next(1, 20);
        w = rnd.next(1, 20);
        y.assign(r, vector<long long>(c));
        long long cur = rnd.next(1, 10);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                cur += rnd.next(0, 12);
                y[i][j] = cur;
            }
        }
        if (rnd.next(0, 1)) {
            reverse(y.begin(), y.end());
        }
    } else if (mode == 4) {
        r = rnd.next(4, 10);
        c = rnd.next(4, 10);
        d = rnd.next(100000000LL, 1000000000LL);
        w = rnd.next(100000000LL, 1000000000LL);
        y.assign(r, vector<long long>(c));
        vector<long long> choices = {
            1,
            rnd.next(2LL, 1000000LL),
            rnd.next(100000000LL, 999999999LL),
            1000000000LL,
        };
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                y[i][j] = rnd.any(choices);
            }
        }
    } else if (mode == 5) {
        r = rnd.next(1, 12);
        c = rnd.next(1, 12);
        d = rnd.next(1LL, 1000000000LL);
        w = rnd.next(1LL, 1000000000LL);
        y.assign(r, vector<long long>(c));
        long long same = rnd.next(1LL, 1000000000LL);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                y[i][j] = same;
            }
        }
        y[rnd.next(0, r - 1)][rnd.next(0, c - 1)] = rnd.next(1LL, 1000000000LL);
    } else {
        r = rnd.next(1, 8);
        c = rnd.next(1, 8);
        d = rnd.next(1, 5000);
        w = rnd.next(1, 5000);
        y.assign(r, vector<long long>(c));
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                y[i][j] = rnd.next(1LL, 100000LL);
            }
        }
    }

    println(r, c, d, w);
    for (int i = 0; i < r; ++i) {
        println(y[i]);
    }

    return 0;
}
