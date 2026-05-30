#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        string blank = inf.readLine(".*", "blank_line");
        ensuref(blank.empty(), "test case %d must be preceded by a blank line", tc);

        int n = inf.readInt(2, 200, "n");
        inf.readSpace();
        int maxM = n * (n - 1) / 2;
        int m = inf.readInt(0, maxM, "m");
        inf.readEoln();

        set<pair<int, int>> edges;
        for (int i = 0; i < m; ++i) {
            int u = inf.readInt(1, n, "u_i");
            inf.readSpace();
            int v = inf.readInt(1, n, "v_i");
            inf.readEoln();

            ensuref(u < v, "edge %d must satisfy u_i < v_i", i + 1);
            ensuref(edges.insert({u, v}).second,
                    "duplicate edge at edge %d: %d %d", i + 1, u, v);
        }
    }

    inf.readEof();
}
