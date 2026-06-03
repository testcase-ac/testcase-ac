#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCases = 0;
    while (true) {
        int s0 = inf.readInt(0, 6, "s_0");
        inf.readSpace();
        int s1 = inf.readInt(0, 6, "s_1");
        inf.readSpace();
        int r0 = inf.readInt(0, 6, "r_0");
        inf.readSpace();
        int r1 = inf.readInt(0, 6, "r_1");
        inf.readEoln();

        if (s0 == 0 && s1 == 0 && r0 == 0 && r1 == 0) {
            break;
        }

        ensuref(s0 >= 1 && s1 >= 1 && r0 >= 1 && r1 >= 1,
                "non-terminating test case %d must contain dice faces from 1 to 6",
                testCases + 1);
        ++testCases;
        // CHECK: the statement gives no test-case limit; use the local default cap.
        ensuref(testCases <= 100000, "too many test cases: %d", testCases);
    }

    ensuref(testCases > 0, "input must contain at least one test case before the terminator");
    inf.readEof();
}
