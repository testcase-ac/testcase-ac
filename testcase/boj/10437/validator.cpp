#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct State {
    long long x, y;
    int dir; // 0=right,1=up,2=left,3=down
    int lastLen;
    long long sumLen;
    vector<int> seq;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int P = inf.readInt(1, 1000, "P");
    inf.readEoln();

    // Precompute for all (x,y) in [1,10000]^2 the existence and minimal steps constraint (<=22)
    // as implied by statement: "for all reachable points, there is a path with <=22 segments".
    // We will verify that any reachable point we discover indeed has some path with <=22 steps,
    // and also use this to bound search in the per-test check.
    // However, exhaustive 10000x10000 is impossible; instead we only check per test case.
    // The statement's global property: reachable points have a solution with <=22 segments.
    // We will enforce this by search bounded to 22 steps and ensure that if our bounded
    // search cannot find a path, then we treat it as NO PATH; we do NOT need to verify
    // the statement for all possible points outside input.

    // For validator: we must ensure that for each test that claims reachability (solution output),
    // the bound holds. But validator doesn't see output. Therefore, the only
    // global property we can check is internal consistency: if there exists ANY path at all,
    // then there must exist one with <=22 segments. We can search up to some safe bound
    // greater than 22 (e.g., 23 or 24) and ensure we never find a path using >22 segments.
    // That would be extremely expensive for arbitrary (x,y). So we instead accept statement
    // as given and *do not* attempt full global verification because validator runs once
    // per input, and the constraint is about outputs of solutions, not about the raw input
    // structure. Thus we skip heavy global checks here.

    for (int tc = 0; tc < P; ++tc) {
        int T = inf.readInt(0, (int)2e9, "T"); // problem does not specify range; use int32
        inf.readSpace();
        int x = inf.readInt(1, 10000, "x");
        inf.readSpace();
        int y = inf.readInt(1, 10000, "y");
        inf.readEoln();

        // T is just a label; no requirement it is consecutive or unique is stated.
        // x,y are coordinates in first quadrant with given bounds. No further structure
        // (like reachability) must be enforced by validator.
    }

    inf.readEof();
}
