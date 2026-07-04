#include "testlib.h"

#include <cstdint>
#include <vector>
using namespace std;

using u64 = uint64_t;
using u128 = __uint128_t;

constexpr u64 kLimit = 1000000000000000000ULL;

u64 multiplyMod(u64 a, u64 b, u64 mod) {
    return static_cast<u64>((u128)a * b % mod);
}

u64 powerMod(u64 a, u64 e, u64 mod) {
    u64 result = 1;
    while (e > 0) {
        if (e & 1) result = multiplyMod(result, a, mod);
        a = multiplyMod(a, a, mod);
        e >>= 1;
    }
    return result;
}

bool isPrime(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL,
                  23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n % p == 0) return n == p;
    }

    u64 d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }

    for (u64 a : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL,
                  23ULL, 29ULL, 31ULL, 37ULL}) {
        if (a >= n) continue;
        u64 x = powerMod(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (int r = 1; r < s; ++r) {
            x = multiplyMod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

u64 readFactorization(const char* name) {
    // CHECK: n has no explicit bound; product <= 1e18 implies at most 59 prime factors.
    int n = inf.readInt(0, 60, format("%s_n", name));
    u128 product = 1;

    for (int i = 0; i < n; ++i) {
        inf.readSpace();
        u64 p = inf.readUnsignedLong(2ULL, kLimit, format("%s_p_%d", name, i + 1));
        ensuref(isPrime(p), "%s factor %d is not prime: %llu", name, i + 1,
                static_cast<unsigned long long>(p));
        product *= p;
        ensuref(product <= kLimit, "%s product exceeds 10^18", name);
    }
    inf.readEoln();

    return static_cast<u64>(product);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 50000, "Q");
    inf.readEoln();

    for (int query = 1; query <= q; ++query) {
        setTestCase(query);
        u64 g = readFactorization("G");
        u64 l = readFactorization("L");

        ensuref(g <= l, "query %d violates G <= L: %llu > %llu", query,
                static_cast<unsigned long long>(g),
                static_cast<unsigned long long>(l));
        ensuref(l % g == 0, "query %d has L not divisible by G", query);
    }

    inf.readEof();
}
