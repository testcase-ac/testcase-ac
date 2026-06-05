#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The Korean BOJ statement/sample use unlabeled cases, while the English
    // original has labeled cases and states at most 1000 instances.
    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int case_id = 1; case_id <= t; ++case_id) {
        setTestCase(case_id);
        inf.readInt(1, 2147483647, "N");
        inf.readEoln();
    }

    inf.readEof();
}
