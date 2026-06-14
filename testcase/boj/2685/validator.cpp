#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int caseNum = 1; caseNum <= t; ++caseNum) {
        setTestCase(caseNum);

        // CHECK: the English variant mentions a data set number, but the
        // original Korean statement and official sample use only B X Y.
        int b = inf.readInt(2, 2000000, "B");
        inf.readSpace();
        int x = inf.readInt(0, 2000000, "X");
        inf.readSpace();
        int y = inf.readInt(0, 2000000, "Y");
        inf.readEoln();
    }

    inf.readEof();
}
