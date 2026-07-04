#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    long long totalN = 0;
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 50000, "n");
        inf.readSpace();
        int m = inf.readInt(15, 100, "m");
        inf.readEoln();

        // CHECK: The statement does not bound the number of test cases; cap aggregate N to one largest case.
        totalN += n;
        ensuref(totalN <= 50000, "sum of n exceeds 50000 after test case %d", caseIndex);

        int a = inf.readInt(1, 1000, "a");
        inf.readSpace();
        int b = inf.readInt(1, 1000, "b");
        inf.readEoln();

        inf.readInts(n, 1, 20, "x");
        inf.readEoln();
    }

    inf.readEof();
}
