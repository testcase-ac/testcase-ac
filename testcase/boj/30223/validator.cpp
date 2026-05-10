#include "testlib.h"
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

struct Point {
    int x, y;
    Point(int x=0, int y=0): x(x), y(y) {}
    Point operator-(const Point& b) const { return Point(x-b.x, y-b.y); }
    ll cross(const Point& b) const { return 1LL*x*b.y - 1LL*y*b.x; }
    bool operator<(const Point& b) const { return x < b.x || (x == b.x && y < b.y); }
    bool operator==(const Point& b) const { return x == b.x && y == b.y; }
};

ll polygon_area2(const vector<Point>& poly) {
    // Returns 2*area (signed, positive if CCW, negative if CW)
    int n = poly.size();
    ll area2 = 0;
    for (int i = 0; i < n; ++i) {
        area2 += poly[i].cross(poly[(i+1)%n]);
    }
    return area2;
}

bool is_simple_polygon(const vector<Point>& poly) {
    // Checks for self-intersection
    int n = poly.size();
    for (int i = 0; i < n; ++i) {
        int i2 = (i+1)%n;
        for (int j = i+1; j < n; ++j) {
            int j2 = (j+1)%n;
            // Skip adjacent edges and same edge
            if (i == j || i2 == j || i == j2) continue;
            Point a1 = poly[i], a2 = poly[i2];
            Point b1 = poly[j], b2 = poly[j2];
            // Check if segments (a1,a2) and (b1,b2) intersect
            auto ccw = [](const Point& A, const Point& B, const Point& C) {
                return (C-B).cross(A-B) > 0;
            };
            bool inter = (ccw(a1,a2,b1) != ccw(a1,a2,b2)) && (ccw(b1,b2,a1) != ccw(b1,b2,a2));
            if (inter) return false;
        }
    }
    return true;
}

bool is_convex(const vector<Point>& poly) {
    // Checks if all turns are the same direction (CW or CCW)
    int n = poly.size();
    int sign = 0;
    for (int i = 0; i < n; ++i) {
        Point a = poly[i];
        Point b = poly[(i+1)%n];
        Point c = poly[(i+2)%n];
        ll z = (b-a).cross(c-b);
        if (z == 0) continue; // collinear, allowed for convex
        if (sign == 0) sign = (z > 0 ? 1 : -1);
        else if ((z > 0 ? 1 : -1) != sign) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 100, "n");
    inf.readEoln();

    vector<Point> poly;
    set<pii> seen;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(1, 1000, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, 1000, "y_i");
        inf.readEoln();
        ensuref(!seen.count({x,y}), "Duplicate vertex at index %d: (%d,%d)", i+1, x, y);
        seen.insert({x,y});
        poly.emplace_back(x, y);
    }

    // Check that the polygon is simple (no self-intersection)
    ensuref(is_simple_polygon(poly), "Polygon is not simple (self-intersecting)");

    // Check that the polygon is convex
    ensuref(is_convex(poly), "Polygon is not convex");

    // Check that the polygon is non-degenerate (area > 0)
    ll area2 = polygon_area2(poly);
    ensuref(abs(area2) > 0, "Polygon area is zero (degenerate polygon)");

    // Check that the order is clockwise
    ensuref(area2 < 0, "Polygon vertices are not in clockwise order (area2 = %lld)", area2);

    inf.readEof();
}
