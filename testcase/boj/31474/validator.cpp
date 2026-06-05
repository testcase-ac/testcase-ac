#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 28, "N");
    inf.readEoln();
    ensuref(n % 2 == 0, "N must be even: %d", n);

    inf.readEof();
}
