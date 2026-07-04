#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <vector>
using namespace std;

using u64 = uint64_t;
using u128 = __uint128_t;

constexpr long long kMaxPrimeExclusive = 1000000000000000000LL;

u64 multiplyMod(u64 a, u64 b, u64 mod) {
    return static_cast<u64>((u128)a * b % mod);
}

u64 powerMod(u64 a, u64 exponent, u64 mod) {
    u64 result = 1;
    a %= mod;
    while (exponent > 0) {
        if (exponent & 1) result = multiplyMod(result, a, mod);
        a = multiplyMod(a, a, mod);
        exponent >>= 1;
    }
    return result;
}

bool isPrime(u64 value) {
    if (value < 2) return false;
    for (u64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL,
                  23ULL, 29ULL, 31ULL, 37ULL}) {
        if (value % p == 0) return value == p;
    }

    u64 d = value - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }

    for (u64 a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL,
                  1795265022ULL}) {
        if (a % value == 0) continue;
        u64 x = powerMod(a, d, value);
        if (x == 1 || x == value - 1) continue;

        bool composite = true;
        for (int r = 1; r < s; ++r) {
            x = multiplyMod(x, x, value);
            if (x == value - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

long long nextPrime(long long value) {
    if (value <= 2) return 2;
    if ((value & 1) == 0) ++value;
    while (value < kMaxPrimeExclusive && !isPrime(static_cast<u64>(value))) {
        value += 2;
    }
    return value;
}

long long randomPrime(long long low, long long high) {
    long long value = rnd.next(low, high);
    long long candidate = nextPrime(value);
    if (candidate <= high) return candidate;

    value = rnd.next(low, high);
    if ((value & 1) == 0) --value;
    for (long long x = value; x >= low; x -= 2) {
        if (isPrime(static_cast<u64>(x))) return x;
    }
    return nextPrime(low);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> smallPrimes = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29,
                                     31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
                                     73, 79, 83, 89, 97};

    int mode = rnd.next(0, 4);
    int n = 1;
    vector<long long> primes;

    if (mode == 0) {
        n = rnd.next(1, 4);
        int start = rnd.next(0, static_cast<int>(smallPrimes.size()) - n);
        for (int i = 0; i < n; ++i) primes.push_back(smallPrimes[start + i]);
    } else {
        primes.push_back(rnd.any(smallPrimes));
        if (mode == 1) {
            n = rnd.next(2, 12);
            long long current = primes.back() + 1;
            for (int i = 1; i < n; ++i) {
                current = nextPrime(current + 1 + rnd.next(0, 8));
                primes.push_back(current);
            }
        } else if (mode == 2) {
            n = rnd.next(2, 18);
            long long current = primes.back();
            for (int i = 1; i < n; ++i) {
                long long gap = rnd.next(10LL, 50000LL);
                current = nextPrime(current + gap);
                primes.push_back(current);
            }
        } else if (mode == 3) {
            n = rnd.next(2, 14);
            for (int i = 1; i < n; ++i) {
                long long low = (i % 3 == 0) ? 1000000000LL : 100000LL;
                long long high = (i % 3 == 0) ? 1000000000000LL : 1000000000LL;
                primes.push_back(randomPrime(low, high));
            }
            sort(primes.begin(), primes.end());
            primes.erase(unique(primes.begin(), primes.end()), primes.end());
            n = static_cast<int>(primes.size());
        } else {
            n = rnd.next(2, 8);
            long long base = rnd.next(999999999000000000LL, 999999999999999000LL);
            for (int i = 1; i < n; ++i) {
                long long candidate = randomPrime(base + i * 100LL, base + i * 200000LL);
                primes.push_back(candidate);
            }
            sort(primes.begin(), primes.end());
            primes.erase(unique(primes.begin(), primes.end()), primes.end());
            n = static_cast<int>(primes.size());
        }
    }

    println(n);
    println(primes);
    return 0;
}
