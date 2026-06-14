#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int r = inf.readInt(1, 50, "R");
        inf.readSpace();
        int c = inf.readInt(1, 50, "C");
        inf.readEoln();

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                inf.readInt(1, 1000, "H_ij");
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}
