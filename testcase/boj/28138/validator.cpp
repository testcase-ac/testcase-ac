#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000000LL, "N");
    inf.readSpace();
    inf.readLong(0LL, n - 1, "R");
    inf.readEoln();
    inf.readEof();
}
