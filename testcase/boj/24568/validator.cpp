#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R: number of regular boxes (each holds 8 cupcakes), R >= 0
    // No explicit upper bound given; assume a reasonable cap to avoid overflow.
    // Since we must simulate and total cupcakes >= 28, but no upper limit in
    // statement, we conservatively allow up to 10^9 to stay within 64-bit safe range.
    long long R = inf.readLong(0LL, 1000000000LL, "R");
    inf.readEoln();

    // Read S: number of small boxes (each holds 3 cupcakes), S >= 0
    long long S = inf.readLong(0LL, 1000000000LL, "S");
    inf.readEoln();

    // Validate the implied global constraint:
    // There are "a total of at least 28 cupcakes."
    // Total cupcakes = 8*R + 3*S >= 28
    __int128 total = (__int128)8 * R + (__int128)3 * S;
    ensuref(total >= 28, "Total cupcakes must be at least 28, but got %lld",
            (long long)total);

    // Also ensure no overflow into negative with given bounds (sanity check)
    ensuref(total <= (__int128)8 * 1000000000LL + (__int128)3 * 1000000000LL,
            "Total cupcakes overflowed expected range");

    inf.readEof();
}
