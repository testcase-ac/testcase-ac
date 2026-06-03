#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 50, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100, "M");
    inf.readSpace();
    int l = inf.readInt(100, 1000, "L");
    inf.readEoln();

    ensuref(n + m < l, "N + M must be less than L: N=%d M=%d L=%d", n, m, l);

    if (n == 0) {
        inf.readEoln();
    } else {
        vector<int> positions = inf.readInts(n, 1, l - 1, "position");
        inf.readEoln();

        set<int> seen;
        for (int i = 0; i < n; ++i) {
            ensuref(seen.insert(positions[i]).second,
                    "duplicate position at index %d: %d", i + 1, positions[i]);
        }
    }

    inf.readEof();
}
