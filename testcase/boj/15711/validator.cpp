#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

bool isPrime_i128(i128 n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;

    int64 smallPrimes[] = {5, 7, 11, 13, 17, 19, 23, 29};
    for (int64 p : smallPrimes) {
        if ((i128)p * p > n) break;
        if (n % p == 0) return (i128)p == n;
    }

    auto mod_mul = [](i128 a, i128 b, i128 m) -> i128 {
        return (a * b) % m;
    };
    auto mod_pow = [&](i128 a, i128 d, i128 m) -> i128 {
        i128 r = 1;
        while (d > 0) {
            if (d & 1) r = mod_mul(r, a, m);
            a = mod_mul(a, a, m);
            d >>= 1;
        }
        return r;
    };

    i128 d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }

    int64 bases[] = {2, 3, 5, 7, 11, 13};
    for (int64 a64 : bases) {
        if ((i128)a64 >= n) continue;
        i128 x = mod_pow(a64, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; ++r) {
            x = mod_mul(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

bool isSumOfTwoPrimes(i128 n) {
    if (n < 4) return false;
    if (n % 2 == 1) {
        // odd sum: n = 2 + (n-2)
        return isPrime_i128(2) && isPrime_i128(n - 2);
    } else {
        // even sum >= 4 : by Goldbach conjecture,
        // but problem guarantees existence only through its own test data.
        // We must verify it explicitly, not assume conjecture.
        // However, statement does NOT guarantee that any even >= 4 works,
        // only asks to check for each (A,B). So here we must actually
        // search, not rely on conjecture.
        // But for validation, we must verify "answer always exists" type
        // only if stated. Here it's not. So this function is only used
        // to recompute answer and cross-check, not for validator constraint.
        // Still, we implement a safe deterministic method for given limits.
        // For n up to 4e12, full search is too slow for validator.
        // So we do NOT use this for global constraints, just special cases.
        return true; // placeholder, but we won't rely on it for checks.
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 500, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        long long A = inf.readLong(1LL, 2000000000000LL, "A");
        inf.readSpace();
        long long B = inf.readLong(1LL, 2000000000000LL, "B");
        inf.readEoln();

        // No extra global constraints given (like "answer always exists"),
        // so we don't need to simulate anything beyond basic range checks.
        // However, we do a cheap sanity check on potential overflow:
        i128 sum = (i128)A + (i128)B;
        ensuref(sum <= (i128)4000000000000LL,
                "A + B exceeded expected safe bound at test %d", tc + 1);
    }

    inf.readEof();
}
