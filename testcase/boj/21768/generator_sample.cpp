#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(0, 2);
    } else if (mode <= 3) {
        n = rnd.next(2, 8);
    } else {
        n = rnd.next(2, 12);
    }

    int length = 1 << n;
    vector<int> a(length, 0);

    if (mode == 0) {
        int base = rnd.next(0, 20);
        for (int mask = 0; mask < length; ++mask) {
            a[mask] = base + rnd.next(0, 3) * __builtin_popcount((unsigned)mask);
        }
    } else if (mode == 1) {
        vector<int> weight(n);
        for (int bit = 0; bit < n; ++bit) {
            weight[bit] = rnd.next(0, 25);
        }
        int base = rnd.next(0, 30);
        for (int mask = 0; mask < length; ++mask) {
            a[mask] = base;
            for (int bit = 0; bit < n; ++bit) {
                if (mask & (1 << bit)) {
                    a[mask] += weight[bit];
                }
            }
        }
    } else if (mode == 2) {
        int scale = rnd.next(1, 30);
        int bias = rnd.next(0, 50);
        for (int mask = 0; mask < length; ++mask) {
            int bits = __builtin_popcount((unsigned)mask);
            a[mask] = bias + scale * bits * bits;
        }
    } else if (mode == 3) {
        int base = rnd.next(0, 60);
        for (int mask = 0; mask < length; ++mask) {
            a[mask] = base + rnd.next(0, 250);
        }

        int b1 = rnd.next(0, n - 1);
        int b2 = rnd.next(0, n - 2);
        if (b2 >= b1) {
            ++b2;
        }

        vector<int> freeBits;
        for (int bit = 0; bit < n; ++bit) {
            if (bit != b1 && bit != b2) {
                freeBits.push_back(bit);
            }
        }

        int baseMask = 0;
        for (int bit : freeBits) {
            if (rnd.next(0, 1)) {
                baseMask |= 1 << bit;
            }
        }

        int x = baseMask | (1 << b1);
        int y = baseMask | (1 << b2);
        int both = baseMask | (1 << b1) | (1 << b2);
        int low = rnd.next(0, 100);
        int high = low + rnd.next(1, 100);
        a[baseMask] = high;
        a[x] = low;
        a[y] = low;
        a[both] = high + rnd.next(1, 100);
    } else {
        vector<int> bitValue(n);
        for (int bit = 0; bit < n; ++bit) {
            bitValue[bit] = rnd.next(1, 40);
        }

        int bias = rnd.next(0, 100);
        for (int mask = 0; mask < length; ++mask) {
            int value = bias;
            for (int bit = 0; bit < n; ++bit) {
                if (mask & (1 << bit)) {
                    value += bitValue[bit];
                }
            }
            a[mask] = value;
        }

        int b1 = rnd.next(0, n - 1);
        int b2 = rnd.next(0, n - 2);
        if (b2 >= b1) {
            ++b2;
        }

        int baseMask = rnd.next(0, length - 1) & ~(1 << b1) & ~(1 << b2);
        int both = baseMask | (1 << b1) | (1 << b2);
        a[both] += rnd.next(1, 200);
    }

    for (int& value : a) {
        value = min(value, 10000000);
    }

    println(n);
    println(a);

    return 0;
}
