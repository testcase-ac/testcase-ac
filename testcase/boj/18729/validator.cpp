#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound z, so use the local default cap.
    int z = inf.readInt(1, 100000, "z");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= z; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "n");
        inf.readSpace();
        int k = inf.readInt(0, n - 1, "k");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= 1000000, "total number of chests exceeds 1000000");

        inf.readInts(n, 0, 1000000000, "t_i");
        inf.readEoln();
    }

    inf.readEof();
}
