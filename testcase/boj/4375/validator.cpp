#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (!inf.eof()) {
        // CHECK: The statement gives EOF-terminated cases with no case-count bound;
        // local policy caps such inputs at 100000 cases.
        ensuref(caseCount < 100000, "too many test cases");

        int n = inf.readInt(1, 10000, "n");
        inf.readEoln();
        ++caseCount;

        ensuref(n % 2 != 0, "n must not be divisible by 2: %d", n);
        ensuref(n % 5 != 0, "n must not be divisible by 5: %d", n);
    }

    ensuref(caseCount > 0, "input must contain at least one test case");
    inf.readEof();
}
