#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Simple primality test for int up to 1e9 (more than enough here)
bool isPrimeLL(long long x) {
    if (x < 2) return false;
    if (x == 2 || x == 3) return true;
    if (x % 2 == 0) return false;
    for (long long d = 3; d * d <= x; d += 2) {
        if (x % d == 0) return false;
    }
    return true;
}

long long gcdll(long long a, long long b) {
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// compute lcm in 64-bit, assuming no overflow for this problem
long long lcmll(long long a, long long b) {
    long long g = gcdll(a, b);
    return (a / g) * b;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 1000, "N");
    inf.readEoln();

    vector<int> A = inf.readInts(N, 1, 1000, "A_i");
    inf.readEoln();

    // Check that all A_i are distinct
    {
        vector<int> B = A;
        sort(B.begin(), B.end());
        for (int i = 1; i < N; ++i) {
            ensuref(B[i] != B[i - 1],
                    "A_i must be distinct, but value %d appears at least twice",
                    B[i]);
        }
    }

    // Global property: according to statement, it is not guaranteed that
    // a valid subset exists, so we must NOT enforce existence.
    // However, there is an implicit guarantee: any subset picked by a solution
    // as valid must have size at least 2 and LCM that is NOT prime.
    // This is not directly an input constraint, so we don't enforce anything
    // beyond checking that there exists no contradictory global promises.
    // The statement only says: output YES if possible, otherwise NO.
    // Therefore, we do not need to validate existence or bounds on answers.

    // Still, if the problem implicitly claimed that "there always exists such a subset"
    // we would verify here. In this problem, it does not, so we just avoid that.

    // But we can at least check that if *all* pairwise LCMs are prime, then any
    // supposedly valid subset cannot exist. This is only a sanity check of the
    // implied maximum size of a "forced NO" instance. This doesn't constrain input,
    // just confirms consistency; so no ensuref here.

    // Example optional computation (no constraints enforced):
    /*
    bool anyNonPrimeLCM = false;
    for (int i = 0; i < N && !anyNonPrimeLCM; ++i) {
        for (int j = i + 1; j < N && !anyNonPrimeLCM; ++j) {
            long long l = lcmll(A[i], A[j]);
            if (!isPrimeLL(l)) {
                anyNonPrimeLCM = true;
            }
        }
    }
    */

    inf.readEof();
}
