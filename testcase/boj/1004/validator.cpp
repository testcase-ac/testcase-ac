#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases (not specified, assume up to 100000)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; tc++) {
        // Read start and end coordinates
        int x1 = inf.readInt(-1000, 1000, "x1");
        inf.readSpace();
        int y1 = inf.readInt(-1000, 1000, "y1");
        inf.readSpace();
        int x2 = inf.readInt(-1000, 1000, "x2");
        inf.readSpace();
        int y2 = inf.readInt(-1000, 1000, "y2");
        inf.readEoln();

        // Number of planetary systems
        int n = inf.readInt(1, 50, "n");
        inf.readEoln();

        vector<int> cx(n), cy(n), r(n);
        for (int i = 0; i < n; i++) {
            cx[i] = inf.readInt(-1000, 1000, "c_x");
            inf.readSpace();
            cy[i] = inf.readInt(-1000, 1000, "c_y");
            inf.readSpace();
            r[i]  = inf.readInt(1, 1000, "r");
            inf.readEoln();
        }

        // Check that no two circles have touching or intersecting boundaries:
        // For circles i and j, let d = distance between centers,
        // let R = r[i] + r[j], let D = |r[i] - r[j]|.
        // Boundaries do not touch/intersect iff d < D or d > R.
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                long long dx = (long long)cx[i] - cx[j];
                long long dy = (long long)cy[i] - cy[j];
                long long dist2 = dx * dx + dy * dy;
                long long sumR  = (long long)r[i] + r[j];
                long long diffR = llabs((long long)r[i] - r[j]);
                bool ok = (dist2 < diffR * diffR) || (dist2 > sumR * sumR);
                ensuref(ok,
                    "Circles %d and %d have touching or intersecting boundaries: "
                    "centers=(%d,%d),(%d,%d), radii=(%d,%d)",
                    i, j, cx[i], cy[i], cx[j], cy[j], r[i], r[j]
                );
            }
        }

        // Check that start and end points are not exactly on any circle boundary
        for (int i = 0; i < n; i++) {
            {
                long long dx = (long long)x1 - cx[i];
                long long dy = (long long)y1 - cy[i];
                long long dist2 = dx * dx + dy * dy;
                long long rad2 = (long long)r[i] * r[i];
                ensuref(dist2 != rad2,
                    "Start point lies on boundary of circle %d: center=(%d,%d), radius=%d",
                    i, cx[i], cy[i], r[i]
                );
            }
            {
                long long dx = (long long)x2 - cx[i];
                long long dy = (long long)y2 - cy[i];
                long long dist2 = dx * dx + dy * dy;
                long long rad2 = (long long)r[i] * r[i];
                ensuref(dist2 != rad2,
                    "End point lies on boundary of circle %d: center=(%d,%d), radius=%d",
                    i, cx[i], cy[i], r[i]
                );
            }
        }
    }

    inf.readEof();
    return 0;
}
