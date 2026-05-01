#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    const int MAX_N = 100000;
    const int MAX_P = 1000000;

    long long totalN = 0;

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        int N = inf.readInt(1, MAX_N, "N");
        inf.readSpace();
        int PA = inf.readInt(0, MAX_P, "P_A");
        inf.readSpace();
        int PB = inf.readInt(0, MAX_P, "P_B");
        inf.readEoln();

        ensuref(PA != PB, "P_A must be different from P_B (case %d)", tc + 1);

        vector<int> X = inf.readInts(N, 1, MAX_P - 1, "X_i");
        inf.readEoln();

        int lo = min(PA, PB);
        int hi = max(PA, PB);

        for (int i = 0; i < N; ++i) {
            int xi = X[i];
            ensuref(lo < xi && xi < hi,
                    "X_%d=%d must satisfy min(P_A,P_B) < X_i < max(P_A,P_B) "
                    "(got [%d,%d]) in case %d",
                    i + 1, xi, lo, hi, tc + 1);
        }

        totalN += N;
        ensuref(totalN <= 100000LL,
                "Sum of N over all test cases exceeds 100000 (current sum = %lld)",
                totalN);
    }

    inf.readEof();
}
