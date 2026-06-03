#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives only T <= 200; require at least one testcase.
    int t = inf.readInt(1, 200, "T");
    inf.readEoln();

    for (int case_index = 1; case_index <= t; ++case_index) {
        setTestCase(case_index);

        long long a = inf.readLong(0LL, 1000000000LL, "a");
        inf.readSpace();
        long long b = inf.readLong(0LL, 1000000000LL, "b");
        inf.readSpace();
        int c = inf.readInt(1, 100, "c");
        inf.readSpace();
        int d = inf.readInt(1, 100000000, "d");
        inf.readEoln();

        ensuref(1LL * c * d <= 100000000LL,
                "case %d violates c*d <= 100000000: c=%d, d=%d",
                case_index, c, d);
    }

    inf.readEof();
}
