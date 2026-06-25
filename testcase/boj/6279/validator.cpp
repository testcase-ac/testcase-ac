#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound T; use the local default cap.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int case_num = 1; case_num <= t; ++case_num) {
        setTestCase(case_num);
        inf.readInt(1, 16, "N");
        inf.readEoln();
    }

    inf.readEof();
}
