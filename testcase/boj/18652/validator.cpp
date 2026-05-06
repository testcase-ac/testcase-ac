#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    long long sumK = 0;

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        long long P = inf.readLong(1LL, (long long)1e18, "P");
        inf.readSpace();
        long long m = inf.readLong(1LL, (long long)1e18, "m");
        inf.readSpace();

        // k can be up to 18, and string may contain leading zeros, only digits.
        string s = inf.readToken("[0-9]{1,18}", "digits");
        inf.readEoln();

        int k = (int)s.size();
        ensuref(1 <= k && k <= 18, "Length of digits string must be between 1 and 18, got %d in test %d", k, tc);
        sumK += k;

        // gcd(P, 10^18) < 5
        // 10^18 = 2^18 * 5^18
        // gcd value is in {1,2,3,4}; but gcd with 10^18 can't be 3, so effectively in {1,2,4}
        // We enforce gcd(P, 10^18) <= 4, which is equivalent to < 5.
        long long g = std::gcd(P, (long long)1000000000000000000LL);
        ensuref(g < 5, "gcd(P, 10^18) must be < 5, but gcd(%lld,10^18) = %lld in test %d", P, g, tc);
    }

    ensuref(sumK <= 10000, "Sum of all k (lengths of digit strings) must be <= 10000, got %lld", sumK);

    inf.readEof();
}
