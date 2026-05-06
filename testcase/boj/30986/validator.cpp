#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The problem describes 16 tetrahedra around a 4D 16-cell.
    // There are 32 faces between adjacent tetrahedra.
    // We only need to validate that each given pair (a,b) is:
    //  - 1 <= a < b <= 16
    //  - not duplicated
    // The statement does NOT explicitly guarantee that (a,b) must correspond
    // to an actual neighboring pair in the 16-cell; it only says
    // "faces where he could not drill holes are given as (a,b)" and
    // "all given faces are not duplicated".
    // So from validator's perspective, we must not add an extra constraint
    // that (a,b) must be a real adjacency in the 16-cell, since that is not
    // clearly stated in the input format/constraints.
    //
    // Additionally, we must enforce canonical integer format and strict
    // whitespace using testlib's readInt/readSpace/readEoln.

    int N = inf.readInt(0, 32, "N");
    inf.readEoln();

    set<pair<int,int>> seen;

    for (int i = 0; i < N; ++i) {
        int a = inf.readInt(1, 16, "a");
        inf.readSpace();
        int b = inf.readInt(1, 16, "b");
        inf.readEoln();

        ensuref(a < b,
                "Line %d after N: must satisfy 1 <= a < b <= 16, got a=%d, b=%d",
                i + 2, a, b);

        pair<int,int> e = {a, b};
        ensuref(!seen.count(e),
                "Duplicate face (%d, %d) on line %d",
                a, b, i + 2);
        seen.insert(e);
    }

    inf.readEof();
}
