#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Number of islands
        int n = inf.readInt(1, 75000, "n");
        inf.readEoln();

        vector<pair<long long, long long>> pts;
        pts.reserve(n);

        // Read island coordinates
        for (int i = 0; i < n; i++) {
            long long x = inf.readLong(-1000000000LL, 1000000000LL, "x_i");
            inf.readSpace();
            long long y = inf.readLong(-1000000000LL, 1000000000LL, "y_i");
            inf.readEoln();
            pts.emplace_back(x, y);
        }

        // Ensure all points are distinct
        sort(pts.begin(), pts.end());
        for (int i = 1; i < n; i++) {
            ensuref(pts[i] != pts[i-1],
                    "Duplicate island coordinates detected at indices %d and %d: (%lld, %lld)",
                    i-1, i, pts[i].first, pts[i].second);
        }
    }

    inf.readEof();
    return 0;
}
