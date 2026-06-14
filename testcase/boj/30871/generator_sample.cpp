#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxValue = 1000000000000000000LL;
    const long long threshold = 0x0123456789ABCDEFLL;

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 24);
    vector<long long> l(n), r(n);

    auto clampValue = [&](long long x) {
        return max(1LL, min(maxValue, x));
    };

    auto makeInterval = [&](long long center, long long radius) {
        long long left = clampValue(center - rnd.next(0LL, radius));
        long long right = clampValue(center + rnd.next(0LL, radius));
        if (left > right) swap(left, right);
        return pair<long long, long long>(left, right);
    };

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            long long base = rnd.next(1LL, 2000LL);
            long long width = rnd.next(0LL, 2000LL);
            l[i] = base;
            r[i] = min(maxValue, base + width);
        }
    } else if (mode == 1) {
        long long center = clampValue(threshold + rnd.next(-5000LL, 5000LL));
        for (int i = 0; i < n; ++i) {
            auto interval = makeInterval(center + rnd.next(-2000LL, 2000LL),
                                         rnd.next(0LL, 8000LL));
            l[i] = interval.first;
            r[i] = interval.second;
        }
    } else if (mode == 2) {
        long long left = rnd.next(1LL, 1000LL);
        long long right = rnd.next(maxValue - 1000000LL, maxValue);
        for (int i = 0; i < n; ++i) {
            l[i] = rnd.next(1, 3) == 1 ? rnd.next(1LL, left) : left;
            r[i] = rnd.next(1, 3) == 1 ? rnd.next(right, maxValue) : right;
        }
    } else if (mode == 3) {
        long long base = rnd.next(1LL, maxValue - 10000LL);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                l[i] = r[i] = clampValue(base + rnd.next(0LL, 10000LL));
            } else {
                auto interval = makeInterval(base + rnd.next(0LL, 10000LL),
                                             rnd.next(1LL, 100LL));
                l[i] = interval.first;
                r[i] = interval.second;
            }
        }
    } else if (mode == 4) {
        long long base = rnd.next(maxValue - 1000000LL, maxValue);
        for (int i = 0; i < n; ++i) {
            auto interval = makeInterval(base - rnd.next(0LL, 200000LL),
                                         rnd.next(0LL, 300000LL));
            l[i] = interval.first;
            r[i] = interval.second;
        }
    } else {
        for (int i = 0; i < n; ++i) {
            long long left = rnd.next(1LL, maxValue);
            long long width = rnd.next(0LL, 1000000000000LL);
            l[i] = left;
            r[i] = min(maxValue, left + width);
        }
    }

    println(n);
    println(l);
    println(r);

    return 0;
}
