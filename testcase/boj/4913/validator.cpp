#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        int l = inf.readInt(-999999, 999999, "L");
        inf.readSpace();
        int u = inf.readInt(-999999, 999999, "U");
        inf.readEoln();

        if (l == -1 && u == -1) {
            ensuref(caseCount > 0, "input must contain at least one real test case before sentinel");
            break;
        }

        ++caseCount;
        setTestCase(caseCount);
        ensuref(l <= u, "L must be <= U, got L=%d U=%d", l, u);
    }

    inf.readEof();
}
