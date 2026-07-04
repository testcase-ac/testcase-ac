#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (!inf.seekEof()) {
        ++caseCount;
        setTestCase(caseCount);
        inf.readInt(3, 9999999, "n");
        ensuref(caseCount <= 100, "too many cases: %d", caseCount);
    }

    ensuref(caseCount > 0, "input must contain at least one case");
    inf.readEof();
}
