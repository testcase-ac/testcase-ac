#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    set<int> positions;
    for (int i = 0; i < n; ++i) {
        int l = inf.readInt(1, 1000, "L_i");
        inf.readSpace();
        inf.readInt(1, 1000, "H_i");
        inf.readEoln();

        // CHECK: duplicate left positions would make unit-width pillars overlap.
        ensuref(positions.insert(l).second,
                "duplicate pillar left position at line %d: %d", i + 2, l);
    }

    inf.readEof();
}
