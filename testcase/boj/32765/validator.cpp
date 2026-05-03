#include "testlib.h"

using namespace std;

// Compute minimal salary for employee i given base X, satisfying:
// 1) salary[i] > salary[i-1]
// 2) salary[i] is a multiple of i
// We only need salary at a single index A, but we may need to simulate from 1 to A.
// Use 64-bit to avoid overflow in intermediate computations.
long long computeSalaryAt(long long X, long long A) {
    long long prev = X; // salary[0]
    for (long long i = 1; i <= A; ++i) {
        // Smallest multiple of i that is >= prev+1
        long long need = prev + 1;
        long long mult = (need + i - 1) / i; // ceil(need / i)
        long long cur = mult * i;
        prev = cur;
    }
    return prev;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_Q = 100000;

    // First line: X and Q
    long long X = inf.readLong(1LL, 1000000000LL, "X");
    inf.readSpace();
    int Q = inf.readInt(1, MAX_Q, "Q");
    inf.readEoln();

    vector<long long> A(Q);
    long long maxA = 0;

    for (int i = 0; i < Q; ++i) {
        A[i] = inf.readLong(1LL, 1000000000LL, "A_i");
        inf.readEoln();
        if (A[i] > maxA) maxA = A[i];
    }

    // Global property check:
    // The problem description effectively assumes that for all queried employees,
    // a finite salary exists satisfying constraints when 0-th employee has salary X.
    // For this infinite linear chain with strictly increasing salaries and
    // divisibility constraints, the constructive greedy algorithm always yields
    // a finite salary. We verify that our construction
    // stays within 64-bit signed range for all required employees.
    //
    // NOTE: We only need correctness for the given constraints; if salary overflows
    // 64-bit, then the instance violates the intended bounds (though bounds are
    // not explicitly given, we enforce feasibility within signed 64-bit).
    if (maxA > 0) {
        long long maxIndexToSimulate = maxA;
        long long prev = X;
        for (long long i = 1; i <= maxIndexToSimulate; ++i) {
            long long need = prev + 1;
            // guard overflow in (need + i - 1)
            __int128 tmp = ( (__int128)need + (__int128)i - 1 );
            long long numer = (long long)tmp;
            long long mult = numer / i;
            __int128 cur128 = (__int128)mult * (__int128)i;
            ensuref(cur128 <= ( (__int128)LLONG_MAX ),
                    "Salary overflow at employee index %lld (exceeds 64-bit signed)", i);
            long long cur = (long long)cur128;
            prev = cur;
        }
    }

    inf.readEof();
}
