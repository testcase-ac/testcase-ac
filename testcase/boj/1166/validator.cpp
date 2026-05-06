#include "testlib.h"
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read input values
    long long N = inf.readLong(1LL, 1000000000LL, "N");
    inf.readSpace();
    long long L = inf.readLong(1LL, 1000000000LL, "L");
    inf.readSpace();
    long long W = inf.readLong(1LL, 1000000000LL, "W");
    inf.readSpace();
    long long H = inf.readLong(1LL, 1000000000LL, "H");
    inf.readEoln();

    // No further constraints in the statement, but we must check the global property:
    // "For the given input, the answer always exists."
    // That is, it must be possible to fit N cubes of size A x A x A into L x W x H for some A > 0.

    // Since L, W, H >= 1 and N >= 1, it's always possible to fit at least one cube of size 1x1x1,
    // as long as N <= L*W*H (which is always true for N=1).
    // For N > L*W*H, it's impossible to fit N cubes of size 1x1x1, but the constraints allow N up to 1e9 and L*W*H up to 1e27.
    // However, the problem guarantees that the answer always exists, so we don't need to check for impossibility.

    // But let's check that for the given N, L, W, H, it's possible to fit N cubes of size > 0.
    // For A very small (e.g., 1e-9), the number of cubes that fit is huge, so always possible.

    // No further global properties to check.

    inf.readEof();
}
