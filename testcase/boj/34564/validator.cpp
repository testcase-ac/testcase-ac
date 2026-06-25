#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_N = 1000000000000000000LL;

    long long n = inf.readLong(2LL, MAX_N, "N");
    inf.readSpace();
    long long k = inf.readLong(1LL, n - 1, "K");
    inf.readEoln();
    inf.readEof();
}
