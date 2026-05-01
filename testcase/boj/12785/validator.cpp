#include "testlib.h"
#include <algorithm>

using namespace std;

// Simple gcd implementation (since <numeric>::gcd may not be available)
long long mygcd(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// Compute nCk using 64-bit, enough for n <= 398 (here max n is small).
long long comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    long long res = 1;
    for (int i = 1; i <= k; ++i) {
        long long num = n - k + i;
        long long den = i;

        long long g1 = mygcd(num, den);
        num /= g1;
        den /= g1;

        long long g2 = mygcd(res, den);
        res /= g2;
        den /= g2;

        // Now den should divide res*num exactly in integer arithmetic.
        res = res * num / den;
    }
    return res;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: w, h
    int w = inf.readInt(2, 200, "w");
    inf.readSpace();
    int h = inf.readInt(2, 200, "h");
    inf.readEoln();

    // Second line: x, y
    int x = inf.readInt(1, w, "x");
    inf.readSpace();
    int y = inf.readInt(1, h, "y");
    inf.readEoln();

    // Check implied global property:
    // Path is along grid, only minimal-time paths via (x,y) are considered.
    // Steps from (1,1) to (x,y): right (x-1), up (y-1)
    int r1 = x - 1;
    int u1 = y - 1;
    // Steps from (x,y) to (w,h): right (w - x), up (h - y)
    int r2 = w - x;
    int u2 = h - y;

    long long totalSteps = (long long)r1 + u1 + r2 + u2;
    long long manhattan = (long long)(w - 1) + (h - 1);

    // Ensure toast is on some minimal path between home and school
    ensuref(totalSteps == manhattan,
            "Point (%d,%d) must lie on some shortest path from (1,1) to (%d,%d); "
            "got path length %lld vs Manhattan distance %lld",
            x, y, w, h, totalSteps, manhattan);

    // Count minimal paths for both segments to ensure > 0 and safe
    long long ways1 = comb(r1 + u1, r1);
    long long ways2 = comb(r2 + u2, r2);

    ensuref(ways1 > 0, "No path from (1,1) to toast (%d,%d)", x, y);
    ensuref(ways2 > 0, "No path from toast (%d,%d) to school (%d,%d)", x, y, w, h);

    __int128 totalWays = (__int128)ways1 * (__int128)ways2;
    ensuref(totalWays > 0, "Total number of minimal paths must be positive");
    ensuref(totalWays <= (__int128)9e18,
            "Total number of paths overflows 64-bit: %lld * %lld",
            (long long)ways1, (long long)ways2);

    inf.readEof();
}
