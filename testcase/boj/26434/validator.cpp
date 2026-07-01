#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    int largeCases = 0;
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 400000, "N");
        inf.readEoln();

        if (n > 200) {
            ++largeCases;
        }
        ensuref(largeCases <= 30,
                "more than 30 cases have N > 200; case %d has N = %d",
                caseIndex, n);

        for (int i = 1; i <= n; ++i) {
            if (i > 1) {
                inf.readSpace();
            }
            inf.readInt(-800, 800, "A_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
