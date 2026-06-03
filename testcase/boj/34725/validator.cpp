#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 1000, "M");
    inf.readEoln();

    ensuref(n % 2 == 0, "N must be even: %d", n);
    ensuref(m % 2 == 0, "M must be even: %d", m);

    inf.readEof();
}
