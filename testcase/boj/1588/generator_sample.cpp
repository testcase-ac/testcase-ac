#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long LIMIT = 2147483647LL;

long long pow3(int n) {
    long long value = 1;
    for (int i = 0; i < n; ++i) {
        value *= 3LL;
    }
    return value;
}

long long maxIndexFor(int n) {
    return min(LIMIT, pow3(n) - 1);
}

long long clampIndex(long long value, long long hi) {
    return min(max(0LL, value), hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int initial = rnd.next(1, 3);
    int mode = rnd.next(0, 7);
    int n = rnd.next(0, 20);
    long long left = 0;
    long long right = 0;

    if (mode == 0) {
        n = rnd.next(0, 4);
        long long hi = maxIndexFor(n);
        left = rnd.next(0LL, hi);
        right = rnd.next(left, hi);
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        long long hi = maxIndexFor(n);
        left = right = rnd.next(0LL, hi);
    } else if (mode == 2) {
        n = rnd.next(1, 20);
        long long hi = maxIndexFor(n);
        long long width = rnd.next(0LL, min(20LL, hi));
        left = rnd.next(0LL, hi - width);
        right = left + width;
    } else if (mode == 3) {
        n = rnd.next(1, 20);
        long long hi = maxIndexFor(n);
        right = rnd.next(0LL, min(100LL, hi));
        left = rnd.next(0LL, right);
    } else if (mode == 4) {
        n = rnd.next(1, 20);
        long long hi = maxIndexFor(n);
        long long width = rnd.next(0LL, min(100LL, hi));
        right = hi;
        left = hi - width;
    } else if (mode == 5) {
        n = rnd.next(1, 20);
        long long hi = maxIndexFor(n);
        long long block = pow3(rnd.next(0, n - 1));
        long long anchor = rnd.next(0LL, hi / block) * block;
        long long radius = rnd.next(0LL, min(12LL, hi));
        left = clampIndex(anchor - radius, hi);
        right = clampIndex(anchor + radius, hi);
    } else if (mode == 6) {
        n = rnd.next(18, 20);
        long long hi = maxIndexFor(n);
        vector<long long> anchors = {0LL, 1LL, 2LL, hi / 3, hi / 2, hi - 2, hi - 1, hi};
        long long anchor = rnd.any(anchors);
        long long radius = rnd.next(0LL, 100000LL);
        left = clampIndex(anchor - radius, hi);
        right = clampIndex(anchor + radius, hi);
    } else {
        n = rnd.next(0, 20);
        long long hi = maxIndexFor(n);
        left = rnd.next(0LL, hi);
        right = rnd.next(0LL, hi);
        if (left > right) swap(left, right);
    }

    println(initial);
    println(left);
    println(right);
    println(n);

    return 0;
}
