#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int P = inf.readInt(1, 10000, "P");
    inf.readEoln();

    for (int tc = 1; tc <= P; ++tc) {
        setTestCase(tc);

        // CHECK: the statement names K as a decimal data set number but gives no bound.
        inf.readInt(0, 1000000000, "K");
        inf.readSpace();
        int S = inf.readInt(2, 100, "S");
        inf.readEoln();

        ensuref(S % 2 == 0, "S must be even, got %d", S);
    }

    inf.readEof();
}
