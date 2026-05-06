#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        long long a = inf.readLong(1LL, 1000000LL, "a");
        inf.readSpace();
        long long b = inf.readLong(1LL, 1000000LL, "b");
        inf.readSpace();
        long long c = inf.readLong(1LL, 1000000LL, "c");
        inf.readEoln();

        // No additional global constraints stated that require simulation
        // The graph is defined purely by inequalities and parity, and
        // the statement does not claim properties like connectivity
        // or guaranteed answer bounds that must be enforced here.
        //
        // Therefore, we only enforce the given numeric constraints
        // and strict formatting, which testlib already does.

        // If desired, you could add simple sanity checks like:
        // ensuref(a >= 1 && b >= 1 && c >= 1, "a,b,c must be >= 1");
        // but readLong bounds already guarantee this.
    }

    inf.readEof();
}
