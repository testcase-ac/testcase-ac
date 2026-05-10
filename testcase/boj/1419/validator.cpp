#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read l
    long long l = inf.readLong(1LL, 1000000000LL, "l");
    inf.readEoln();

    // Read r
    long long r = inf.readLong(1LL, 1000000000LL, "r");
    inf.readEoln();
    ensuref(l <= r, "Constraint violation: l (%lld) must be <= r (%lld)", l, r);

    // Read k
    int k = inf.readInt(2, 5, "k");
    inf.readEoln();

    // No further input
    inf.readEof();

    return 0;
}
