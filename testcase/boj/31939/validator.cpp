#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MOD = 998244353;

    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int R = inf.readInt(1, 100000000, "R");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        int x = inf.readInt(-100000000, 100000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-100000000, 100000000, "y_i");
        inf.readEoln();

        // No extra geometric or probabilistic constraints are guaranteed
        // by the statement besides the numeric bounds, so we do not
        // restrict positions (including possibly at the origin),
        // and we do not attempt to verify rationality of the expectation
        // or the non-divisibility of the denominator by MOD here.
    }

    inf.readEof();
}
