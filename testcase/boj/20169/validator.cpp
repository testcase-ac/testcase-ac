#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

struct Seg {
    int idx;
    bool isHoriz;
    int fixed; // y if horizontal, x if vertical
    int low, high; // range on the other axis, inclusive
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and t
    int n = inf.readInt(2, 500, "n");
    inf.readSpace();
    long long t = inf.readLong(0LL, 1000000000LL, "t");
    inf.readEoln();

    vector<Seg> segs;
    segs.reserve(n);
    set<pair<int,int>> endpoints;

    for (int i = 0; i < n; i++) {
        // Read the four coordinates
        char buf[32];
        sprintf(buf, "bx_%d", i+1);
        int bx = inf.readInt(0, 10000000, buf);
        inf.readSpace();
        sprintf(buf, "by_%d", i+1);
        int by = inf.readInt(0, 10000000, buf);
        inf.readSpace();
        sprintf(buf, "ex_%d", i+1);
        int ex = inf.readInt(0, 10000000, buf);
        inf.readSpace();
        sprintf(buf, "ey_%d", i+1);
        int ey = inf.readInt(0, 10000000, buf);
        inf.readEoln();

        // Endpoints must be distinct
        ensuref(!(bx == ex && by == ey),
                "Segment %d has zero length (both endpoints are (%d,%d))",
                i+1, bx, by);
        // No shared endpoints
        pair<int,int> p1 = {bx, by}, p2 = {ex, ey};
        ensuref(endpoints.count(p1) == 0,
                "Endpoint (%d,%d) of segment %d is shared by multiple roads",
                bx, by, i+1);
        ensuref(endpoints.count(p2) == 0,
                "Endpoint (%d,%d) of segment %d is shared by multiple roads",
                ex, ey, i+1);
        endpoints.insert(p1);
        endpoints.insert(p2);

        // Must be horizontal or vertical
        bool isH = false;
        if (by == ey) {
            isH = true;
        } else if (bx == ex) {
            isH = false;
        } else {
            ensuref(false,
                    "Segment %d is neither horizontal nor vertical: (%d,%d)-(%d,%d)",
                    i+1, bx, by, ex, ey);
        }

        // Build Seg entry
        Seg s;
        s.idx = i+1;
        s.isHoriz = isH;
        if (isH) {
            s.fixed = by;
            s.low = min(bx, ex);
            s.high = max(bx, ex);
        } else {
            s.fixed = bx;
            s.low = min(by, ey);
            s.high = max(by, ey);
        }
        segs.push_back(s);
    }

    // Check pairwise segment constraints
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            const Seg &A = segs[i], &B = segs[j];
            // Same orientation: must not overlap or touch
            if (A.isHoriz && B.isHoriz) {
                if (A.fixed == B.fixed) {
                    // check intervals [low,high] disjoint
                    bool overlap = (A.low <= B.high && B.low <= A.high);
                    ensuref(!overlap,
                            "Horizontal segments %d and %d overlap or touch at y=%d",
                            A.idx, B.idx, A.fixed);
                }
            } else if (!A.isHoriz && !B.isHoriz) {
                if (A.fixed == B.fixed) {
                    bool overlap = (A.low <= B.high && B.low <= A.high);
                    ensuref(!overlap,
                            "Vertical segments %d and %d overlap or touch at x=%d",
                            A.idx, B.idx, A.fixed);
                }
            } else {
                // One horizontal, one vertical: check intersection
                const Seg &H = A.isHoriz ? A : B;
                const Seg &V = A.isHoriz ? B : A;
                int hy = H.fixed;
                int hl = H.low, hr = H.high;
                int vx = V.fixed;
                int vl = V.low, vr = V.high;
                bool inX = (hl <= vx && vx <= hr);
                bool inY = (vl <= hy && hy <= vr);
                if (inX && inY) {
                    // Must be a proper interior intersection (four-way)
                    bool strictlyInsideH = (vx > hl && vx < hr);
                    bool strictlyInsideV = (hy > vl && hy < vr);
                    ensuref(strictlyInsideH && strictlyInsideV,
                            "Segments %d and %d intersect at endpoint (%d,%d) instead of a proper crossing",
                            A.idx, B.idx, vx, hy);
                }
            }
        }
    }

    inf.readEof();
    return 0;
}
