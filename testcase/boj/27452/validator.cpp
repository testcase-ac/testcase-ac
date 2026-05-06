#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    long long T = inf.readLong(1LL, 1000LL, "T");
    inf.readEoln();

    // Precompute lengths of S_n up to where they exceed 1e18,
    // since lengths grow like Fibonacci and we only care about
    // whether k > |S_n| or not (answer existence guarantee).
    const long long LIM = (long long)1e18;
    vector<long long> len;
    len.push_back(0); // dummy for 0-index
    len.push_back(2); // |S_1| = 2, "()"
    len.push_back(2); // |S_2| = 2, "()"
    while (true) {
        long long a = len[len.size() - 2];
        long long b = len[len.size() - 1];
        __int128 next = (__int128)a + (__int128)b + 2; // +2 for outer "()"
        if (next > (__int128)LIM) {
            len.push_back(LIM + 1); // cap above limit
            break;
        } else {
            len.push_back((long long)next);
        }
        if ((int)len.size() > 1000) break; // safety, never actually hit
    }

    for (long long tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        long long n = inf.readLong(1LL, (long long)1e18, "n");
        inf.readSpace();
        long long k = inf.readLong(1LL, (long long)1e18, "k");
        inf.readEoln();

        // Validate the "answer is 0 if k > |S_n|" promise by computing |S_n|
        // or an upper bound and checking consistency.
        // Effective length for large n: it saturates to > 1e18 quickly.
        long long effectiveLen;
        if (n < (long long)len.size())
            effectiveLen = len[(size_t)n];
        else
            effectiveLen = LIM + 1; // definitely longer than any k in range

        // No specific constraint to enforce beyond range, but we at least
        // ensure our modeling didn't underflow / overflow.
        ensuref(effectiveLen >= 2,
                "Computed length for n=%lld is too small: %lld", n, effectiveLen);

        // Nothing else to check per test case: n,k already in range,
        // and we just modeled length for global property.
    }

    inf.readEof();
}
