#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int x = inf.readInt(0, 1000000, "x");
    inf.readEoln();
    ensuref(x % 2 == 0, "x must be even, got %d", x);

    inf.readEof();
}
