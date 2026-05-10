#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Pt { ll x, y; };

// cross product (b - a) x (c - a)
static __int128 orient(const Pt &a, const Pt &b, const Pt &c) {
    return (__int128)(b.x - a.x) * (c.y - a.y)
         - (__int128)(b.y - a.y) * (c.x - a.x);
}

// returns  1 if pt is strictly inside convex CCW polygon poly
//          0 if pt is on boundary (edge or vertex)
//         -1 if pt is outside
int inConvex(const vector<Pt> &poly, const Pt &pt) {
    int n = (int)poly.size();
    if (n < 3) return -1;
    // check wedge at poly[0]
    __int128 o1 = orient(poly[0], poly[1], pt);
    if (o1 < 0) return -1;
    if (o1 == 0) {
        // collinear with edge [0,1]
        // check if on segment
        ll minx = min(poly[0].x, poly[1].x), maxx = max(poly[0].x, poly[1].x);
        ll miny = min(poly[0].y, poly[1].y), maxy = max(poly[0].y, poly[1].y);
        if (pt.x >= minx && pt.x <= maxx && pt.y >= miny && pt.y <= maxy)
            return 0;
        else
            return -1;
    }
    __int128 o2 = orient(poly[0], poly[n-1], pt);
    if (o2 > 0) return -1;
    if (o2 == 0) {
        // collinear with edge [0,n-1]
        ll minx = min(poly[0].x, poly[n-1].x), maxx = max(poly[0].x, poly[n-1].x);
        ll miny = min(poly[0].y, poly[n-1].y), maxy = max(poly[0].y, poly[n-1].y);
        if (pt.x >= minx && pt.x <= maxx && pt.y >= miny && pt.y <= maxy)
            return 0;
        else
            return -1;
    }
    // binary search to find sector
    int l = 1, r = n-1;
    while (r - l > 1) {
        int m = (l + r) >> 1;
        if (orient(poly[0], poly[m], pt) > 0) l = m;
        else r = m;
    }
    // check triangle (0, l, r)
    __int128 o3 = orient(poly[l], poly[r], pt);
    if (o3 < 0) return -1;
    if (o3 == 0) {
        ll minx = min(poly[l].x, poly[r].x), maxx = max(poly[l].x, poly[r].x);
        ll miny = min(poly[l].y, poly[r].y), maxy = max(poly[l].y, poly[r].y);
        if (pt.x >= minx && pt.x <= maxx && pt.y >= miny && pt.y <= maxy)
            return 0;
        else
            return -1;
    }
    return 1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(3, 10000, "N");
    inf.readSpace();
    int M = inf.readInt(3, 10000, "M");
    inf.readSpace();
    int K = inf.readInt(2, 300000, "K");
    inf.readEoln();

    vector<Pt> A(N), B(M), S(K);
    set<pair<ll,ll>> seen;

    // Read polygon A
    for (int i = 0; i < N; i++) {
        ll x = inf.readLong(-1000000000LL, 1000000000LL, "A_x");
        inf.readSpace();
        ll y = inf.readLong(-1000000000LL, 1000000000LL, "A_y");
        if (i < N-1) inf.readSpace();
        else inf.readEoln();
        A[i] = {x, y};
        auto pr = make_pair(x, y);
        ensuref(!seen.count(pr),
                "Duplicate point in input: (%lld,%lld)", x, y);
        seen.insert(pr);
    }

    // Read polygon B
    for (int i = 0; i < M; i++) {
        ll x = inf.readLong(-1000000000LL, 1000000000LL, "B_x");
        inf.readSpace();
        ll y = inf.readLong(-1000000000LL, 1000000000LL, "B_y");
        if (i < M-1) inf.readSpace();
        else inf.readEoln();
        B[i] = {x, y};
        auto pr = make_pair(x, y);
        ensuref(!seen.count(pr),
                "Duplicate point in input: (%lld,%lld)", x, y);
        seen.insert(pr);
    }

    // Read signature points S
    for (int i = 0; i < K; i++) {
        ll x = inf.readLong(-1000000000LL, 1000000000LL, "S_x");
        inf.readSpace();
        ll y = inf.readLong(-1000000000LL, 1000000000LL, "S_y");
        if (i < K-1) inf.readSpace();
        else inf.readEoln();
        S[i] = {x, y};
        auto pr = make_pair(x, y);
        ensuref(!seen.count(pr),
                "Duplicate point in input: (%lld,%lld)", x, y);
        seen.insert(pr);
    }

    // Validate convexity and CCW of A
    ensuref(N >= 3, "Polygon A must have at least 3 vertices");
    for (int i = 0; i < N; i++) {
        int i1 = (i + 1) % N, i2 = (i + 2) % N;
        __int128 c = orient(A[i], A[i1], A[i2]);
        ensuref(c > 0,
                "Polygon A is not strictly convex and CCW at vertices %d,%d,%d: "
                "(%lld,%lld),(%lld,%lld),(%lld,%lld)",
                i, i1, i2,
                A[i].x, A[i].y, A[i1].x, A[i1].y, A[i2].x, A[i2].y);
    }

    // Validate convexity and CCW of B
    ensuref(M >= 3, "Polygon B must have at least 3 vertices");
    for (int i = 0; i < M; i++) {
        int i1 = (i + 1) % M, i2 = (i + 2) % M;
        __int128 c = orient(B[i], B[i1], B[i2]);
        ensuref(c > 0,
                "Polygon B is not strictly convex and CCW at vertices %d,%d,%d: "
                "(%lld,%lld),(%lld,%lld),(%lld,%lld)",
                i, i1, i2,
                B[i].x, B[i].y, B[i1].x, B[i1].y, B[i2].x, B[i2].y);
    }

    // All vertices of B must lie strictly inside A
    for (int i = 0; i < M; i++) {
        int res = inConvex(A, B[i]);
        ensuref(res == 1,
                "Polygon B vertex %d (%lld,%lld) is not strictly inside polygon A",
                i, B[i].x, B[i].y);
    }

    // Signature points must not lie on the boundary of A or B
    for (int i = 0; i < K; i++) {
        int inA = inConvex(A, S[i]);
        ensuref(inA != 0,
                "Signature point %d (%lld,%lld) is on the boundary of A",
                i, S[i].x, S[i].y);
        int inB = inConvex(B, S[i]);
        ensuref(inB != 0,
                "Signature point %d (%lld,%lld) is on the boundary of B",
                i, S[i].x, S[i].y);
    }

    inf.readEof();
    return 0;
}
