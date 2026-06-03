#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readSpace();
    int k = inf.readInt(1, 3, "K");
    inf.readEoln();

    ensuref(k <= n, "K must not exceed N: K=%d, N=%d", k, n);

    set<pair<int, int>> positions;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(0, 100000, "X_i");
        inf.readSpace();
        int y = inf.readInt(0, 100000, "Y_i");
        inf.readEoln();

        ensuref(positions.insert({x, y}).second,
                "duplicate house position at index %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
}
