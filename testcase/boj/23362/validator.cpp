#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using uint64 = unsigned long long;
using uint128 = __uint128_t;

uint64 mulMod(uint64 a, uint64 b, uint64 mod) {
    return static_cast<uint128>(a) * b % mod;
}

uint64 powMod(uint64 a, uint64 e, uint64 mod) {
    uint64 result = 1;
    while (e > 0) {
        if (e & 1) {
            result = mulMod(result, a, mod);
        }
        a = mulMod(a, a, mod);
        e >>= 1;
    }
    return result;
}

bool isPrime(uint64 n) {
    if (n < 2) {
        return false;
    }
    for (uint64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL,
                     23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n % p == 0) {
            return n == p;
        }
    }

    uint64 d = n - 1;
    int shifts = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++shifts;
    }

    for (uint64 a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL,
                     1795265022ULL}) {
        if (a % n == 0) {
            continue;
        }
        uint64 x = powMod(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }
        bool witness = true;
        for (int r = 1; r < shifts; ++r) {
            x = mulMod(x, x, n);
            if (x == n - 1) {
                witness = false;
                break;
            }
        }
        if (witness) {
            return false;
        }
    }

    return true;
}

uint64 rho(uint64 n) {
    if (n % 2 == 0) {
        return 2;
    }
    if (n % 3 == 0) {
        return 3;
    }

    for (uint64 c = 1;; ++c) {
        uint64 x = 2;
        uint64 y = 2;
        uint64 d = 1;
        while (d == 1) {
            x = (mulMod(x, x, n) + c) % n;
            y = (mulMod(y, y, n) + c) % n;
            y = (mulMod(y, y, n) + c) % n;
            uint64 diff = x > y ? x - y : y - x;
            d = std::gcd(diff, n);
        }
        if (d != n) {
            return d;
        }
    }
}

void addFactors(uint64 n, map<uint64, int>& factors) {
    if (n == 1) {
        return;
    }
    if (isPrime(n)) {
        ++factors[n];
        return;
    }

    uint64 factor = rho(n);
    addFactors(factor, factors);
    addFactors(n / factor, factors);
}

int divisorCount(uint64 n) {
    map<uint64, int> factors;
    addFactors(n, factors);

    int result = 1;
    for (auto [prime, exponent] : factors) {
        result *= exponent + 1;
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 60, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        inf.readEoln();

        int64 n = inf.readLong(1LL, 99999999999999LL, "N");
        inf.readEoln();

        ensuref(divisorCount(static_cast<uint64>(n)) <= 47,
                "N in case %d has more than 47 divisors: %lld",
                caseIndex,
                n);
    }

    inf.readEof();
}
