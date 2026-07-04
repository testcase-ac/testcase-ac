#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseNo = 1; caseNo <= t; ++caseNo) {
        setTestCase(caseNo);

        int n = inf.readInt(1, 1000, "N");
        inf.readSpace();
        int k = inf.readInt(1, 1000, "K");
        inf.readEoln();

        ensuref(k == 1 || (2 <= k && k <= 1000),
                "K=%d must match one of the stated test sets", k);

        inf.readInts(n, -1000, 1000, "E_i");
        inf.readEoln();
    }

    inf.readEof();
}
