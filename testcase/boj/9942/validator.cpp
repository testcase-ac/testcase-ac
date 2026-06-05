#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_CASES = 100000;
    int caseCount = 0;

    while (!inf.seekEof()) {
        ++caseCount;
        ensuref(caseCount <= MAX_CASES, "too many cases: %d > %d", caseCount, MAX_CASES);

        inf.readInt(1, 1000, "N");
        inf.readEoln();
    }

    ensuref(caseCount > 0, "input must contain at least one case");
    inf.readEof();
}
