#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}
    bool operator==(const Point& o) const { return x == o.x && y == o.y; }
    bool operator<(const Point& o) const { return x < o.x || (x == o.x && y < o.y); }
};

// Cross product (b - a) x (c - a)
ll cross(const Point& a, const Point& b, const Point& c) {
    ll x1 = b.x - a.x, y1 = b.y - a.y;
    ll x2 = c.x - a.x, y2 = c.y - a.y;
    return x1 * y2 - y1 * x2;
}

// Area of polygon (signed, 2x actual area)
ll polygon_area2(const vector<Point>& pts) {
    ll area = 0;
    int n = pts.size();
    for (int i = 0; i < n; ++i) {
        area += 1LL * pts[i].x * pts[(i+1)%n].y;
        area -= 1LL * pts[(i+1)%n].x * pts[i].y;
    }
    return area;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MIN_N = 3, MAX_N = 50000;
    const int MIN_C = -1000000, MAX_C = 1000000;

    int n = inf.readInt(MIN_N, MAX_N, "n");
    inf.readEoln();

    vector<Point> pts;
    set<pii> seen;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(MIN_C, MAX_C, "x_i");
        inf.readSpace();
        int y = inf.readInt(MIN_C, MAX_C, "y_i");
        inf.readEoln();

        ensuref(!seen.count({x, y}), "Duplicate point at index %d: (%d, %d)", i+1, x, y);
        pts.emplace_back(x, y);
        seen.insert({x, y});
    }

    // 1. No three towers are collinear
    for (int i = 0; i < n; ++i) {
        int j = (i+1)%n, k = (i+2)%n;
        ll cp = cross(pts[i], pts[j], pts[k]);
        ensuref(cp != 0, "Three consecutive points are collinear at indices %d, %d, %d", i+1, j+1, k+1);
    }

    // 2. No tower is strictly inside the convex hull (i.e., all points are on the convex hull)
    //    Since input is given in convex hull order, we can check that all points are on the hull by:
    //    - The polygon is strictly convex (all cross products have same sign and nonzero)
    //    - No duplicate points (already checked above)
    //    - No three consecutive points collinear (already checked above)
    //    - All points are on the boundary (by construction)
    //    So, nothing more is needed for this property.

    // 3. Points are given in order of traversal of their convex hull in clockwise direction.
    //    Check that the order is strictly convex and clockwise.
    //    For strictly convex, all cross products between consecutive triples must have the same sign (all negative for clockwise).
    int sign = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i+1)%n, k = (i+2)%n;
        ll cp = cross(pts[i], pts[j], pts[k]);
        if (cp != 0) {
            if (sign == 0) sign = (cp > 0 ? 1 : -1);
            else ensuref((cp > 0 ? 1 : -1) == sign, "Polygon is not strictly convex at indices %d, %d, %d", i+1, j+1, k+1);
        }
    }
    // For clockwise, area must be negative
    ll area2 = polygon_area2(pts);
    ensuref(area2 < 0, "Points are not given in clockwise order (signed area = %lld)", area2);

    inf.readEof();
}
