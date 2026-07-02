#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseNum = 1; caseNum <= t; ++caseNum) {
        setTestCase(caseNum);

        int c = inf.readInt(1, 40, "C");
        inf.readSpace();
        inf.readInt(1, c, "N");
        inf.readEoln();
    }

    inf.readEof();
}
