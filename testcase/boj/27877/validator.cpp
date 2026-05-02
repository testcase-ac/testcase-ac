#include "testlib.h"

using namespace std;

// Compute integer square root of x (x up to about 2e14 safely in 64-bit)
long long isqrt_longlong(long long x) {
    if (x <= 0) return 0;
    long long r = (long long)sqrt((long double)x);
    while ((r + 1) * (r + 1) <= x) ++r;
    while (r * r > x) --r;
    return r;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer N, 1 <= N <= 1e14, canonical decimal
    long long N = inf.readLong(1LL, 100000000000000LL, "N");
    inf.readEoln();

    // Since the statement says "If it's impossible to merge all N cards into one deck, print -1",
    // but does NOT guarantee that it's always possible, we MUST NOT enforce existence of a plan.
    // However, we *should* check any *guaranteed* global property that appears in the statement.
    // The statement doesn't claim that some property (like possibility of full merge) always holds,
    // so we don't check that here.

    // There is no multi‑case format specified, so we assume a single test case.

    // No further structural input to validate.

    inf.readEof();
}
