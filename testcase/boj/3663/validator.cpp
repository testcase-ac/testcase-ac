#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "t");
    inf.readEoln();

    for (int case_idx = 1; case_idx <= t; ++case_idx) {
        setTestCase(case_idx);
        inf.readToken("[A-Z]{1,1000}", "s");
        inf.readEoln();
    }

    inf.readEof();
}
