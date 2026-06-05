#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long a = inf.readLong(1LL, 1000000000000000000LL, "a");
    inf.readSpace();
    long long b = inf.readLong(1LL, 1000000000000000000LL, "b");
    inf.readEoln();

    ensuref(b <= a, "b must be at most a, got a=%lld b=%lld", a, b);

    inf.readEof();
}
