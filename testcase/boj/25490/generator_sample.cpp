#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 30);
    vector<long long> b(n);

    if (mode == 0) {
        long long value = rnd.next(0LL, 1000000000LL);
        fill(b.begin(), b.end(), value);
    } else if (mode == 1) {
        long long cur = rnd.next(0LL, 20LL);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0LL, 5LL);
            b[i] = cur;
        }
        if (rnd.next(0, 1)) {
            reverse(b.begin(), b.end());
        }
    } else if (mode == 2) {
        long long low = rnd.next(0LL, 5LL);
        long long high = rnd.next(999999990LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            b[i] = (i % 2 == 0 ? low + rnd.next(0LL, 3LL) : high - rnd.next(0LL, 3LL));
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            b[i] = rnd.next(0, 3) == 0 ? rnd.next(1LL, 1000000000LL) : 0LL;
        }
    } else if (mode == 4) {
        int pivot = rnd.next(0, n - 1);
        long long center = rnd.next(0LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            long long delta = rnd.next(0LL, 10LL);
            if (i <= pivot) {
                b[i] = min(1000000000LL, center + delta + pivot - i);
            } else {
                b[i] = max(0LL, center - delta - (i - pivot));
            }
        }
    } else if (mode == 5) {
        long long lo = rnd.next(0LL, 100LL);
        long long hi = rnd.next(lo, min(1000000000LL, lo + rnd.next(0LL, 100000LL)));
        for (int i = 0; i < n; ++i) {
            b[i] = rnd.next(lo, hi);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 4);
            if (bucket == 0) {
                b[i] = 0;
            } else if (bucket == 1) {
                b[i] = rnd.next(1LL, 20LL);
            } else if (bucket == 2) {
                b[i] = rnd.next(999999980LL, 1000000000LL);
            } else {
                b[i] = rnd.next(0LL, 1000000000LL);
            }
        }
    }

    println(n);
    println(b);

    return 0;
}
