#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long LIMIT = 100000000000000LL;

long long boundedRandom(long long lo, long long hi) {
    return rnd.next(lo, hi);
}

vector<long long> randomSmallArray(int n) {
    vector<long long> a(n);
    int valueLimit = rnd.next(1, 20);
    for (long long& x : a) {
        x = rnd.next(-valueLimit, valueLimit);
    }
    return a;
}

vector<long long> repeatedSegmentSums() {
    int segments = rnd.next(2, 8);
    long long target = rnd.next(-15, 15);
    vector<long long> a;

    for (int i = 0; i < segments; ++i) {
        int len = rnd.next(1, 4);
        long long sum = 0;
        for (int j = 0; j + 1 < len; ++j) {
            long long x = rnd.next(-10, 10);
            a.push_back(x);
            sum += x;
        }
        a.push_back(target - sum);
    }

    return a;
}

vector<long long> zeroRichArray() {
    int n = rnd.next(2, 20);
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        int kind = rnd.next(0, 5);
        if (kind <= 2) {
            a[i] = 0;
        } else if (kind == 3 && i + 1 < n) {
            long long x = rnd.next(1, 20);
            if (rnd.next(0, 1) == 0) x = -x;
            a[i] = x;
            a[++i] = -x;
        } else {
            a[i] = rnd.next(-3, 3);
        }
    }
    return a;
}

vector<long long> boundaryArray() {
    int n = rnd.next(2, 12);
    vector<long long> pool = {-LIMIT, -LIMIT + 1, -1000000, -1, 0,
                              1, 1000000, LIMIT - 1, LIMIT};
    vector<long long> a(n);
    for (long long& x : a) {
        x = rnd.any(pool);
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<long long> a;

    if (mode == 0) {
        a = randomSmallArray(rnd.next(1, 25));
    } else if (mode == 1) {
        a = repeatedSegmentSums();
    } else if (mode == 2) {
        a = zeroRichArray();
    } else if (mode == 3) {
        a = boundaryArray();
    } else {
        int n = rnd.next(2, 40);
        long long lo = boundedRandom(-1000, 0);
        long long hi = boundedRandom(0, 1000);
        a.resize(n);
        for (long long& x : a) {
            x = boundedRandom(lo, hi);
        }
    }

    println(static_cast<int>(a.size()));
    println(a);

    return 0;
}
