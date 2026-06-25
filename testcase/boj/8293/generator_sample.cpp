#include "testlib.h"

#include <vector>

using namespace std;

const long long MAX_N = 1000000000000000000LL;
const int MAX_K = 100000;

long long clampN(long long value) {
    if (value < 1) return 1;
    if (value > MAX_N) return MAX_N;
    return value;
}

long long powLimited(long long base, int exp) {
    __int128 value = 1;
    for (int i = 0; i < exp; ++i) {
        value *= base;
        if (value > MAX_N) return MAX_N;
    }
    return (long long)value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
        37, 41, 43, 47, 53, 59, 61
    };

    int mode = rnd.next(0, 6);
    long long n = 1;
    int k = 1;

    if (mode == 0) {
        n = rnd.next(1LL, 200LL);
        k = rnd.next(1, 30);
    } else if (mode == 1) {
        n = rnd.next(1LL, 1000000LL);
        k = rnd.next(1, 1000);
    } else if (mode == 2) {
        long long center = powLimited(rnd.any(primes), rnd.any(primes));
        n = clampN(center + rnd.next(-20LL, 20LL));
        k = rnd.next(1, 200);
    } else if (mode == 3) {
        long long base = rnd.next(900000000LL, 1000000000LL);
        n = clampN(base * base + rnd.next(-1000000LL, 1000000LL));
        k = rnd.next(1, 500);
    } else if (mode == 4) {
        n = rnd.next(1LL, MAX_N);
        k = rnd.next(1, MAX_K);
    } else if (mode == 5) {
        n = MAX_N - rnd.next(0LL, 1000000000000LL);
        k = rnd.next(MAX_K - 1000, MAX_K);
    } else {
        long long bucket = rnd.next(1LL, 1000000000LL);
        n = clampN(bucket * bucket);
        k = rnd.next(1, MAX_K);
    }

    println(n, k);
    return 0;
}
