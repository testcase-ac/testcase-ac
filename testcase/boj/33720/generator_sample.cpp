#include "testlib.h"
#include <vector>

using namespace std;

long long randomOdd(long long lo, long long hi) {
    long long value = rnd.next(lo, hi);
    if (value % 2 == 0) {
        if (value == hi) --value;
        else ++value;
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_N = 1000000000000LL;
    long long n;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        vector<long long> edges = {2, 3, 4, 5, 12, 17, MAX_N - 1, MAX_N};
        n = rnd.any(edges);
    } else if (mode == 1) {
        n = rnd.next(1LL, 500000000000LL) * 2LL;
    } else if (mode == 2) {
        vector<long long> smallPrimes = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 97, 997};
        n = rnd.any(smallPrimes);
    } else if (mode == 3) {
        vector<long long> smallFactors = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        long long p = rnd.any(smallFactors);
        long long q = randomOdd(1LL, MAX_N / p);
        n = p * q;
        if (n < 2) n = p * p;
    } else if (mode == 4) {
        long long base = randomOdd(3LL, 1000000LL);
        n = base * base;
    } else if (mode == 5) {
        long long offset = rnd.next(0LL, 1000000LL);
        n = MAX_N - offset;
        if (n < 2) n = 2;
    } else if (mode == 6) {
        n = randomOdd(999999000001LL, MAX_N - 1);
    } else {
        n = rnd.next(2LL, MAX_N);
    }

    println(n);
    return 0;
}
