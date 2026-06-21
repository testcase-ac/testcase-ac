#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int z = inf.readInt(1, 30, "z");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= z; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 200000, "n");
        inf.readSpace();
        inf.readInt(1, 1000000000, "k");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= 500000, "sum of n exceeds 500000 at test case %d", tc);

        for (int i = 1; i <= n; ++i) {
            if (i > 1) {
                inf.readSpace();
            }
            inf.readInt(1, 1000000000, "a_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
