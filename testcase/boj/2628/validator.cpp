#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read paper dimensions
    int W = inf.readInt(1, 100, "W");
    inf.readSpace();
    int H = inf.readInt(1, 100, "H");
    inf.readEoln();

    // Maximum possible distinct cut lines is (H-1) horizontal + (W-1) vertical
    int maxCuts = (H >= 1 ? H - 1 : 0) + (W >= 1 ? W - 1 : 0);
    // The problem statement says "number of cuts" is a natural number; allow zero cuts too.
    int m = inf.readInt(0, maxCuts, "m");
    inf.readEoln();

    // Read each cut
    for (int i = 0; i < m; i++) {
        int d = inf.readInt(0, 1, "d_i"); // 0 = horizontal, 1 = vertical
        inf.readSpace();
        if (d == 0) {
            // Horizontal cut at a horizontal grid line: must be between 1 and H-1
            ensuref(H >= 2,
                    "Cannot have a horizontal cut when H = %d (no available horizontal grid lines)", H);
            int k = inf.readInt(1, H - 1, "k_i");
        } else {
            // Vertical cut at a vertical grid line: must be between 1 and W-1
            ensuref(W >= 2,
                    "Cannot have a vertical cut when W = %d (no available vertical grid lines)", W);
            int k = inf.readInt(1, W - 1, "k_i");
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
