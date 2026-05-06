#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        long long xA = inf.readLong(1LL, 1000000000LL, "x_A");
        inf.readSpace();
        long long yA = inf.readLong(1LL, 1000000000LL, "y_A");
        inf.readSpace();
        long long xC = inf.readLong(1LL, 1000000000LL, "x_C");
        inf.readSpace();
        long long yC = inf.readLong(1LL, 1000000000LL, "y_C");
        inf.readSpace();
        long long v  = inf.readLong(1LL, 1000000000LL, "v");
        inf.readEoln();

        ensuref(xA != xC || yA != yC,
                "A and C must be at different positions, but both are (%lld, %lld)",
                xA, yA);

        // No further global properties to check: the statement does not
        // guarantee things like finiteness of the answer for all inputs,
        // only describes when to output -1, which is solution logic.
    }

    inf.readEof();
}
