#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int case_id = 1; case_id <= t; ++case_id) {
        setTestCase(case_id);

        inf.readLong(1LL, 1000000000LL, "K");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "N");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "M");
        inf.readEoln();
    }

    inf.readEof();
}
