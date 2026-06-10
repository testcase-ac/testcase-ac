#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long maxYear = 281474976710656LL;

    int p = inf.readInt(1, 1000, "P");
    inf.readEoln();

    for (int i = 1; i <= p; ++i) {
        setTestCase(i);

        // CHECK: The statement calls K an integer data set number but gives no
        // upper bound. Keep it positive and within ordinary 32-bit contest IDs.
        inf.readInt(1, 1000000000, "K");
        inf.readSpace();
        inf.readLong(1LL, maxYear, "Y");
        inf.readEoln();
    }

    inf.readEof();
}
