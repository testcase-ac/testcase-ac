#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000000000000LL, "N");
    inf.readSpace();
    inf.readLong(1LL, n, "M");
    inf.readEoln();
    inf.readEof();
}
