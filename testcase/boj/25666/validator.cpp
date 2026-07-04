#include "testlib.h"

#include <cstdint>
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

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    long long previous = 0;
    for (int i = 1; i <= n; ++i) {
        if (i > 1) inf.readSpace();
        long long p = inf.readLong(2LL, kMaxPrimeExclusive - 1, format("p_%d", i));
        ensuref(previous < p, "p_%d must be greater than p_%d: %lld <= %lld",
                i, i - 1, p, previous);
        ensuref(i != 1 || p < 100, "p_1 must be less than 100, got %lld", p);
        ensuref(isPrime(static_cast<u64>(p)), "p_%d must be prime, got %lld", i, p);
        previous = p;
    }
    inf.readEoln();

    inf.readEof();
}
