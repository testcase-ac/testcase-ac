#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (!inf.eof()) {
        // CHECK: The statement gives EOF-terminated inputs with no line-count bound;
        // local policy caps such inputs at 100000 cases.
        ensuref(caseCount < 100000, "too many input lines");

        ++caseCount;
        setTestCase(caseCount);

        inf.readInt(1, 100000000, "n");
        inf.readEoln();
    }

    ensuref(caseCount > 0, "input must contain at least one line");
    inf.readEof();
}
