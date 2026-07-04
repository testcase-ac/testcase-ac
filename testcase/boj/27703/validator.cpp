#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound t. Cap it so validation has a
    // practical aggregate limit while still allowing many small test cases.
    int testCount = inf.readInt(1, 100000, "t");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        setTestCase(caseIndex);

        inf.readEoln();

        int rows = inf.readInt(1, 100, "r");
        inf.readSpace();
        int cols = inf.readInt(1, 100, "c");
        inf.readEoln();

        int redRow = inf.readInt(1, rows, "r_r");
        inf.readSpace();
        int redCol = inf.readInt(1, cols, "c_r");
        inf.readEoln();

        int blueRow = inf.readInt(1, rows, "r_b");
        inf.readSpace();
        int blueCol = inf.readInt(1, cols, "c_b");
        inf.readEoln();

        ensuref(redRow != blueRow || redCol != blueCol,
                "case %d has identical red and blue squares: (%d, %d)",
                caseIndex,
                redRow,
                redCol);
    }

    inf.readEof();
}
