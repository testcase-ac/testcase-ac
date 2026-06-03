#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: the statement does not bound the number of datasets; use the local
    // default cap for unspecified testcase counts.
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int t = 1; t <= n; ++t) {
        setTestCase(t);

        int a1 = inf.readInt(1, 1000, "A1");
        inf.readSpace();
        int p1 = inf.readInt(1, 1000, "P1");
        inf.readEoln();

        int r1 = inf.readInt(1, 1000, "R1");
        inf.readSpace();
        int p2 = inf.readInt(1, 1000, "P2");
        inf.readEoln();

        (void)a1;
        (void)p1;
        (void)r1;
        (void)p2;
    }

    inf.readEof();
}
