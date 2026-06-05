#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 262144, "N");
    inf.readSpace();
    int m = inf.readInt(0, n, "M");
    inf.readSpace();
    inf.readInt(1, n, "K");
    inf.readEoln();

    ensuref((n & (n - 1)) == 0, "N must be a power of two: %d", n);

    inf.readEof();
}
