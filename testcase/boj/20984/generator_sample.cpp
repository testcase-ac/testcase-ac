#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long clampHeight(long long x) {
    return max(1LL, min(1000000000LL, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 45);
    vector<long long> a(n);

    if (mode == 0) {
        long long cur = rnd.next(1LL, 1000000000LL);
        long long step = rnd.next(0LL, 12LL);
        for (int i = 0; i < n; ++i) {
            a[i] = clampHeight(cur + step * i);
        }
    } else if (mode == 1) {
        long long cur = rnd.next(1LL, 1000000000LL);
        long long step = rnd.next(0LL, 12LL);
        for (int i = 0; i < n; ++i) {
            a[i] = clampHeight(cur - step * i);
        }
    } else if (mode == 2) {
        int pivot = rnd.next(0, n - 1);
        long long high = rnd.next(20LL, 1000000000LL);
        long long leftStep = rnd.next(1LL, 20LL);
        long long rightStep = rnd.next(1LL, 20LL);
        for (int i = 0; i < n; ++i) {
            long long dist = abs(i - pivot);
            long long step = (i < pivot ? leftStep : rightStep);
            a[i] = clampHeight(high - dist * step);
        }
    } else if (mode == 3) {
        int pivot = rnd.next(0, n - 1);
        long long low = rnd.next(1LL, 1000000000LL - 50);
        long long leftStep = rnd.next(1LL, 20LL);
        long long rightStep = rnd.next(1LL, 20LL);
        for (int i = 0; i < n; ++i) {
            long long dist = abs(i - pivot);
            long long step = (i < pivot ? leftStep : rightStep);
            a[i] = clampHeight(low + dist * step);
        }
    } else if (mode == 4) {
        long long lo = rnd.next(1LL, 30LL);
        long long hi = rnd.next(999999950LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? hi : lo);
            if (rnd.next(0, 3) == 0) {
                a[i] = clampHeight(a[i] + rnd.next(-3LL, 3LL));
            }
        }
    } else if (mode == 5) {
        long long cur = rnd.next(1LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            if (i == 0 || rnd.next(0, 2) == 0) {
                cur = rnd.next(1LL, 1000000000LL);
            }
            a[i] = cur;
        }
    } else {
        long long cur = rnd.next(1LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            cur = clampHeight(cur + rnd.next(-25LL, 25LL));
            a[i] = cur;
        }
    }

    println(n);
    println(a);
    return 0;
}
