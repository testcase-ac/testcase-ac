#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int z = inf.readInt(1, 20, "z");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= z; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 2000000, "n");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= 30000000LL,
                "total sequence length exceeds 30000000 after testcase %d: %lld",
                tc, totalN);

        inf.readInts(n, 1, 1000000, "a_i");
        inf.readEoln();
    }

    inf.readEof();
}
