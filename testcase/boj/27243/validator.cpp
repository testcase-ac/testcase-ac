#include "testlib.h"

using namespace std;

// Count number of 1-bits in unsigned long long
int popcount_ull(unsigned long long v) {
    return __builtin_popcountll(v);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read x: natural number, 1 <= x <= 1e18
    long long x = inf.readLong(1LL, 1000000000000000000LL, "x");
    inf.readEoln();

    // Read k: natural number, 1 <= k <= 60
    long long k = inf.readLong(1LL, 60LL, "k");
    inf.readEoln();

    // Check that an answer always exists by brute-force searching y.
    // Problem guarantees existence; validator should ensure this.
    unsigned long long ux = (unsigned long long)x;
    int target = (int)k;
    bool ok = false;

    // Upper bound for search: if k >= popcount(x), y=0 works sometimes;
    // otherwise we can always add up to a number with that popcount within
    // a reasonable bound. For safety, search up to some limit.
    // Since x <= 1e18 < 2^60 and k <= 60, we can safely search up to, say, 1<<20.
    const unsigned long long LIMIT = (1ULL << 20);
    for (unsigned long long y = 0; y <= LIMIT; ++y) {
        if (popcount_ull(ux + y) == target) {
            ok = true;
            break;
        }
    }
    ensuref(ok, "No y found with popcount(x + y) == k within search limit; input likely violates problem guarantee.");

    inf.readEof();
}
