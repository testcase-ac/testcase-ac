#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();
    int k = inf.readInt(1, 1000, "K");
    inf.readEoln();

    ensuref(m % n == 0, "M must be divisible by N: M=%d, N=%d", m, n);

    inf.readEof();
}
