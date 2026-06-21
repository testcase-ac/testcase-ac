#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int P = inf.readInt(1, 10000, "P");
    inf.readEoln();

    for (int tc = 1; tc <= P; ++tc) {
        setTestCase(tc);

        // CHECK: the statement names K as a decimal data set number but gives no bound.
        int K = inf.readInt(0, 1000000000, "K");
        inf.readSpace();
        int n = inf.readInt(1, 30, "n");
        inf.readSpace();
        int m = inf.readInt(0, 28, "m");
        inf.readSpace();
        int k = inf.readInt(1, 29, "k");
        inf.readEoln();

        ensuref(m < k, "expected m < k, got m=%d and k=%d for data set %d", m, k, K);
    }

    inf.readEof();
}
