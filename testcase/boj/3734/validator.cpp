#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Compare non-negative decimal strings without leading zeros (except "0").
// Return -1 if a<b, 0 if a==b, 1 if a>b.
int cmpDec(const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    if (a == b) return 0;
    return a < b ? -1 : 1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // n can be up to 10^120-1, so we read it as a string.
    // It is stated as a number, so we must enforce canonical form.
    string nStr = inf.readToken("[0-9]+", "n");
    inf.readSpace();

    // k is an integer with 1 < k < 1e8, so k in [2, 10^8-1].
    // BUT the sample includes k = 1 ("35 1"), which must be accepted.
    // Therefore we trust the statement bound "1 < k < 1e8" except that
    // we relax the lower bound to 1 to allow the sample.
    long long k = inf.readLong(1LL, 100000000LL - 1LL, "k");
    inf.readEoln();

    // Canonical form for n: no leading zeros (except single "0", but here n>1).
    ensuref(!(nStr.size() > 1 && nStr[0] == '0'),
            "n must not have leading zeros");

    // 1 < n < 10^120  => n > 1 and at most 120 digits (since 10^120 has 121 digits).
    ensuref(cmpDec(nStr, "1") > 0, "n must be > 1");
    ensuref(nStr.size() <= 120, "n must have at most 120 digits");

    // The statement implies that for the given input there exist primes p, q
    // such that n = p * q, p <= q, and |q - k*p| <= 1e5.
    // However, n can be up to 120 decimal digits, so fully checking this
    // (by factoring n or searching such primes) is computationally infeasible
    // and unsafe in a validator.
    //
    // Therefore, we only enforce the explicit input-format and range constraints
    // and do NOT attempt to verify the existence of such primes globally.

    inf.readEof();
}
