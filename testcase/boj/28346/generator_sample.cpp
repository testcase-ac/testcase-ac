#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_A = 1000000000;

int boundedValue(long long value) {
    return static_cast<int>(max(0LL, min<long long>(MAX_A, value)));
}

vector<int> makeCase(int mode, int n) {
    vector<int> a(n);

    if (mode == 0) {
        int x = rnd.next(0, 5);
        fill(a.begin(), a.end(), x);
    } else if (mode == 1) {
        int low = rnd.next(0, 20);
        int high = rnd.next(MAX_A - 1000, MAX_A);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0) ? low : high;
            if (rnd.next(4) == 0) a[i] = rnd.next(0, MAX_A);
        }
    } else if (mode == 2) {
        int baseBit = rnd.next(0, 29);
        for (int i = 0; i < n; ++i) {
            long long value = 1LL << rnd.next(max(0, baseBit - 2), min(29, baseBit + 2));
            if (rnd.next(2)) value -= 1;
            a[i] = boundedValue(value);
        }
    } else if (mode == 3) {
        int lo = rnd.next(0, 100);
        int hi = lo + rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
    } else if (mode == 4) {
        int start = rnd.next(0, 1000);
        int step = rnd.next(0, 100000);
        for (int i = 0; i < n; ++i) a[i] = boundedValue(start + 1LL * i * step);
        if (rnd.next(2)) reverse(a.begin(), a.end());
    } else {
        vector<int> pool;
        int poolSize = rnd.next(2, min(n, 6));
        for (int i = 0; i < poolSize; ++i) {
            pool.push_back(rnd.next(0, MAX_A));
        }
        for (int i = 0; i < n; ++i) a[i] = rnd.any(pool);
    }

    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        if (tc == 0 && rnd.next(3) == 0) {
            n = 2;
        } else if (mode == 2 || mode == 5) {
            n = rnd.next(2, 18);
        } else {
            n = rnd.next(2, 30);
        }

        println(n);
        println(makeCase(mode, n));
    }

    return 0;
}
