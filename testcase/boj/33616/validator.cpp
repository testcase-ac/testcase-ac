#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

struct State {
    int p, q;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    // To check the statement claim that for given inputs,
    // the answer (minimal number of commands) always exists and is small,
    // we will explicitly search minimal K up to some small bound.
    // However, the original statement does not actually guarantee existence;
    // it only asks to print -1 if impossible.
    // So we must NOT reject inputs where it is impossible.
    // Thus we do NOT enforce any "always possible" property here.
    //
    // What we *can* safely validate from statement:
    //  - a, b are integers with 0 <= a, b < 2^30, a != b.
    //  - No further global constraints are specified.

    const int MAX_AB = (1 << 30) - 1;

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        int a = inf.readInt(0, MAX_AB, "a");
        inf.readSpace();
        int b = inf.readInt(0, MAX_AB, "b");
        inf.readEoln();

        ensuref(a != b, "a must not be equal to b in test case %d (got %d %d)",
                tc + 1, a, b);

        // No further semantic/global checks are required from validator's perspective.
        // The problem does not guarantee solvability nor bound the minimal K.
        // Hence we must not enforce any such property.
    }

    inf.readEof();
}
