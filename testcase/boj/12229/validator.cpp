#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int p = inf.readInt(20, 200, "P");
        inf.readSpace();
        int q = inf.readInt(20, 200, "Q");
        inf.readSpace();
        int n = inf.readInt(1, 100, "N");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            inf.readInt(1, 200, "H_i");
            inf.readSpace();
            inf.readInt(0, 1000000, "G_i");
            inf.readEoln();
        }

        (void)p;
        (void)q;
    }

    inf.readEof();
}
