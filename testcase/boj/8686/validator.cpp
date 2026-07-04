#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(1LL, 1000000000LL, "x");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "y");
        inf.readEoln();
    }

    inf.readEof();
}
