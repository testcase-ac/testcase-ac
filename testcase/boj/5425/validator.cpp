#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_VALUE = 1000000000000000LL;

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        long long a = inf.readLong(0LL, MAX_VALUE, "a");
        inf.readSpace();
        long long b = inf.readLong(0LL, MAX_VALUE, "b");
        inf.readEoln();

        ensuref(a <= b, "expected a <= b, got a=%lld and b=%lld", a, b);
    }

    inf.readEof();
}
