#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 30);
    int q = rnd.next(1, 35);
    int mode = rnd.next(0, 3);

    string bits;
    bits.reserve(n);

    if (mode == 0) {
        char bit = rnd.next(0, 1) ? '1' : '0';
        bits.assign(n, bit);
    } else if (mode == 1) {
        char first = rnd.next(0, 1) ? '1' : '0';
        for (int i = 0; i < n; ++i) {
            bits.push_back((i & 1) ? (first == '0' ? '1' : '0') : first);
        }
    } else if (mode == 2) {
        char bit = rnd.next(0, 1) ? '1' : '0';
        while ((int)bits.size() < n) {
            int remaining = n - (int)bits.size();
            int run = rnd.next(1, min(remaining, 6));
            bits.append(run, bit);
            bit = bit == '0' ? '1' : '0';
        }
    } else {
        for (int i = 0; i < n; ++i) {
            bits.push_back(rnd.next(0, 1) ? '1' : '0');
        }
    }

    println(n, q);
    println(bits);

    bool hasCombo = false;
    for (int i = 1; i <= q; ++i) {
        int t;
        if (i == q && !hasCombo) {
            t = 2;
        } else {
            t = rnd.next(1, 100) <= 55 ? 2 : 1;
        }
        hasCombo = hasCombo || t == 2;

        int l = 1;
        int r = n;
        int rangeMode = rnd.next(0, 4);
        if (rangeMode == 0) {
            int p = rnd.next(1, n);
            l = p;
            r = p;
        } else if (rangeMode == 1) {
            r = rnd.next(1, n);
        } else if (rangeMode == 2) {
            l = rnd.next(1, n);
        } else if (rangeMode == 3) {
            l = rnd.next(1, n);
            r = rnd.next(l, n);
        }

        println(t, l, r);
    }

    return 0;
}
