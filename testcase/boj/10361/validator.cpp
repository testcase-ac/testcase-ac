#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 1000, "N");
        inf.readSpace();
        int k = inf.readInt(1, 1000, "K");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            inf.readInt(0, 1, "sequence_i");
            inf.readEoln();
        }
    }

    inf.readEof();
}
