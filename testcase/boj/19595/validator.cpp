#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int case_idx = 1; case_idx <= t; ++case_idx) {
        setTestCase(case_idx);

        int a = inf.readInt(3, 100000, "A");
        inf.readSpace();
        int k = inf.readInt(2, a - 1, "k");
        inf.readEoln();
    }

    inf.readEof();
}
