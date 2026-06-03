#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        int n = inf.readInt(0, 10000000, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++caseCount;
        setTestCase(caseCount);
        ensuref(n >= 1, "n must be positive before the terminating zero");
    }

    inf.readEof();
}
