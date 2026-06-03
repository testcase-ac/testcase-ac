#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int case_idx = 1; case_idx <= t; ++case_idx) {
        setTestCase(case_idx);

        int n = inf.readInt(1, 100000, "N");
        inf.readEoln();

        inf.readInts(n, 4, 1000000, "S_i");
        inf.readEoln();
    }

    inf.readEof();
}
