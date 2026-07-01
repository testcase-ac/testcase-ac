#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 500, "T");
    inf.readEoln();

    for (int t = 1; t <= T; ++t) {
        setTestCase(t);

        // CHECK: The statement only writes K <= 10^18, but K is a row number.
        inf.readLong(1LL, 1000000000000000000LL, "K");
        inf.readEoln();
    }

    inf.readEof();
}
