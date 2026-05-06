#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Safe multiply with upper bound check using __int128
bool mul_le(__int128 a, __int128 b, __int128 limit) {
    if (a == 0 || b == 0) return true;
    return a <= limit / b;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read single integer k with canonical form and given range
    long long k = inf.readLong(3LL, 4000000000000000000LL, "k");
    inf.readEoln();

    // Now check the global promise there exists a solution (x,y) with:
    // 2/k = 1/x + 1/y, 1 <= x < y <= 2^125, and x,y integers
    // For validation, just check existence of *some* solution with bounds.
    // Derivation:
    // 1/x + 1/y = 2/k => (x + y) / (xy) = 2/k => 2xy - kx - ky = 0
    // Add k^2/2 to both sides (algebraic trick):
    // (2x - k)(2y - k) = k^2
    // Put a = 2x - k, b = 2y - k => a*b = k^2
    // From 1 <= x <= y we get a <= b and a,b > -k, and also parity constraints:
    // a and b must have same parity as k (so that x,y are integers).
    //
    // Known number-theoretic fact (Egyptian fractions) ensures at least one
    // decomposition for all k >= 3 with denominators of possibly large size,
    // but the problem restricts x,y <= 2^125. We must verify such a pair exists
    // for the given k under this bound, as the statement guarantees that.

    // Precompute bound B = 2^125
    __int128 B = (__int128)1 << 125;

    __int128 kk = k;
    __int128 kk2 = kk * kk;

    bool ok = false;

    // Iterate over divisors d of k^2 up to sqrt(k^2)=k, so up to k.
    // For each divisor a = d, b = k^2 / d, with a <= b.
    // Only consider a,b having same parity as k.
    // Then x = (a + k)/2, y = (b + k)/2.
    // Check x >= 1, x < y, and both <= 2^125.
    long long limit = k; // divisors up to k
    for (long long d = 1; d * ( (__int128)d ) <= kk2; ++d) {
        if (kk2 % d != 0) continue;
        __int128 a = d;
        __int128 b = kk2 / d;
        if (a > b) break; // since d increases

        // parity check: a, b, k must have same parity
        if ( ( (a ^ kk) & 1 ) != 0 ) continue;
        if ( ( (b ^ kk) & 1 ) != 0 ) continue;

        __int128 x = (a + kk) / 2;
        __int128 y = (b + kk) / 2;

        if (!(x >= 1 && x < y)) continue;
        if (!(x <= B && y <= B)) continue;

        ok = true;
        break;
    }

    ensuref(ok, "No pair (x,y) exists satisfying 2/k = 1/x + 1/y with 1<=x<y<=2^125 for k=%lld", k);

    inf.readEof();
}
