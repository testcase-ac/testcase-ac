#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readEoln();
    ensuref(n % 100 != 99, "N must not end in 99: %d", n);
    inf.readEof();
}
