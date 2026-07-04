#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long maxPlate = 10000000000000000LL;

    long long a = inf.readLong(1LL, maxPlate, "A");
    inf.readSpace();
    long long b = inf.readLong(1LL, maxPlate, "B");
    inf.readEoln();
    ensuref(a <= b, "A must not exceed B: A=%lld, B=%lld", a, b);

    inf.readEof();
}
