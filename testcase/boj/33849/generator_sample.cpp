#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const long long MAXV = 1000000000LL;

pair<long long, long long> makePairForRatio(long long num, long long den, long long scale) {
    return {den * scale, num * scale};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 24);
    vector<long long> x(n), y(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            x[i] = rnd.next(1, 40);
            y[i] = rnd.next(1, 40);
        }
    } else if (mode == 1) {
        long long den = rnd.next(1, 20);
        long long num = rnd.next(den, 40LL);
        int l = rnd.next(0, n - 1);
        int r = rnd.next(l, n - 1);

        for (int i = 0; i < n; ++i) {
            if (l <= i && i <= r) {
                long long scale = rnd.next(1LL, MAXV / max(num, den));
                auto p = makePairForRatio(num, den, scale);
                x[i] = p.first;
                y[i] = p.second;
            } else {
                long long scale = rnd.next(1, 20);
                x[i] = den * scale;
                y[i] = max(1LL, num * scale - rnd.next(1LL, min(10LL, num * scale)));
            }
        }
    } else if (mode == 2) {
        long long den = rnd.next(2, 50);
        long long num = rnd.next(1LL, den - 1);

        for (int i = 0; i < n; ++i) {
            long long scale = rnd.next(1LL, min(1000000LL, MAXV / den));
            x[i] = den * scale;
            y[i] = num * scale;
            if (rnd.next(0, 2) == 0 && y[i] < MAXV) ++y[i];
            if (rnd.next(0, 3) == 0 && y[i] > 1) --y[i];
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1) == 0) {
                x[i] = rnd.next(MAXV - 1000, MAXV);
                y[i] = rnd.next(1, 1000);
            } else {
                x[i] = rnd.next(1, 1000);
                y[i] = rnd.next(MAXV - 1000, MAXV);
            }
        }
    } else if (mode == 4) {
        long long den = rnd.next(1, 1000);
        long long num = rnd.next(1, 1000);
        long long g = __gcd(num, den);
        num /= g;
        den /= g;

        long long maxScale = MAXV / max(num, den);
        for (int i = 0; i < n; ++i) {
            long long scale = rnd.next(1LL, min(1000000LL, maxScale));
            auto p = makePairForRatio(num, den, scale);
            x[i] = p.first;
            y[i] = p.second;
        }
    } else {
        n = rnd.next(20, 60);
        x.assign(n, 1);
        y.assign(n, 1);
        long long high = rnd.next(MAXV - 10000, MAXV);
        int blocks = rnd.next(1, 4);
        for (int b = 0; b < blocks; ++b) {
            int l = rnd.next(0, n - 1);
            int len = rnd.next(1, min(8, n - l));
            for (int i = l; i < l + len; ++i) {
                x[i] = 1;
                y[i] = high;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (y[i] != high) {
                x[i] = rnd.next(1, 200);
                y[i] = rnd.next(1, 200);
            }
        }
    }

    println(n);
    println(x);
    println(y);

    return 0;
}
