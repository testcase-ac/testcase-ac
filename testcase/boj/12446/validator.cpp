#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // T: number of test cases
    int T = inf.readInt(1, 500, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int A = inf.readInt(1, 1000, "A");
        inf.readSpace();
        int B = inf.readInt(1, 1000, "B");
        inf.readSpace();
        int C = inf.readInt(1, 1000, "C");
        inf.readEoln();

        // No extra global constraints are stated (existence of answer is trivial
        // since we are working modulo C), so nothing more to check here.
        // Bacteria count recurrence and modular exponentiation properties
        // are part of the solution, not the validator.
    }

    inf.readEof();
}
