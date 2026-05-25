#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int kMaxCoord = 10000000;
    constexpr int kMaxTotalPositions = 5000000;

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalPositions = 0;
    for (int tc = 1; tc <= T; ++tc) {
        int n = inf.readInt(1, 1000000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 1000000, "m");
        inf.readEoln();

        totalPositions += n + m;
        ensuref(totalPositions <= kMaxTotalPositions,
                "total number of house positions exceeds %d", kMaxTotalPositions);

        set<int> left;
        for (int i = 0; i < n; ++i) {
            int a = inf.readInt(-kMaxCoord, kMaxCoord, "a_i");
            inf.readEoln();
            ensuref(left.insert(a).second,
                    "duplicate left-side coordinate in test case %d: %d", tc, a);
        }

        set<int> right;
        for (int j = 0; j < m; ++j) {
            int b = inf.readInt(-kMaxCoord, kMaxCoord, "b_j");
            inf.readEoln();
            // CHECK: The Korean text says all n + m coordinates are distinct,
            // but the English original and official sample allow the same
            // y-coordinate to appear once on each side.
            ensuref(right.insert(b).second,
                    "duplicate right-side coordinate in test case %d: %d", tc, b);
        }
    }

    inf.readEof();
}
