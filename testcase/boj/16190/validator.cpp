#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    // Read the 2n coordinates a[0..2n-1]
    int cnt = 2 * n;
    vector<long long> a = inf.readLongs(cnt, 1LL, 1000000LL, "a_i");
    inf.readEoln();

    // Check strictly increasing
    for (int i = 1; i < cnt; i++) {
        ensuref(a[i] > a[i-1],
                "a[%d] = %lld is not strictly greater than a[%d] = %lld",
                i, a[i], i-1, a[i-1]);
    }

    // Validate the mountain boundary stays in y >= 0
    // Compute y-coordinate at each cusp
    long long y = 0;  // at cusp 0
    for (int i = 1; i < cnt; i++) {
        long long dx = a[i] - a[i-1];
        if (i % 2 == 1) {
            // odd-indexed segment: slope +1
            y += dx;
        } else {
            // even-indexed segment: slope -1
            y -= dx;
        }
        ensuref(y >= 0,
                "Boundary dips below x-axis at cusp index %d: y = %lld",
                i, y);
    }
    // After the last cusp (index 2n-1), the final segment drops to y=0;
    // ensured by y >= 0 above.

    // Read x-coordinate of Joon's house
    long long x = inf.readLong(a[0], a[cnt-1], "x");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
