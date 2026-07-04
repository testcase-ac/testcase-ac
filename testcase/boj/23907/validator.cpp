#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    int largeCases = 0;
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 100000, "N");
        inf.readEoln();

        if (n > 1000) {
            ++largeCases;
            ensuref(largeCases <= 5,
                    "more than 5 cases have N > 1000: case %d has N=%d",
                    caseIndex, n);
        }

        inf.readInts(n, -100, 100, "A_i");
        inf.readEoln();
    }

    inf.readEof();
}
