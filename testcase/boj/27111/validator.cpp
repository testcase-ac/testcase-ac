#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 200000;
    const int MAXID = 200000;

    int N = inf.readInt(1, MAXN, "N");
    inf.readEoln();

    // Read records, ensuring format and ranges.
    vector<int> a(N);
    vector<int> b(N);
    for (int i = 0; i < N; ++i) {
        a[i] = inf.readInt(1, MAXID, "a_i");
        inf.readSpace();
        b[i] = inf.readInt(0, 1, "b_i");
        inf.readEoln();
    }

    // Now validate global constraints implied by statement:
    // - There exists some (possibly empty) set of missing logs that makes:
    //   * nobody inside before first log,
    //   * nobody inside after last log,
    //   * sequence is consistent with people entering/exiting.

    // We'll check that such a sequence is *possible* (not compute minimum).
    // Model:
    // For each person x:
    //   We don't know initial state (inside/outside), because earlier logs may be missing.
    //   But:
    //     - One cannot exit twice in a row without an intervening enter in *our* logs;
    //       missing logs may be between our logs, but they must keep consistency:
    //       if we see two consecutive exits for same person with no enter in between,
    //       then between those exits there must be an enter and another exit, which are missing.
    //       That is allowed. So per-person sequence alone doesn't make it impossible.
    //
    // Global constraints:
    //   Before first record: all outside.
    //   After last record: all outside.
    //
    // Because missing logs can be inserted arbitrarily before, between, and after,
    // there is always a way to adjust with extra enters/exits to satisfy start/end emptiness,
    // as long as individuals themselves can alternate properly (which is always possible
    // due to freedom of initial state).
    //
    // Therefore, there is actually no impossible input under the given numeric constraints,
    // and no extra structural impossibility to check beyond ranges and format.
    //
    // We still can add a light sanity check: that answer (min missing) is finite,
    // equivalently that no one is forced into an impossible parity pattern.
    // But because we can choose each person's initial state arbitrarily and insert
    // arbitrary missing logs, such impossibility never arises.
    //
    // So no extra ensuref is needed here.

    inf.readEof();
}
