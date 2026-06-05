#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 499, "N");
    inf.readEoln();

    ensuref(n % 2 == 1, "N must be odd: %d", n);

    inf.readEof();
}
