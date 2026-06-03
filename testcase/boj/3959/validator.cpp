#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 159999, "t");
    inf.readEoln();

    for (int case_id = 1; case_id <= t; ++case_id) {
        setTestCase(case_id);

        inf.readInt(1, 500, "j");
        inf.readSpace();
        inf.readInt(1, 500, "p");
        inf.readSpace();
        inf.readInt(1, 500, "H");
        inf.readSpace();
        inf.readInt(1, 500, "L");
        inf.readEoln();
    }

    inf.readEof();
}
