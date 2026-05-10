#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

// Helper function to compute orientation
// Returns:
// 0 -> colinear
// 1 -> clockwise
// 2 -> counterclockwise
int orientation(const pll &p, const pll &q, const pll &r) {
    ll val = (q.second - p.second) * (r.first - q.first) -
             (q.first - p.first) * (r.second - q.second);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// Check if point q lies on segment pr
bool onSegment(const pll &p, const pll &q, const pll &r) {
    return q.first <= max(p.first, r.first) && q.first >= min(p.first, r.first) &&
           q.second <= max(p.second, r.second) && q.second >= min(p.second, r.second);
}

// Check if two segments (p1,q1) and (p2,q2) intersect
bool doIntersect(const pll &p1, const pll &q1, const pll &p2, const pll &q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

// Check if polygon is simple (no self-intersection)
bool isSimplePolygon(const vector<pll> &poly) {
    int n = poly.size();
    for (int i = 0; i < n; ++i) {
        pll a1 = poly[i];
        pll a2 = poly[(i+1)%n];
        for (int j = i+1; j < n; ++j) {
            // Edges are (a1,a2) and (b1,b2)
            pll b1 = poly[j];
            pll b2 = poly[(j+1)%n];
            // Skip adjacent edges and the same edge
            if (i == j) continue;
            if ((i+1)%n == j || i == (j+1)%n) continue;
            if (doIntersect(a1, a2, b1, b2)) return false;
        }
    }
    return true;
}

// Check if all points are distinct
bool allPointsDistinct(const vector<pll> &poly) {
    set<pll> s(poly.begin(), poly.end());
    return (int)s.size() == (int)poly.size();
}

// Check if polygon is non-degenerate (area > 0)
ll polygonArea2(const vector<pll> &poly) {
    int n = poly.size();
    ll area2 = 0;
    for (int i = 0; i < n; ++i) {
        area2 += (poly[i].first * poly[(i+1)%n].second);
        area2 -= (poly[(i+1)%n].first * poly[i].second);
    }
    return area2 > 0 ? area2 : -area2;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(3, 10000, "N");
    inf.readEoln();

    vector<pll> poly;
    for (int i = 0; i < N; ++i) {
        ll x = inf.readLong(0LL, 1000000000LL, "x_i");
        inf.readSpace();
        ll y = inf.readLong(0LL, 1000000000LL, "y_i");
        inf.readEoln();
        poly.emplace_back(x, y);
    }

    // Check all points are distinct
    ensuref(allPointsDistinct(poly), "Polygon vertices must be distinct");

    // Check polygon is simple (no self-intersection)
    ensuref(isSimplePolygon(poly), "Polygon must be simple (no self-intersection)");

    // Check polygon is non-degenerate (area > 0)
    ll area2 = polygonArea2(poly);
    ensuref(area2 > 0, "Polygon area must be positive (non-degenerate)");

    // Read 3 points (targets)
    for (int i = 0; i < 3; ++i) {
        ll x = inf.readLong(0LL, 1000000000LL, "target_x");
        inf.readSpace();
        ll y = inf.readLong(0LL, 1000000000LL, "target_y");
        inf.readEoln();
    }

    inf.readEof();
}
