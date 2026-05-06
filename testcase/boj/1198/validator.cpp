#include "testlib.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int COORD_MIN = 1;
const int COORD_MAX = 10000;
const int N_MIN = 3;
const int N_MAX = 35;

// Cross product (b-a) x (c-a)
ll cross(const pii& a, const pii& b, const pii& c) {
    ll x1 = b.first - a.first;
    ll y1 = b.second - a.second;
    ll x2 = c.first - a.first;
    ll y2 = c.second - a.second;
    return x1 * y2 - y1 * x2;
}

// Area of polygon (absolute value, divided by 2)
double polygon_area(const vector<pii>& pts) {
    ll area2 = 0;
    int n = pts.size();
    for (int i = 0; i < n; ++i) {
        area2 += 1LL * pts[i].first * pts[(i+1)%n].second;
        area2 -= 1LL * pts[(i+1)%n].first * pts[i].second;
    }
    return fabs(area2) / 2.0;
}

// Check if all points are unique
void check_unique_points(const vector<pii>& pts) {
    set<pii> s(pts.begin(), pts.end());
    ensuref((int)s.size() == (int)pts.size(), "Polygon has duplicate points");
}

// Check if all points are in bounds
void check_points_in_bounds(const vector<pii>& pts) {
    for (int i = 0; i < (int)pts.size(); ++i) {
        int x = pts[i].first, y = pts[i].second;
        ensuref(x >= COORD_MIN && x <= COORD_MAX, "x[%d]=%d out of bounds [%d,%d]", i+1, x, COORD_MIN, COORD_MAX);
        ensuref(y >= COORD_MIN && y <= COORD_MAX, "y[%d]=%d out of bounds [%d,%d]", i+1, y, COORD_MIN, COORD_MAX);
    }
}

// Check if polygon is non-degenerate (area > 0)
void check_non_degenerate(const vector<pii>& pts) {
    double area = polygon_area(pts);
    ensuref(area > 0, "Polygon is degenerate (area = 0)");
}

// Check if polygon is convex and in clockwise order
void check_convex_clockwise(const vector<pii>& pts) {
    int n = pts.size();
    // For convex polygon, all cross products should have the same sign (strictly negative for clockwise)
    ll prev = 0;
    for (int i = 0; i < n; ++i) {
        ll cr = cross(pts[i], pts[(i+1)%n], pts[(i+2)%n]);
        if (cr == 0) {
            ensuref(false, "Polygon has colinear consecutive points at indices %d, %d, %d", i+1, (i+2-1+n)%n+1, (i+3-1+n)%n+1);
        }
        if (i == 0) prev = cr;
        else {
            ensuref((prev < 0 && cr < 0) || (prev > 0 && cr > 0), "Polygon is not convex at indices %d, %d, %d", i+1, (i+2-1+n)%n+1, (i+3-1+n)%n+1);
        }
    }
    // For clockwise, area should be negative (signed area)
    ll area2 = 0;
    for (int i = 0; i < n; ++i) {
        area2 += 1LL * pts[i].first * pts[(i+1)%n].second;
        area2 -= 1LL * pts[(i+1)%n].first * pts[i].second;
    }
    ensuref(area2 < 0, "Polygon points are not in clockwise order (signed area = %lld)", area2);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(N_MIN, N_MAX, "n");
    inf.readEoln();

    vector<pii> pts;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(COORD_MIN, COORD_MAX, "x_i");
        inf.readSpace();
        int y = inf.readInt(COORD_MIN, COORD_MAX, "y_i");
        inf.readEoln();
        pts.emplace_back(x, y);
    }

    check_unique_points(pts);
    check_points_in_bounds(pts);
    check_non_degenerate(pts);
    check_convex_clockwise(pts);

    inf.readEof();
}
