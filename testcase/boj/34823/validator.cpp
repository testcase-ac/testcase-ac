#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: three integers y, c, p
    long long y = inf.readLong(0LL, 1000000LL, "y");
    inf.readSpace();
    long long c = inf.readLong(0LL, 1000000LL, "c");
    inf.readSpace();
    long long p = inf.readLong(0LL, 1000000LL, "p");
    inf.readEoln();

    // Optional: check that the answer fits in standard int range.
    // Each "YCPC" uses 1 Y, 2 C, and 1 P.
    long long maxYCPC = min(y, min(c / 2, p));
    ensuref(maxYCPC <= 1000000000LL,
            "Computed maximum number of YCPC words (%lld) does not fit in 32-bit int",
            maxYCPC);

    inf.readEof();
}
