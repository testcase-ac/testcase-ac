#include "testlib.h"
#include <algorithm>
#include <cstdlib>
#include <set>
#include <vector>
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
    int n = poly.size();
    ll area2 = 0;
    for (int i = 0; i < n; ++i) {
        area2 += poly[i].cross(poly[(i+1)%n]);
    }
    return area2;
}

int sign(ll value) {
    if (value < 0) return -1;
    if (value > 0) return 1;
    return 0;
}

bool between(int a, int b, int c) {
    return min(a, b) <= c && c <= max(a, b);
}

bool on_segment(const Point& a, const Point& b, const Point& p) {
    return (b - a).cross(p - a) == 0 &&
           between(a.x, b.x, p.x) &&
           between(a.y, b.y, p.y);
}

bool segments_intersect(const Point& a, const Point& b,
                        const Point& c, const Point& d) {
    ll ab_c = (b - a).cross(c - a);
    ll ab_d = (b - a).cross(d - a);
    ll cd_a = (d - c).cross(a - c);
    ll cd_b = (d - c).cross(b - c);

    if (sign(ab_c) * sign(ab_d) < 0 && sign(cd_a) * sign(cd_b) < 0) {
        return true;
    }
    return on_segment(a, b, c) ||
           on_segment(a, b, d) ||
           on_segment(c, d, a) ||
           on_segment(c, d, b);
}

bool is_simple_polygon(const vector<Point>& poly) {
    int n = poly.size();
    for (int i = 0; i < n; ++i) {
        int i2 = (i+1)%n;
        for (int j = i+1; j < n; ++j) {
            int j2 = (j+1)%n;
            if (i == j || i2 == j || i == j2) continue;
            if (segments_intersect(poly[i], poly[i2], poly[j], poly[j2])) {
                return false;
            }
        }
    }
    return true;
}

bool is_convex(const vector<Point>& poly) {
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
