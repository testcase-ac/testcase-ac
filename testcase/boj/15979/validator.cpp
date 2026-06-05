#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long m = inf.readLong(-1000000000LL, 1000000000LL, "M");
    inf.readSpace();
    long long n = inf.readLong(-1000000000LL, 1000000000LL, "N");
    inf.readEoln();
    inf.readEof();

    (void)m;
    (void)n;
}
