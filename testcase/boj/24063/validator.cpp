#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int mConstraints = inf.readInt(1, 1000000, "M");
    inf.readSpace();
    long long modValue = inf.readLong(2LL, 1000000000LL, "m");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(1, 10000, format("X_%d", i).c_str());
    }
    inf.readEoln();

    for (int i = 1; i <= mConstraints; ++i) {
        inf.readInt(1, n, format("a_%d", i).c_str());
        inf.readSpace();
        inf.readInt(1, n, format("b_%d", i).c_str());
        inf.readSpace();
        inf.readLong(0LL, modValue - 1, format("c_%d", i).c_str());
        inf.readEoln();
    }

    inf.readEof();
}
