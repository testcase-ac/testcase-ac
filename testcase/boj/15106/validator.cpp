#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long a = inf.readLong(1LL, 1000000000000LL, "a");
    inf.readSpace();
    long long b = inf.readLong(a, 1000000000000LL, "b");
    inf.readEoln();

    ensuref(b - a <= 1000000LL, "b - a must be at most 10^6, got %lld", b - a);

    inf.readEof();
}
