#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "t");
    inf.readEoln();

    for (int case_num = 1; case_num <= t; ++case_num) {
        setTestCase(case_num);

        inf.readInt(1, 30, "n");
        inf.readSpace();
        int m = inf.readInt(0, 28, "m");
        inf.readSpace();
        int k = inf.readInt(m + 1, 29, "k");
        inf.readEoln();
    }

    inf.readEof();
}
