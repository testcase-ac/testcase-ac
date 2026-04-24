#include "testlib.h"
#include <vector>
#include <set>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of points
    int n = inf.readInt(3, 500, "n");
    inf.readEoln();

    // Read points
    vector<pair<int,int>> pts;
    pts.reserve(n);
    set<pair<int,int>> seen;
    for (int i = 0; i < n; i++) {
        // Read x, y with exactly one space between, then newline
        int x = inf.readInt(-1000000, 1000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-1000000, 1000000, "y_i");
        inf.readEoln();

        // Check duplicate
        pair<int,int> p = {x, y};
        ensuref(!seen.count(p),
                "Duplicate point detected at index %d: (%d, %d)", i, x, y);
        seen.insert(p);
        pts.emplace_back(p);
    }

    // Check no three points are collinear
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            for (int k = j+1; k < n; k++) {
                // Compute area*2 = cross((pj - pi), (pk - pi))
                int64_t x1 = pts[j].first - pts[i].first;
                int64_t y1 = pts[j].second - pts[i].second;
                int64_t x2 = pts[k].first - pts[i].first;
                int64_t y2 = pts[k].second - pts[i].second;
                int64_t cross = x1 * y2 - x2 * y1;
                ensuref(cross != 0,
                        "Collinear points detected at indices %d, %d, %d: "
                        "(%d,%d), (%d,%d), (%d,%d)",
                        i, j, k,
                        pts[i].first, pts[i].second,
                        pts[j].first, pts[j].second,
                        pts[k].first, pts[k].second);
            }
        }
    }

    inf.readEof();
    return 0;
}
