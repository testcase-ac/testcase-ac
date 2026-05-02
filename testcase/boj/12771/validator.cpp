#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;

struct Segment {
    int x0, x1, y;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 1, N_MAX = 2000;
    const int X_MIN = -1000000, X_MAX = 1000000;
    const int Y_MIN = 1, Y_MAX = 1000000;

    int n = inf.readInt(N_MIN, N_MAX, "n");
    inf.readEoln();

    vector<Segment> segs;
    set<tuple<int,int,int>> seen; // For duplicate check

    for (int i = 0; i < n; ++i) {
        int x0 = inf.readInt(X_MIN, X_MAX, "x0");
        inf.readSpace();
        int x1 = inf.readInt(X_MIN, X_MAX, "x1");
        inf.readSpace();
        int y = inf.readInt(Y_MIN, Y_MAX, "y");
        inf.readEoln();

        // No two deposits will intersect, not even at a point.
        // We'll check this after reading all segments.

        // Save as-is, endpoints can be in any order
        segs.push_back({x0, x1, y});

        // Optional: check for duplicate segments (same x0, x1, y)
        ensuref(seen.insert(make_tuple(x0, x1, y)).second, 
            "Duplicate deposit at line %d: (%d, %d, %d)", i+2, x0, x1, y);
    }

    // Check for intersection between all pairs of segments
    // Segments are horizontal at different y's, but y's may be equal.
    // For two segments to intersect, they must be at the same y and their projections overlap or touch.
    // For segments at different y, they never intersect (since all are horizontal).
    // So, for each y, collect all segments at that y and check for overlap.

    // Map from y to vector of [x0,x1] intervals
    map<int, vector<pair<int,int>>> y_to_intervals;
    for (const auto& s : segs) {
        int l = min(s.x0, s.x1);
        int r = max(s.x0, s.x1);
        y_to_intervals[s.y].emplace_back(l, r);
    }
    for (const auto& [y, intervals] : y_to_intervals) {
        // Sort by left endpoint
        vector<pair<int,int>> sorted = intervals;
        sort(sorted.begin(), sorted.end());
        for (size_t i = 1; i < sorted.size(); ++i) {
            int prev_l = sorted[i-1].first, prev_r = sorted[i-1].second;
            int curr_l = sorted[i].first, curr_r = sorted[i].second;
            // If prev_r >= curr_l, they touch or overlap at a point
            ensuref(prev_r < curr_l, 
                "Deposits at y=%d intersect or touch at x=%d (intervals [%d,%d] and [%d,%d])",
                y, curr_l, prev_l, prev_r, curr_l, curr_r);
        }
    }

    inf.readEof();
}
