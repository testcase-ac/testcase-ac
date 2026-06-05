#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int m = inf.readInt(1, 10000, "M");
        inf.readEoln();

        for (int i = 0; i < m; ++i) {
            inf.readInt(1, 10000, "a_i");
            if (i % 10 == 9 || i == m - 1) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
