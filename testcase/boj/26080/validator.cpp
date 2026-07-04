#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int d = inf.readInt(1, 200000, "d");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000000000000LL, "k");
    inf.readEoln();

    ensuref(d % 2 == 0, "d must be even, found %d", d);

    inf.readEof();
}
