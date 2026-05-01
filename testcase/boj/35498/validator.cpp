#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 500000;
    const long long MINA = -1000000000LL;
    const long long MAXA =  1000000000LL;

    int N = inf.readInt(1, MAXN, "N");
    inf.readSpace();
    int Q = inf.readInt(1, MAXN, "Q");
    inf.readEoln();

    vector<long long> A(N + 1);
    for (int i = 1; i <= N; ++i) {
        A[i] = inf.readLong(MINA, MAXA, "A_i");
        if (i < N) inf.readSpace();
        else inf.readEoln();
    }

    bool hasType2 = false;

    // We'll simulate to additionally ensure that values do not overflow 64-bit
    // during operations (though not required by statement, it's a safety check).
    // Using long long is enough, but we'll guard via __int128 during updates.
    for (int qi = 0; qi < Q; ++qi) {
        int t = inf.readInt(1, 2, "t");
        if (t == 1) {
            inf.readSpace();
            int i = inf.readInt(1, N, "i");
            inf.readSpace();
            int j = inf.readInt(1, N, "j");
            inf.readSpace();
            long long v = inf.readLong(MINA, MAXA, "v");
            inf.readEoln();

            ensuref(i <= j, "Query %d: i (%d) must be <= j (%d)", qi + 1, i, j);

            // Simulate the range add, checking for 64-bit overflow
            for (int k = i; k <= j; ++k) {
                __int128 tmp = (__int128)A[k] + (__int128)v;
                ensuref(tmp >= ( __int128)LLONG_MIN && tmp <= ( __int128)LLONG_MAX,
                        "Value overflow at query %d, position %d", qi + 1, k);
                A[k] = (long long)tmp;
            }
        } else {
            // type 2 query: check monotone non-decreasing
            inf.readEoln();
            hasType2 = true;

            bool ok = true;
            for (int i = 1; i < N; ++i) {
                if (A[i] > A[i + 1]) {
                    ok = false;
                    break;
                }
            }
            // Statement guarantees that these queries exist and are answerable;
            // our simulation guarantees this condition is well-defined.
            (void)ok; // nothing else to enforce, as solutions will output based on this.
        }
    }

    ensuref(hasType2, "There must be at least one type-2 query");

    inf.readEof();
}
