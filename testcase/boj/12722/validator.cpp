#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(10, 10, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int k = inf.readInt(1, 1000000, "K");
        inf.readEoln();

        int n = inf.readInt(1, 100, "n");
        for (int i = 1; i <= n; ++i) {
            inf.readSpace();
            inf.readInt(1, k, "d_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
