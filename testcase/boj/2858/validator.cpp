#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read input: R and B on one line
    int R = inf.readInt(8, 5000, "R");
    inf.readSpace();
    int B = inf.readInt(1, 2000000, "B");
    inf.readEoln();

    // We expect exactly one valid pair (L, W) with L >= W >= 3 such that:
    //   R == 2*L + 2*W - 4
    //   B == (L - 2) * (W - 2)
    int solutions = 0;
    int foundL = -1, foundW = -1;

    // Let (L-2)*(W-2) = B.  Set x = L-2, y = W-2, so x*y = B.
    // We iterate divisors y <= x to enforce L >= W.
    for (int y = 1; (long long)y * y <= B; ++y) {
        if (B % y != 0) continue;
        int x = B / y;
        // Enforce x >= y to avoid counting reflections separately
        if (x < y) continue;
        int L = x + 2;
        int W = y + 2;
        // Both dimensions must be at least 3
        if (L < 3 || W < 3) continue;
        // Check the red tile count matches perimeter formula
        int Rcalc = 2 * L + 2 * W - 4;
        if (Rcalc == R) {
            solutions++;
            foundL = L;
            foundW = W;
        }
    }

    ensuref(solutions > 0,
            "No valid room dimensions for R=%d, B=%d", R, B);
    ensuref(solutions == 1,
            "Ambiguous room dimensions for R=%d, B=%d: found %d solutions",
            R, B, solutions);

    // Finish validation
    inf.readEof();
    return 0;
}
