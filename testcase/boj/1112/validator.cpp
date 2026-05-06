#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // x: decimal integer, range [-1e9, 1e9]
    // b: base, integer, 2 <= |b| <= 10, b != 0, b != 1, b != -1
    long long x = inf.readLong(-1000000000LL, 1000000000LL, "x");
    inf.readSpace();
    long long b = inf.readLong(-10LL, 10LL, "b");
    inf.readEoln();

    ensuref(b != 0, "base b must not be zero");
    ensuref(b != 1 && b != -1, "base b must satisfy 2 <= |b| <= 10, so b != 1 and b != -1");
    ensuref(llabs(b) >= 2 && llabs(b) <= 10, "base |b| must be between 2 and 10");

    // No further global properties stated that must hold for the input
    // (representation existence/uniqueness is guaranteed mathematically, not an input property).

    inf.readEof();
}
