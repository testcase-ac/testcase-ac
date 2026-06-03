#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(1LL, 1000000000LL, "F_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "C_i");
        inf.readEoln();
    }

    int m = inf.readInt(1, 50, "m");
    inf.readEoln();

    for (int case_num = 1; case_num <= m; ++case_num) {
        setTestCase(case_num);
        inf.readLong(1LL, 1000000000LL, "V");
        inf.readSpace();
        inf.readInt(1, 1000, "T");
        inf.readEoln();
    }

    inf.readEof();
}
