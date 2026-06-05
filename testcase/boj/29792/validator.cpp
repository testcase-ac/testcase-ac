#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 49, "N");
    inf.readSpace();
    int m = inf.readInt(1, n, "M");
    inf.readSpace();
    int k = inf.readInt(1, 13, "K");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readLong(1LL, 100000000000LL, "D");
        inf.readEoln();
    }

    for (int i = 0; i < k; ++i) {
        inf.readLong(1LL, 266000000000LL, "P");
        inf.readSpace();
        inf.readInt(1, 1596506, "Q");
        inf.readEoln();
    }

    inf.readEof();
}
