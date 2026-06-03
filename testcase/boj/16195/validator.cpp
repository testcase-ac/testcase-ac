#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not specify T's upper bound; use the local default.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int case_index = 1; case_index <= t; ++case_index) {
        setTestCase(case_index);

        int n = inf.readInt(1, 1000, "n");
        inf.readSpace();
        int m = inf.readInt(1, n, "m");
        inf.readEoln();
    }

    inf.readEof();
}
