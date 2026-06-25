#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long sumK = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readInt(0, 1000000000, "N");
        inf.readSpace();
        int k = inf.readInt(1, 200000, "K");
        inf.readEoln();

        sumK += k;
        // CHECK: The English statement says "in one test case"; with T cases,
        // this is interpreted as the sum of K over the whole input file.
        ensuref(sumK <= 200000, "sum of K exceeds 200000 at case %d", tc);
    }

    inf.readEof();
    return 0;
}
