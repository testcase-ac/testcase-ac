#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    long long x, y;
};

long long dist2(const Point& a, const Point& b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx * dx + dy * dy;
}

long long cross(const Point& o, const Point& a, const Point& b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

// Convex hull (Monotone chain), returns hull in CCW order without duplicate last point
vector<Point> convex_hull(vector<Point> pts) {
    int n = (int)pts.size();
    if (n <= 1) return pts;

    sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });

    vector<Point> lower, upper;
    for (int i = 0; i < n; i++) {
        while (lower.size() >= 2 &&
               cross(lower[lower.size()-2], lower[lower.size()-1], pts[i]) <= 0)
            lower.pop_back();
        lower.push_back(pts[i]);
    }
    for (int i = n-1; i >= 0; i--) {
        while (upper.size() >= 2 &&
               cross(upper[upper.size()-2], upper[upper.size()-1], pts[i]) <= 0)
            upper.pop_back();
        upper.push_back(pts[i]);
    }
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

// Rotating calipers to get diameter^2 of convex polygon
long long diameter2(const vector<Point>& hull) {
    int n = (int)hull.size();
    if (n == 1) return 0;
    if (n == 2) return dist2(hull[0], hull[1]);

    long long best = 0;
    int j = 1;
    for (int i = 0; i < n; i++) {
        int ni = (i + 1) % n;
        // move j while area increases
        while (true) {
            int nj = (j + 1) % n;
            long long cur = llabs(cross(hull[i], hull[ni], hull[j]));
            long long nxt = llabs(cross(hull[i], hull[ni], hull[nj]));
            if (nxt > cur) j = nj;
            else break;
        }
        best = max(best, dist2(hull[i], hull[j]));
    }
    return best;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    vector<Point> pts;
    pts.reserve(N);

    for (int i = 0; i < N; i++) {
        long long x = inf.readLong(-50000LL, 50000LL, "x_i");
        inf.readSpace();
        long long y = inf.readLong(-50000LL, 50000LL, "y_i");
        inf.readEoln();
        pts.push_back({x, y});
    }

    // Global property check: maximum squared distance fits in signed 64-bit.
    // Given constraints already guarantee this (<= 1e10),
    // but we verify by computing using 128-bit intermediate in case of changes.
    vector<Point> hull = convex_hull(pts);
    long long ans = diameter2(hull);

    __int128 mx = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N && j < i + 4; j++) { 
            // small local check to avoid O(N^2); hull-based ans is authoritative
            __int128 dx = pts[i].x - pts[j].x;
            __int128 dy = pts[i].y - pts[j].y;
            __int128 d2 = dx * dx + dy * dy;
            if (d2 > mx) mx = d2;
        }
    }
    // basic sanity: answer should be at least local max found above
    ensuref((__int128)ans >= mx,
            "Computed diameter is smaller than a locally found distance; possible overflow or bug in constraints");

    // Also ensure within 64-bit signed range
    ensuref((__int128)ans >= 0 && (__int128)ans <= (__int128)9e18,
            "Maximum squared distance out of 64-bit range");

    inf.readEof();
}
