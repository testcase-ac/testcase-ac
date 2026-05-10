#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long COORD_MIN = 0;
    const long long COORD_MAX = 500000;

    int N = inf.readInt(4, 300000, "N");
    ensuref(N % 2 == 0, "N must be even");
    inf.readEoln();

    vector<Pt> v(N);
    for (int i = 0; i < N; ++i) {
        long long x = inf.readLong(COORD_MIN, COORD_MAX, "x_i");
        inf.readSpace();
        long long y = inf.readLong(COORD_MIN, COORD_MAX, "y_i");
        inf.readEoln();
        v[i] = {x, y};
    }

    // Check first and last vertices
    ensuref(v[0].x == 0 && v[0].y == 0, "First vertex must be (0,0)");
    ensuref(v[N-1].y == 0, "Last vertex y-coordinate must be 0");
    ensuref(v[N-1].x >= 0, "Last vertex x-coordinate must be >= 0");

    // Check edges alternate vertical/horizontal starting with vertical and ending with vertical.
    // There are N-1 edges (polygonal chain, not closed).
    int verticalCnt = 0, horizontalCnt = 0;
    for (int i = 0; i < N-1; ++i) {
        Pt a = v[i], b = v[i+1];
        ensuref(!(a.x == b.x && a.y == b.y),
                "Consecutive vertices %d and %d must be distinct", i, i+1);
        bool vertical = (a.x == b.x);
        bool horizontal = (a.y == b.y);
        ensuref(vertical || horizontal,
                "Edge %d between (%lld,%lld) and (%lld,%lld) must be axis-aligned",
                i, a.x, a.y, b.x, b.y);
        ensuref(!(vertical && horizontal),
                "Edge %d has zero length", i);

        if (vertical) ++verticalCnt;
        else ++horizontalCnt;

        if (i == 0 || i == N-2) {
            ensuref(vertical, "First and last edges must be vertical (edge %d)", i);
        } else {
            // edges must alternate
            Pt p = v[i-1], c = v[i+1];
            bool prevVertical = (p.x == a.x);
            // current 'vertical' already computed
            ensuref(prevVertical != vertical,
                    "Edges must alternate vertical and horizontal at vertex index %d", i);
        }
    }
    ensuref(verticalCnt == horizontalCnt + 1,
            "Number of vertical segments must be exactly one more than horizontal segments");

    // Polygon non-degeneracy: area > 0 and simple (no self-intersection).
    // Compute signed area using shoelace on the polyline closed by (A,0) to (0,0).
    // Actually the chain already starts at (0,0) and ends at (A,0); to form polygon
    // add edge from last to first.
    long double area2 = 0.0L;
    for (int i = 0; i < N; ++i) {
        Pt a = v[i];
        Pt b = v[(i+1)%N];
        area2 += (long double)a.x * b.y - (long double)b.x * a.y;
    }
    long double area = fabsl(area2) / 2.0L;
    ensuref(area > 0.0L, "Polygon area must be positive");

    // Check simple orthogonal polygon: no edge self-intersection except adjacent.
    // Since N up to 3e5, O(N^2) is impossible.
    // For an x-monotone "all bottom visible" shape this is implied, but we at least
    // check that x is non-decreasing along the chain (since we view from above and see all bottom).
    // From description, when viewed from above, all horizontal segments are visible,
    // which for axis-aligned boundary with start (0,0) and end (A,0) implies x is non-decreasing.
    for (int i = 1; i < N; ++i) {
        ensuref(v[i].x >= v[i-1].x,
                "x-coordinates along boundary must be non-decreasing (violated between %d and %d)",
                i-1, i);
    }

    // Check all y >= 0 already ensured by bounds, and shape is above bottom y=0.
    // There must be at least one horizontal segment strictly above y=0 (since N>=4 and vertical>horizontal).
    bool hasAbove = false;
    for (int i = 0; i < N-1; ++i) {
        if (v[i].y == v[i+1].y && v[i].y > 0)
            hasAbove = true;
    }
    ensuref(hasAbove, "There must be at least one horizontal segment strictly above y=0");

    // Read holes
    int K = inf.readInt(1, N/2, "K");
    inf.readEoln();

    // Collect horizontal segments for fast lookup: map by (y) then list of [x1,x2].
    // But we just need to verify holes match some horizontal segment.
    // Build a map: key (y) -> multimap of (x1,x2) with count.
    // However, N up to 3e5, number of horizontals up to ~1.5e5, K up to N/2 - manageable.
    map<long long, multiset<pair<long long,long long>>> horiz;
    for (int i = 0; i < N-1; ++i) {
        Pt a = v[i], b = v[i+1];
        if (a.y == b.y) {
            long long y = a.y;
            long long x1 = min(a.x, b.x);
            long long x2 = max(a.x, b.x);
            horiz[y].insert({x1, x2});
        }
    }

    // Track used horizontal segments so that no segment has more than one hole.
    set<tuple<long long,long long,long long>> usedSeg; // (y,x1,x2)

    for (int i = 0; i < K; ++i) {
        long long a, b, c, d;
        a = inf.readLong(COORD_MIN, COORD_MAX, "a");
        inf.readSpace();
        b = inf.readLong(COORD_MIN, COORD_MAX, "b");
        inf.readSpace();
        c = inf.readLong(COORD_MIN, COORD_MAX, "c");
        inf.readSpace();
        d = inf.readLong(COORD_MIN, COORD_MAX, "d");
        inf.readEoln();

        ensuref(a < c, "For hole %d, must have a < c", i+1);
        ensuref(b == d, "For hole %d, y-coordinates must be equal (b == d)", i+1);

        long long y = b;
        long long x1 = a, x2 = c;

        auto itMap = horiz.find(y);
        ensuref(itMap != horiz.end(),
                "Hole %d at y=%lld does not correspond to any horizontal segment", i+1, y);

        auto &ms = itMap->second;
        auto itSeg = ms.find({x1, x2});
        ensuref(itSeg != ms.end(),
                "Hole %d segment (%lld,%lld)-( %lld,%lld ) not found among polygon horizontals",
                i+1, x1, y, x2, y);

        // ensure at most one hole per horizontal segment
        auto key = make_tuple(y, x1, x2);
        ensuref(usedSeg.find(key) == usedSeg.end(),
                "Multiple holes on same horizontal segment (%lld,%lld)-(%lld,%lld)",
                x1, y, x2, y);
        usedSeg.insert(key);

        // Note: We do NOT remove from multiset since specification allows at most one hole;
        // but even if there were duplicates (shouldn't happen in valid polygon), we keep them.
    }

    inf.readEof();
}
