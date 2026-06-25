#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int case_idx = 1; case_idx <= t; ++case_idx) {
        setTestCase(case_idx);

        inf.readInt(1, 10, "n");
        inf.readSpace();
        inf.readInt(1, 100000, "k");
        inf.readEoln();
    }

    inf.readEof();
}
