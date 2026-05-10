#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of points N
    int n = inf.readInt(3, 100000, "N");
    inf.readEoln();

    vector<pair<int,int>> pts;
    pts.reserve(n);
    set<pair<int,int>> seen;

    // Read the points, check bounds and duplicates
    for (int i = 0; i < n; i++) {
        string xi_name = "x_" + to_string(i+1);
        string yi_name = "y_" + to_string(i+1);
        int x = inf.readInt(-40000, 40000, xi_name.c_str());
        inf.readSpace();
        int y = inf.readInt(-40000, 40000, yi_name.c_str());
        inf.readEoln();

        // Check duplicate point
        bool inserted = seen.insert({x, y}).second;
        ensuref(inserted,
                "Duplicate point at index %d: (%d, %d)", 
                i+1, x, y);

        pts.emplace_back(x, y);
    }

    // Check that not all points are colinear
    // Use the first two points as base
    auto p0 = pts[0];
    auto p1 = pts[1];
    bool all_colinear = true;
    long long dx1 = (long long)p1.first  - p0.first;
    long long dy1 = (long long)p1.second - p0.second;
    for (int i = 2; i < n; i++) {
        long long dx2 = (long long)pts[i].first  - p0.first;
        long long dy2 = (long long)pts[i].second - p0.second;
        long long cross = dx1 * dy2 - dy1 * dx2;
        if (cross != 0) {
            all_colinear = false;
            break;
        }
    }
    ensuref(!all_colinear,
            "All %d points are colinear", n);

    inf.readEof();
    return 0;
}
