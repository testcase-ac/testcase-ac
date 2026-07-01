#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(100, 100, "T");
    inf.readEoln();

    for (int caseNum = 1; caseNum <= t; ++caseNum) {
        setTestCase(caseNum);

        int k = inf.readInt(1, 5000, "K");
        inf.readEoln();

        int n = inf.readInt(1, 100, "n");
        for (int i = 1; i <= n; ++i) {
            inf.readSpace();
            inf.readInt(1, k, "d_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
