#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    long long n = inf.readLong(2LL, 100000LL, "n");
    inf.readSpace();
    long long k = inf.readLong(0LL, n / 2, "k");
    inf.readEoln();

    // Read array a[1..n]
    vector<long long> a = inf.readLongs((int)n, 1LL, (long long)1e18, "a_i");
    inf.readEoln();

    // No extra global properties implied by the statement.
    // Just basic constraints already enforced by readLongs:
    //  - 1 <= a_i <= 1e18
    //  - canonical integer format is ensured by testlib.

    inf.readEof();
}
