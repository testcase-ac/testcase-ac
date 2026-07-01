#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 50000, "T");
    inf.readEoln();

    for (int i = 1; i <= T; ++i) {
        setTestCase(i);

        long long a = inf.readLong(1LL, 1000000000000000000LL, "a");
        inf.readSpace();
        long long b = inf.readLong(a, 1000000000000000000LL, "b");
        inf.readSpace();
        inf.readInt(2, 10, "m");
        inf.readSpace();
        inf.readInt(1, 100, "n");
        inf.readEoln();
    }

    inf.readEof();
}
