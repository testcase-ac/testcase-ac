#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000000LL, "N");
    inf.readSpace();
    long long m = inf.readLong(n, 1000000000000LL, "M");
    inf.readEoln();
    inf.readEof();
}
