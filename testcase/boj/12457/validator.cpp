#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);
        // CHECK: The official sample includes a larger value, but this Small
        // statement's judged constraint says N <= 10000.
        inf.readInt(1, 10000, "N");
        inf.readEoln();
    }

    inf.readEof();
}
