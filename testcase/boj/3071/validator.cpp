#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not give an upper bound for T; cap it at the
    // local default for unspecified test case counts.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);
        inf.readLong(-(1LL << 30), 1LL << 30, "n");
        inf.readEoln();
    }

    inf.readEof();
}
