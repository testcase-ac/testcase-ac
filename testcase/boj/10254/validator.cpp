#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Number of cities in this test case
        int n = inf.readInt(2, 200000, "n");
        inf.readEoln();

        vector<pair<int,int>> pts;
        pts.reserve(n);

        // Read all points
        for (int i = 0; i < n; ++i) {
            int x = inf.readInt(-10000000, 10000000, "x");
            inf.readSpace();
            int y = inf.readInt(-10000000, 10000000, "y");
            inf.readEoln();
            pts.emplace_back(x, y);
        }

        // Check for duplicate points
        sort(pts.begin(), pts.end());
        for (int i = 1; i < n; ++i) {
            if (pts[i] == pts[i-1]) {
                ensuref(false,
                        "Duplicate point detected in test case %d at sorted index %d: (%d, %d)",
                        tc, i, pts[i].first, pts[i].second);
            }
        }
    }

    inf.readEof();
    return 0;
}
