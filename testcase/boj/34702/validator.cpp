#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

long long cross(const Point& a, const Point& b, const Point& c) {
    // (b - a) x (c - a)
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

long long area2(const vector<Point>& P) {
    int n = (int)P.size();
    long long s = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        s += P[i].x * P[j].y - P[i].y * P[j].x;
    }
    return s;
}

// Check P is strictly convex polygon in CCW order, with no three consecutive collinear
bool isStrictlyConvexCCW(const vector<Point>& P) {
    int n = (int)P.size();
    if (n < 3) return false;
    int prevSign = 0;
    for (int i = 0; i < n; ++i) {
        const Point& a = P[i];
        const Point& b = P[(i + 1) % n];
        const Point& c = P[(i + 2) % n];
        long long cr = cross(a, b, c);
        int s = (cr > 0) - (cr < 0);
        if (s == 0) return false; // no three consecutive collinear
        if (prevSign == 0) prevSign = s;
        else if (s != prevSign) return false; // must keep same orientation
    }
    // For CCW, orientation should be positive (area > 0)
    return prevSign > 0;
}

// Point in/on convex polygon test (P strictly convex, CCW)
// Returns: 1 if strictly inside, 0 if on boundary, -1 if outside
int pointInConvexPolygon(const vector<Point>& P, const Point& q) {
    int n = (int)P.size();
    // Quick checks with first point as reference
    if (cross(P[0], P[1], q) < 0) return -1;
    if (cross(P[0], P[n - 1], q) > 0) return -1;

    int l = 1, r = n - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (cross(P[0], P[m], q) >= 0) l = m;
        else r = m;
    }
    long long cr = cross(P[l], P[(l + 1) % n], q);
    if (cr > 0) return 1;
    if (cr == 0) return 0;
    return -1;
}

// Check that the convex hull of P[0..N-1] is exactly these N points, in this order.
// This enforces that the given polygon is the convex hull of its own vertices,
// i.e., no vertex lies strictly inside the convex hull of the others (and
// no three points are collinear, already guaranteed by constraints).
bool checkPolygonIsOwnConvexHull(const vector<Point>& P) {
    int n = (int)P.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);

    sort(idx.begin(), idx.end(), [&](int a, int b) {
        if (P[a].x != P[b].x) return P[a].x < P[b].x;
        return P[a].y < P[b].y;
    });

    vector<int> hull;
    hull.reserve(n * 2);

    // lower hull
    for (int id : idx) {
        while (hull.size() >= 2) {
            int a = hull[hull.size() - 2];
            int b = hull[hull.size() - 1];
            if (cross(P[a], P[b], P[id]) <= 0) hull.pop_back();
            else break;
        }
        hull.push_back(id);
    }
    // upper hull
    size_t lowerSize = hull.size();
    for (int i = (int)idx.size() - 2; i >= 0; --i) {
        int id = idx[i];
        while (hull.size() > lowerSize) {
            int a = hull[hull.size() - 2];
            int b = hull[hull.size() - 1];
            if (cross(P[a], P[b], P[id]) <= 0) hull.pop_back();
            else break;
        }
        hull.push_back(id);
    }
    if (!hull.empty()) hull.pop_back();

    if ((int)hull.size() != n) return false;

    // hull is CCW by construction; we must check that its cyclic order
    // matches exactly P[0..N-1] up to rotation.
    // Build position map for indices in hull.
    vector<int> posInHull(n, -1);
    for (int i = 0; i < n; ++i) posInHull[hull[i]] = i;

    int start = posInHull[0];
    if (start == -1) return false;

    for (int k = 0; k < n; ++k) {
        int expectedIdx = (start + k) % n;
        if (hull[expectedIdx] != k) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 3, N_MAX = 30000;
    const int MK_MIN = 3, MK_MAX = 200000;
    const long long COORD_MIN = -1000000LL, COORD_MAX = 1000000LL;

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readSpace();
    int M = inf.readInt(MK_MIN, MK_MAX, "M");
    inf.readSpace();
    int K = inf.readInt(MK_MIN, MK_MAX, "K");
    inf.readEoln();

    vector<Point> P(N);
    set<pair<long long,long long>> allCoords;

    for (int i = 0; i < N; ++i) {
        long long x = inf.readLong(COORD_MIN, COORD_MAX, "x_p");
        inf.readSpace();
        long long y = inf.readLong(COORD_MIN, COORD_MAX, "y_p");
        inf.readEoln();
        P[i] = {x, y};
        pair<long long,long long> key = {x, y};
        ensuref(!allCoords.count(key),
                "Duplicate coordinate for P at index %d: (%lld, %lld)", i + 1, x, y);
        allCoords.insert(key);
    }

    // Given: N vertices of a convex polygon P in CCW order.
    // Also: no three of N points are collinear.
    ensuref(isStrictlyConvexCCW(P),
            "Polygon P must be strictly convex, CCW, and have no three collinear vertices.");

    // Ensure polygon is the convex hull of its vertices (no interior vertex).
    ensuref(checkPolygonIsOwnConvexHull(P),
            "Polygon P's given vertices must coincide with the convex hull of these points.");

    // Optional: enforce that polygon area is positive (already implied by CCW check),
    // but we can still assert non-degeneracy explicitly.
    long long a2 = area2(P);
    ensuref(a2 > 0, "Polygon area must be positive.");

    vector<Point> Q(M);
    for (int i = 0; i < M; ++i) {
        long long x = inf.readLong(COORD_MIN, COORD_MAX, "x_q");
        inf.readSpace();
        long long y = inf.readLong(COORD_MIN, COORD_MAX, "y_q");
        inf.readEoln();
        Q[i] = {x, y};
        pair<long long,long long> key = {x, y};
        ensuref(!allCoords.count(key),
                "All coordinates must be distinct, but Q_%d duplicates an earlier point: (%lld, %lld)",
                i + 1, x, y);
        allCoords.insert(key);
    }

    // Problem states: "P의 경계 위에 있지 않은 ... 점 Q_i" (points not on the boundary).
    // It does NOT forbid points inside, so we must only ensure "not on boundary".
    for (int i = 0; i < M; ++i) {
        int pos = pointInConvexPolygon(P, Q[i]);
        ensuref(pos != 0, "Point Q_%d must not lie on the boundary of polygon P", i + 1);
        // Inside (-1/1) is allowed, so no further restriction.
    }

    for (int qi = 0; qi < K; ++qi) {
        int i = inf.readInt(1, M, "i");
        inf.readSpace();
        int j = inf.readInt(1, M, "j");
        inf.readEoln();
        ensuref(i != j, "Query %d has i == j (%d); must be i != j", qi + 1, i);
    }

    inf.readEof();
}
