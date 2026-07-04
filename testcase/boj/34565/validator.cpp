#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    int totalN = 0;
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 5000, "N");
        inf.readEoln();

        string s = inf.readToken("[HY?]{1,5000}", "S");
        inf.readEoln();

        ensuref((int)s.size() == n, "case %d: |S| = %d, expected N = %d",
                caseIndex, (int)s.size(), n);

        totalN += n;
        ensuref(totalN <= 5000, "sum of N exceeds 5000 after case %d: %d",
                caseIndex, totalN);
    }

    inf.readEof();
}
