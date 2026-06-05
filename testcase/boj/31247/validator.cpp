#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_VALUE = 1000000000000000000LL;

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        inf.readLong(1LL, MAX_VALUE, "N");
        inf.readSpace();
        inf.readLong(0LL, MAX_VALUE, "K");
        inf.readEoln();
    }

    inf.readEof();
}
