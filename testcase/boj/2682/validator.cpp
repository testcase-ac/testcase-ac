#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        // CHECK: The Korean statement and official sample use "n k" per case;
        // the English variant describes an extra data set number.
        int n = inf.readInt(1, 20, "n");
        inf.readSpace();
        int k = inf.readInt(1, n, "k");
        inf.readEoln();
    }

    inf.readEof();
}
