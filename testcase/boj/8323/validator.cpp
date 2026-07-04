#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20, "t");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        inf.readInt(1, 1000000, "n_i");
        inf.readSpace();
        inf.readInt(1, 1000000, "k_i");
        inf.readEoln();
    }

    inf.readEof();
}
