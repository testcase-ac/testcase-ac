#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(2LL, 1000000000000000000LL, "N");
    inf.readSpace();
    int m = inf.readInt(2, 10000000, "M");
    inf.readEoln();

    inf.readEof();
}
