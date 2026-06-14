#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

namespace {

constexpr long long MAX_PRIME = 20000000LL;
constexpr long long MAX_C = MAX_PRIME * MAX_PRIME;

long long randomPrime(const vector<long long>& primes, int mode) {
    if (mode == 0) {
        return primes[rnd.next(0, 9)];
    }
    if (mode == 1) {
        return primes[rnd.next(10, 18)];
    }
    return rnd.any(primes);
}

long long randomBoundedConstant(const vector<long long>& primes, int mode) {
    if (mode == 0) {
        return rnd.next(1LL, 1000LL);
    }
    if (mode == 1) {
        return rnd.any(primes) * rnd.any(primes);
    }
    if (mode == 2) {
        return MAX_C;
    }
    return rnd.next(MAX_C - 1000000LL, MAX_C);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> primes = {
        2,        3,        5,        7,        11,       13,       17,
        19,       23,       29,       97,       101,      997,      1009,
        7919,     104729,   999983,   19999981, 19999999,
    };

    int mode = rnd.next(0, 3);
    long long x2 = randomPrime(primes, mode);
    long long x1 = randomPrime(primes, mode);
    long long x3 = randomPrime(primes, mode);
    while (x1 == x3) {
        x3 = randomPrime(primes, mode);
    }

    int secondMode = rnd.next(0, 3);
    long long x6 = randomPrime(primes, secondMode);
    long long x7 = randomPrime(primes, secondMode);
    long long x5 = randomPrime(primes, secondMode);
    while (x7 == x5) {
        x5 = randomPrime(primes, secondMode);
    }

    int cMode = rnd.next(0, 3);
    long long c1 = x1 * x2;
    long long c2 = randomBoundedConstant(primes, cMode);
    long long c3 = x6 * x7;
    long long c4 = randomBoundedConstant(primes, rnd.next(0, 3));
    long long c5 = x2 * x3;
    long long c6 = x6 * x5;

    println(c1, c2, c3, c4, c5, c6);
    return 0;
}
