#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();

    // Read problem type: 1 or 2
    int type = inf.readInt(1, 2, "type");
    inf.readSpace();

    // Precompute factorials up to 20!
    static long long fact[21];
    fact[0] = 1;
    for (int i = 1; i <= 20; i++) {
        __int128 tmp = (__int128)fact[i - 1] * i;
        fact[i] = (long long)tmp;
    }

    if (type == 1) {
        // Subproblem 1: read k in [1, N!]
        long long k = inf.readLong(1LL, fact[N], "k");
        (void)k;
        inf.readEoln();
    } else {
        // Subproblem 2: read a permutation of size N
        vector<int> perm = inf.readInts(N, 1, N, "perm");
        inf.readEoln();
        vector<char> seen(N+1, false);
        for (int i = 0; i < N; i++) {
            int v = perm[i];
            ensuref(!seen[v],
                    "Duplicate element in permutation at position %d: %d",
                    i+1, v);
            seen[v] = true;
        }
    }

    inf.readEof();
    return 0;
}
