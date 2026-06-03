#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 20, "N");
        inf.readEoln();
        ensuref(n % 2 == 0, "N must be even, got %d", n);

        set<pair<int, int>> points;
        for (int i = 0; i < n; ++i) {
            int x = inf.readInt(-100000, 100000, "x_i");
            inf.readSpace();
            int y = inf.readInt(-100000, 100000, "y_i");
            inf.readEoln();

            ensuref(points.insert({x, y}).second,
                    "duplicate point at index %d: (%d, %d)", i + 1, x, y);
        }
    }

    inf.readEof();
}
