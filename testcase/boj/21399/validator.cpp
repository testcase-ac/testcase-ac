#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 15, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(4, 29999, "n");
        inf.readEoln();
        ensuref(n % 3 == 1, "n must be congruent to 1 modulo 3, got %d", n);

        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            inf.readLong(1LL, 1000000000LL, "v_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
