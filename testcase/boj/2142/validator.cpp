#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 500, "N");
        inf.readSpace();
        int m = inf.readInt(1, 500, "M");
        inf.readEoln();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                inf.readInt(-1000000, 1000000, "A_i_j");
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}
