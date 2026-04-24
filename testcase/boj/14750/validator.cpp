#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static bool onSegment(const pair<ll,ll>& p, const pair<ll,ll>& q, const pair<ll,ll>& r) {
    // check if q lies on segment pr (assuming collinear)
    return q.first >= min(p.first, r.first) && q.first <= max(p.first, r.first)
        && q.second >= min(p.second, r.second) && q.second <= max(p.second, r.second);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: n, k, h, m
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 5, "k");
    inf.readSpace();
    int h = inf.readInt(1, 50, "h");
    inf.readSpace();
    // m ≤ k*h
    int m = inf.readInt(1, (ll)k * h, "m");
    inf.readEoln();

    // Polygon vertices
    ensuref(n >= 3, "Number of polygon vertices n must be at least 3, got %d", n);
    vector<pair<ll,ll>> poly(n);
    for (int i = 0; i < n; i++) {
        ll x = inf.readLong(-1000000000LL, 1000000000LL, "poly_x");
        inf.readSpace();
        ll y = inf.readLong(-1000000000LL, 1000000000LL, "poly_y");
        inf.readEoln();
        poly[i] = {x, y};
    }

    // Check edges are orthogonal and non-zero
    vector<int> orient(n); // 0=horizontal,1=vertical
    for (int i = 0; i < n; i++) {
        auto p = poly[i];
        auto q = poly[(i+1) % n];
        // orthogonal
        ensuref(p.first == q.first || p.second == q.second,
                "Edge %d is not axis-aligned: (%lld,%lld)->(%lld,%lld)",
                i, p.first, p.second, q.first, q.second);
        // non-zero length
        ensuref(!(p.first == q.first && p.second == q.second),
                "Edge %d has zero length at (%lld,%lld)",
                i, p.first, p.second);
        // orientation
        orient[i] = (p.first == q.first ? 1 : 0);
    }
    // No three consecutive collinear => consecutive edges must alternate orientation
    for (int i = 0; i < n; i++) {
        int prev = (i - 1 + n) % n;
        ensuref(orient[prev] != orient[i],
                "Edges %d->%d and %d->%d are both %s (collinear)",
                prev, i, i, (i+1)%n,
                orient[prev] ? "vertical" : "horizontal");
    }

    // Check polygon is simple: no intersections among non-adjacent edges
    auto segIntersect = [&](int i, int j) {
        // edges i: p1->p2, j: p3->p4
        auto p1 = poly[i];
        auto p2 = poly[(i+1)%n];
        auto p3 = poly[j];
        auto p4 = poly[(j+1)%n];
        // bounding box quick reject
        ll minx1 = min(p1.first, p2.first), maxx1 = max(p1.first, p2.first);
        ll miny1 = min(p1.second, p2.second), maxy1 = max(p1.second, p2.second);
        ll minx2 = min(p3.first, p4.first), maxx2 = max(p3.first, p4.first);
        ll miny2 = min(p3.second, p4.second), maxy2 = max(p3.second, p4.second);
        if (maxx1 < minx2 || maxx2 < minx1 || maxy1 < miny2 || maxy2 < miny1)
            return false;
        // both horizontal
        if (p1.second == p2.second && p3.second == p4.second) {
            if (p1.second != p3.second) return false;
            // check x-range overlap
            return !(maxx1 < minx2 || maxx2 < minx1);
        }
        // both vertical
        if (p1.first == p2.first && p3.first == p4.first) {
            if (p1.first != p3.first) return false;
            // check y-range overlap
            return !(maxy1 < miny2 || maxy2 < miny1);
        }
        // one horiz, one vert
        pair<ll,ll> h1, h2, v1, v2;
        if (p1.second == p2.second) {
            h1 = p1; h2 = p2;
            v1 = p3; v2 = p4;
        } else {
            h1 = p3; h2 = p4;
            v1 = p1; v2 = p2;
        }
        // check if vertical.x in horizontal x-range and horizontal.y in vertical y-range
        ll hy = h1.second;
        ll hminx = min(h1.first, h2.first), hmaxx = max(h1.first, h2.first);
        ll vx = v1.first;
        ll vminy = min(v1.second, v2.second), vmaxy = max(v1.second, v2.second);
        return (vx >= hminx && vx <= hmaxx && hy >= vminy && hy <= vmaxy);
    };
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            // skip adjacent edges
            if ((j == i+1) || (i==0 && j==n-1)) continue;
            if (segIntersect(i, j)) {
                ensuref(false, "Edges %d->%d and %d->%d intersect or touch",
                        i, (i+1)%n, j, (j+1)%n);
            }
        }
    }

    // Check CCW (positive signed area)
    long double area2 = 0;
    for (int i = 0; i < n; i++) {
        int j = (i+1)%n;
        area2 += (long double)poly[i].first * poly[j].second
               - (long double)poly[j].first * poly[i].second;
    }
    ensuref(area2 > 0, "Polygon must be in CCW order (signed area = %Lf)", area2);

    // Read holes
    vector<pair<ll,ll>> holes(h);
    set<pair<ll,ll>> holeSet;
    for (int i = 0; i < h; i++) {
        ll x = inf.readLong(-1000000000LL, 1000000000LL, "hole_x");
        inf.readSpace();
        ll y = inf.readLong(-1000000000LL, 1000000000LL, "hole_y");
        inf.readEoln();
        holes[i] = {x,y};
        ensuref(!holeSet.count(holes[i]), "Duplicate hole at (%lld,%lld)", x, y);
        holeSet.insert(holes[i]);
        // must lie on boundary
        bool onB = false;
        for (int e = 0; e < n; e++) {
            auto p = poly[e];
            auto q = poly[(e+1)%n];
            // horizontal edge
            if (p.second == q.second && y == p.second &&
                x >= min(p.first, q.first) && x <= max(p.first, q.first)) {
                onB = true; break;
            }
            // vertical edge
            if (p.first == q.first && x == p.first &&
                y >= min(p.second, q.second) && y <= max(p.second, q.second)) {
                onB = true; break;
            }
        }
        ensuref(onB, "Hole at (%lld,%lld) is not on polygon boundary", x, y);
    }

    // Read mice
    vector<pair<ll,ll>> mice(m);
    set<pair<ll,ll>> mouseSet;
    for (int i = 0; i < m; i++) {
        ll x = inf.readLong(-1000000000LL, 1000000000LL, "mouse_x");
        inf.readSpace();
        ll y = inf.readLong(-1000000000LL, 1000000000LL, "mouse_y");
        inf.readEoln();
        mice[i] = {x,y};
        ensuref(!mouseSet.count(mice[i]), "Duplicate mouse at (%lld,%lld)", x, y);
        mouseSet.insert(mice[i]);
        // not on boundary
        for (int e = 0; e < n; e++) {
            auto p = poly[e];
            auto q = poly[(e+1)%n];
            if ((p.second == q.second && y == p.second &&
                 x >= min(p.first, q.first) && x <= max(p.first, q.first))
             || (p.first == q.first && x == p.first &&
                 y >= min(p.second, q.second) && y <= max(p.second, q.second))) {
                ensuref(false, "Mouse at (%lld,%lld) lies on boundary", x, y);
            }
        }
        // point-in-polygon (ray to +x)
        int cnt = 0;
        for (int e = 0; e < n; e++) {
            auto a = poly[e];
            auto b = poly[(e+1)%n];
            if (a.second == b.second) continue; // skip horizontal
            // ensure a.y < b.y
            if (a.second > b.second) swap(a, b);
            // check if ray intersects segment (a,b)
            if (y <= a.second || y > b.second) continue;
            // x-coordinate of vertical segment is a.x
            if (a.first > x) cnt++;
        }
        ensuref(cnt % 2 == 1, "Mouse at (%lld,%lld) is not strictly inside polygon", x, y);
    }

    inf.readEof();
    return 0;
}
