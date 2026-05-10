#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N
    int N = inf.readInt(1, 500, "N");
    inf.readEoln();

    // P array
    vector<int> P(N);
    for (int i = 0; i < N; ++i) {
        P[i] = inf.readInt(1, N, "P_i");
        if (i + 1 < N) inf.readSpace();
    }
    inf.readEoln();

    // Check all P_i are distinct
    {
        vector<int> freq(N + 1, 0);
        for (int i = 0; i < N; ++i) {
            ensuref(freq[P[i]] == 0,
                    "P_i values must be distinct, but value %d appears multiple times",
                    P[i]);
            freq[P[i]] = 1;
        }
    }

    // Optional: verify that P is a permutation of [1..N]
    // (follows from range and distinctness, but we can assert it explicitly)
    for (int v = 1; v <= N; ++v) {
        // freq[v] must be 1, as checked above
        // No extra work needed; just sanity.
        // If you want, you can assert again:
        // ensuref(freq[v] == 1, "Value %d missing in permutation P", v);
    }

    inf.readEof();
}
