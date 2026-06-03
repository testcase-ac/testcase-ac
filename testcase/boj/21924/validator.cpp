#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(2, min(1LL * n * (n - 1) / 2, 500000LL), "M");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        int c = inf.readInt(1, 1000000, "c");
        inf.readEoln();

        ensuref(a != b, "self-loop at edge %d: %d %d", i, a, b);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "duplicate edge at edge %d: %d %d with cost %d", i, a, b, c);
    }

    inf.readEof();
}
