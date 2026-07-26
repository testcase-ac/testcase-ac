#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    int sumN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        int n = inf.readInt(1, 3000, "N");
        inf.readEoln();
        sumN += n;
        ensuref(sumN <= 3000, "sum of N exceeds 3000 after testcase %d: %d", tc, sumN);

        vector<pair<int, int>> intervals(n);
        vector<int> seen(2 * n + 1, 0);
        for (int i = 0; i < n; ++i) {
            int l = inf.readInt(1, 2 * n, "L_i");
            inf.readSpace();
            int r = inf.readInt(1, 2 * n, "R_i");
            inf.readEoln();

            ensuref(l < r, "testcase %d pair %d has L_i >= R_i: %d %d", tc, i + 1, l, r);
            ensuref(!seen[l], "testcase %d chair %d appears more than once", tc, l);
            ensuref(!seen[r], "testcase %d chair %d appears more than once", tc, r);
            seen[l] = seen[r] = 1;
            intervals[i] = {l, r};
        }

        for (int chair = 1; chair <= 2 * n; ++chair) {
            ensuref(seen[chair], "testcase %d chair %d is not occupied", tc, chair);
        }

        for (int i = 0; i < n; ++i) {
            auto [li, ri] = intervals[i];
            for (int j = i + 1; j < n; ++j) {
                auto [lj, rj] = intervals[j];
                bool crossing = (li < lj && lj < ri && ri < rj) ||
                                (lj < li && li < rj && rj < ri);
                ensuref(!crossing,
                        "testcase %d intervals %d=(%d,%d) and %d=(%d,%d) cross",
                        tc, i + 1, li, ri, j + 1, lj, rj);
            }
        }
    }

    inf.readEof();
    return 0;
}
