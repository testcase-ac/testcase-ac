#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    long long m = inf.readLong(1LL, 1000000000LL, "M");
    inf.readEoln();

    inf.readLongs(n, 1LL, m, "a_i");
    inf.readEoln();

    inf.readEof();
}
