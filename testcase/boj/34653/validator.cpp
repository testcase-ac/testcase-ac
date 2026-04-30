#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 2;
    const int N_MAX = 200000;
    const int Q_MIN = 1;
    const int Q_MAX = 200000;
    const long long COORD_MIN = 1LL;
    const long long COORD_MAX = 1000000000LL;

    // Read N
    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readEoln();

    vector<long long> L(N), H(N);

    // Read buildings
    for (int i = 0; i < N; ++i) {
        L[i] = inf.readLong(COORD_MIN, COORD_MAX, "L_i");
        inf.readSpace();
        H[i] = inf.readLong(COORD_MIN, COORD_MAX, "H_i");
        inf.readEoln();

        if (i > 0) {
            ensuref(L[i - 1] < L[i],
                    "L_i must be strictly increasing: L[%d]=%lld, L[%d]=%lld",
                    i, L[i - 1], i + 1, L[i]);
        }
    }

    // Read Q
    int Q = inf.readInt(Q_MIN, Q_MAX, "Q");
    inf.readEoln();

    // d_i must satisfy L1 < d_i < L_N and d_i != any L_i
    long long L1 = L.front();
    long long LN = L.back();

    // For quick check d_i != any L_i, use set
    // (O(Q log N), acceptable for validator)
    set<long long> buildingPos(L.begin(), L.end());

    for (int i = 0; i < Q; ++i) {
        long long d = inf.readLong(L1 + 1, LN - 1, "d_i");
        inf.readEoln();

        ensuref(buildingPos.find(d) == buildingPos.end(),
                "d_i at index %d must not equal any L_j, but d_i=%lld is a building position",
                i + 1, d);
    }

    inf.readEof();
}
