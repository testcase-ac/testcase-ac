#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 2000, "N");
    inf.readSpace();
    int m = inf.readInt(3, 4000, "M");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int x = inf.readInt(1, n, "x_j");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_j");
        inf.readSpace();
        int t = inf.readInt(1, 100000, "t_j");
        inf.readEoln();

        ensuref(x != y, "self-loop at road %d: %d -> %d", i, x, y);
        ensuref(edges.insert({x, y}).second,
                "duplicate directed road at road %d: %d -> %d", i, x, y);
        (void)t;
    }

    for (int i = 1; i <= n; ++i) {
        int c = inf.readInt(0, 1, "c_i");
        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
        if (i == 1 || i == n) {
            ensuref(c == 0, "c_%d must be 0, found %d", i, c);
        }
    }

    inf.readLong(1, 1000000000LL, "a");
    inf.readSpace();
    inf.readLong(1, 1000000000LL, "b");
    inf.readEoln();
    inf.readEof();

    return 0;
}
