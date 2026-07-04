#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives only t <= 8000. Require at least one testcase
    // because an empty set of cases would make the input instance vacuous.
    int t = inf.readInt(1, 8000, "t");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 40000, "n");
        inf.readSpace();
        long long s = inf.readLong(0LL, 1000000000LL, "s");
        inf.readSpace();
        int k = inf.readInt(1, n, "k");
        inf.readEoln();
    }

    inf.readEof();
}
