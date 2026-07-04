#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long k = inf.readLong(1LL, 1000000000000000000LL, "k");
    inf.readSpace();
    long long a = inf.readLong(1LL, 1000000000000000000LL, "a");
    inf.readSpace();
    long long b = inf.readLong(1LL, 1000000000000000000LL, "b");
    inf.readEoln();

    ensuref(a <= b, "expected a <= b, got a=%lld and b=%lld", a, b);

    inf.readEof();
}
