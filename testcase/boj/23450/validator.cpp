#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int case_id = 1; case_id <= t; ++case_id) {
        setTestCase(case_id);

        int n = inf.readInt(1, 100, "n");
        inf.readSpace();
        int m = inf.readInt(1, 100, "m");
        inf.readEoln();
    }

    inf.readEof();
}
