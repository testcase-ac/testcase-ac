#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 50000, "T");
    inf.readEoln();

    long long totalN = 0;
    for (int t = 1; t <= T; ++t) {
        setTestCase(t);

        int N = inf.readInt(2, 100000, "N");
        inf.readEoln();

        totalN += N;
        ensuref(totalN <= 100000, "sum of N exceeds 100000 after testcase %d", t);

        inf.readInts(N, 1, 1000000000, "K_i");
        inf.readEoln();
    }

    inf.readEof();
}
