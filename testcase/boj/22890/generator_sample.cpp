#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int kMaxX = 1000000000;

int digitCount(int x) {
    int digits = 0;
    do {
        ++digits;
        x /= 10;
    } while (x > 0);
    return digits;
}

int pow10Int(int e) {
    int result = 1;
    while (e--) result *= 10;
    return result;
}

vector<int> makeCase(int mode, int n) {
    vector<int> x(n);

    if (mode == 0) {
        int cur = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(1, 20);
            x[i] = cur;
        }
    } else if (mode == 1) {
        int value = rnd.next(1, kMaxX);
        for (int i = 0; i < n; ++i) x[i] = value;
    } else if (mode == 2) {
        int cur = rnd.next(1, kMaxX);
        for (int i = 0; i < n; ++i) {
            x[i] = cur;
            cur = max(1, cur - rnd.next(0, min(cur - 1, 1000000)));
        }
    } else if (mode == 3) {
        int prefix = rnd.next(1, 9999);
        int digits = digitCount(prefix);
        int scale = pow10Int(rnd.next(1, 9 - digits));
        int base = min(kMaxX, prefix * scale);
        for (int i = 0; i < n; ++i) {
            x[i] = (i % 2 == 0 ? base + rnd.next(0, min(scale - 1, kMaxX - base)) : prefix);
        }
    } else if (mode == 4) {
        int hi = rnd.next(900000000, kMaxX);
        for (int i = 0; i < n; ++i) {
            x[i] = rnd.next(max(1, hi - 1000), hi);
        }
    } else if (mode == 5) {
        int first = rnd.next(1, 9);
        for (int i = 0; i < n; ++i) {
            int digits = rnd.next(1, 9);
            int lo = (digits == 1 ? 1 : pow10Int(digits - 1));
            int hi = min(kMaxX, pow10Int(digits) - 1);
            x[i] = rnd.next(lo, hi);
            if (rnd.next(0, 3) == 0) x[i] = first;
        }
    } else {
        int lo = rnd.next(1, 1000);
        int hi = rnd.next(lo, min(kMaxX, lo + rnd.next(0, 10000)));
        for (int i = 0; i < n; ++i) x[i] = rnd.next(lo, hi);
    }

    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 14);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = (tc < 7 ? tc : rnd.next(0, 6));
        int n = rnd.next(2, 12);
        if (tc == t - 1 && rnd.next(0, 2) == 0) n = rnd.next(30, 100);

        vector<int> x = makeCase(mode, n);
        if (rnd.next(0, 4) == 0) {
            shuffle(x.begin(), x.end());
        }

        println(n);
        println(x);
    }

    return 0;
}
