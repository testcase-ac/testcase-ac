#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not give an upper bound for T. Use the local
    // default cap for unbounded multi-case numeric inputs.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);
        inf.readInt(1, 1000000, "N");
        inf.readEoln();
    }

    inf.readEof();
}
