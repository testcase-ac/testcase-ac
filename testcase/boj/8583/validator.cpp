#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_VALUE = 1000000000000000000LL;

    long long a = inf.readLong(1LL, MAX_VALUE, "a");
    inf.readSpace();
    long long b = inf.readLong(1LL, MAX_VALUE, "b");
    inf.readEoln();

    ensuref(a <= b, "expected a <= b, got a=%lld and b=%lld", a, b);

    inf.readEof();
}
