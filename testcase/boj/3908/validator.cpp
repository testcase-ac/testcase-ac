#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The BOJ Korean statement and materialized sample use a leading test count;
    // the English legacy variant describes a 0 0 sentinel format.
    // CHECK: The statement gives no upper bound for T; this cap keeps input size practical.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        inf.readInt(1, 1120, "n");
        inf.readSpace();
        inf.readInt(1, 14, "k");
        inf.readEoln();
    }

    inf.readEof();
}
