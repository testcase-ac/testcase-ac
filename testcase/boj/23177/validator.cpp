#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxCount = 1 << 18;
    const long long maxT = 1000000000000000000LL;

    int n = inf.readInt(1, maxCount, "n");
    inf.readSpace();
    int l = inf.readInt(1, maxCount, "l");
    inf.readSpace();
    inf.readLong(1LL, maxT, "t");
    inf.readEoln();

    for (int i = 1; i <= l; ++i) {
        inf.readInt(1, n, "a");
        inf.readSpace();
        inf.readInt(1, n, "b");
        inf.readEoln();
    }

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(0, 255, "x");
    }
    inf.readEoln();

    inf.readEof();
}
