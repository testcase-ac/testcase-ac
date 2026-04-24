#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n, c, b
    int n = inf.readInt(2, 500000, "n");
    inf.readSpace();
    int c = inf.readInt(1, n - 1, "c");
    inf.readSpace();
    int b = inf.readInt(1, n - 1, "b");
    inf.readEoln();

    // Read broken bit positions
    vector<int> z = inf.readInts(b, 2, n, "z_i");
    inf.readEoln();

    // Check that z is strictly increasing
    for (int i = 1; i < b; i++) {
        ensuref(z[i] > z[i - 1],
                "Broken bits positions must be strictly increasing, but z[%d]=%d <= z[%d]=%d",
                i, z[i], i-1, z[i-1]);
    }
    // Last broken bit must be at position n
    ensuref(z[b-1] == n,
            "Last broken bit position z[%d]=%d must equal n=%d",
            b-1, z[b-1], n);

    // Compute maximum achievable bit changes
    long long cmax = 0;
    // Segment before first broken bit (from 1 to z[0]-1), only right boundary at broken zero
    int L0 = z[0] - 1;
    cmax += L0;
    // Interior segments between broken bits
    for (int i = 0; i + 1 < b; i++) {
        int Li = z[i+1] - z[i] - 1;
        // For a segment of length Li with zeros at both ends,
        // max changes = Li + (Li is odd ? 1 : 0)
        cmax += Li + (Li % 2);
    }

    // Validate that desired c is achievable
    ensuref(c <= cmax,
            "Desired number of bit changes c=%d exceeds maximum possible c_max=%lld",
            c, cmax);

    inf.readEof();
    return 0;
}
