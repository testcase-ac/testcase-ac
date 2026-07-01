#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long kMinA = 0;
const long long kMaxA = 1000000000LL;

long long clampValue(long long x) {
    return max(kMinA, min(kMaxA, x));
}

vector<long long> arithmeticArray(int n) {
    long long diff = rnd.next(-20, 20);
    long long lo = max(kMinA, kMinA - diff * (n - 1));
    long long hi = min(kMaxA, kMaxA - diff * (n - 1));
    if (lo > hi) {
        diff = 0;
        lo = kMinA;
        hi = kMaxA;
    }

    long long start = rnd.next(lo, hi);
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = start + diff * i;
    }
    return a;
}

vector<long long> oneChangedArithmetic(int n) {
    vector<long long> a = arithmeticArray(n);
    int pos = rnd.next(0, n - 1);
    long long delta = rnd.next(1, 50);
    if (rnd.next(2) == 0) {
        delta = -delta;
    }
    a[pos] = clampValue(a[pos] + delta);
    return a;
}

vector<long long> constantWithGlitches(int n) {
    long long base = rnd.next(0LL, 1000000000LL);
    vector<long long> a(n, base);
    int glitches = rnd.next(1, min(4, n));
    for (int i = 0; i < glitches; ++i) {
        int pos = rnd.next(0, n - 1);
        long long delta = rnd.next(1, 10);
        if (rnd.next(2) == 0) {
            delta = -delta;
        }
        a[pos] = clampValue(base + delta);
    }
    return a;
}

vector<long long> randomWalk(int n) {
    vector<long long> a(n);
    a[0] = rnd.next(0LL, 1000000000LL);
    for (int i = 1; i < n; ++i) {
        a[i] = clampValue(a[i - 1] + rnd.next(-30, 30));
    }
    return a;
}

vector<long long> boundaryCase(int n) {
    vector<long long> a(n);
    long long base = rnd.next(2) == 0 ? 0 : 1000000000LL;
    for (int i = 0; i < n; ++i) {
        long long offset = rnd.next(0, 5);
        if (base == 0) {
            a[i] = offset;
        } else {
            a[i] = 1000000000LL - offset;
        }
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 18);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0) {
            n = 2;
        } else if (rnd.next(5) == 0) {
            n = rnd.next(40, 120);
        } else {
            n = rnd.next(2, 18);
        }

        int mode = rnd.next(5);
        vector<long long> a;
        if (mode == 0) {
            a = arithmeticArray(n);
        } else if (mode == 1) {
            a = oneChangedArithmetic(n);
        } else if (mode == 2) {
            a = constantWithGlitches(n);
        } else if (mode == 3) {
            a = randomWalk(n);
        } else {
            a = boundaryCase(n);
        }

        println(n);
        println(a);
    }

    return 0;
}
