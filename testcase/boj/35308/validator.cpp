#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    int sumN = 0;
    for (int caseIdx = 1; caseIdx <= t; ++caseIdx) {
        setTestCase(caseIdx);

        int n = inf.readInt(1, 100000, "N");
        inf.readSpace();
        int k = inf.readInt(1, n, "K");
        inf.readEoln();

        sumN += n;
        ensuref(sumN <= 100000, "sum of N exceeds 100000 after case %d", caseIdx);
    }

    inf.readEof();
}
