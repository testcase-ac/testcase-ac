#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        int n = inf.readInt(0, 10000, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++caseCount;
        ensuref(caseCount <= 100000, "too many test cases: %d", caseCount);
    }

    inf.readEof();
}
