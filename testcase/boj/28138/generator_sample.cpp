#include "testlib.h"

#include <algorithm>

using namespace std;

const long long LIMIT = 1000000000000LL;

long long boundedProduct(long long cap) {
    long long value = 1;
    int factors = rnd.next(1, 5);
    for (int i = 0; i < factors; ++i) {
        long long nextFactor = rnd.next(2LL, 12LL);
        if (value > cap / nextFactor) break;
        value *= nextFactor;
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long n = 1;
    long long r = 0;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = boundedProduct(1000000000LL) * rnd.next(1LL, 1000LL);
        n = max(1LL, min(n, LIMIT));
        r = 0;
    } else if (mode == 1) {
        r = rnd.next(1LL, 1000000LL);
        long long m = rnd.next(r + 1, r + 1000000LL);
        long long k = rnd.next(1LL, max(1LL, (LIMIT - r) / m));
        n = r + m * k;
    } else if (mode == 2) {
        r = rnd.next(1LL, 1000000LL);
        long long d = rnd.next(1LL, r);
        n = r + d;
    } else if (mode == 3) {
        long long root = rnd.next(1LL, 1000000LL);
        long long d = root * root;
        r = rnd.next(0LL, min(root + 20, LIMIT - d));
        n = r + d;
    } else if (mode == 4) {
        long long d = rnd.next(1LL, 1000000LL);
        n = LIMIT - rnd.next(0LL, 1000000LL);
        if (d >= n) d = 1;
        r = n - d;
    } else {
        long long d = boundedProduct(100000000000LL);
        r = rnd.next(0LL, min(1000000LL, LIMIT - d));
        n = r + d;
    }

    println(n, r);
    return 0;
}
