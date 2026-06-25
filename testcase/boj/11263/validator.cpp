#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (!inf.eof()) {
        ++cases;
        // CHECK: The statement gives no number of test cases; cap EOF-style cases locally.
        ensuref(cases <= 100000, "too many test cases: %d", cases);

        int n = inf.readInt(2, 7, "n");
        inf.readSpace();
        // CHECK: The statement does not bound s. Accept impossible sums, but cap size locally.
        int s = inf.readInt(0, 1000000000, "s");
        (void)s;
        inf.readEoln();
    }

    ensuref(cases > 0, "input must contain at least one test case");
    inf.readEof();
}
