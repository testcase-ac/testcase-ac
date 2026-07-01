#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseId = 1; caseId <= t; ++caseId) {
        setTestCase(caseId);
        inf.readLong(2LL, 1000000000000000LL, "N");
        inf.readEoln();
    }

    inf.readEof();
}
