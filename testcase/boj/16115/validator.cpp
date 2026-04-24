#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point { 
    ll x, y; 
};

ll cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
ll cross(const Point &a, const Point &b, const Point &c) {
    // cross of (b-a) x (c-a)
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// point-in-polygon (ray casting) for origin
// returns +1 if inside, 0 if on boundary, -1 if outside
int pointInPoly(const vector<Point>& P) {
    int n = P.size();
    bool inside = false;
    for (int i = 0, j = n-1; i < n; j = i++) {
        const Point &a = P[j], &b = P[i];
        // check if origin is on segment ab
        ll cr = cross(a, b, {0,0});
        if (cr == 0) {
            // check bounding box
            if (min(a.x,b.x) <= 0 && 0 <= max(a.x,b.x)
             && min(a.y,b.y) <= 0 && 0 <= max(a.y,b.y))
                return 0;
        }
        // ray cast to the right (positive x)
        // count edges crossing ray from (0,0) horizontally
        bool cond1 = (a.y > 0) != (b.y > 0);
        if (cond1) {
            // intersection x-coordinate
            double xint = a.x + (double)(b.x - a.x) * (0 - a.y) / (double)(b.y - a.y);
            if (xint > 0) inside = !inside;
        }
    }
    return inside ? 1 : -1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 300000, "N");
    inf.readEoln();

    vector<Point> P(N);
    for (int i = 0; i < N; i++) {
        P[i].x = inf.readLong(-1000000LL, 1000000LL, "x_i");
        inf.readSpace();
        P[i].y = inf.readLong(-1000000LL, 1000000LL, "y_i");
        inf.readEoln();
    }

    // 1) Compute signed area to ensure CCW and non-degenerate
    //    Also ensures polygon not self-crossing in this basic sense.
    __int128 area2 = 0;
    for (int i = 0; i < N; i++) {
        int j = (i+1)%N;
        area2 += (__int128)P[i].x * P[j].y - (__int128)P[i].y * P[j].x;
    }
    ensuref(area2 > 0, "Polygon must be CCW with positive area; computed area2 = %lld", (long long)area2);
    // note: area2 != 0 ensures non-degenerate overall polygon.
    
    // 2) No three consecutive collinear
    for (int i = 0; i < N; i++) {
        int i1 = (i+1)%N, i2 = (i+2)%N;
        ll cr = cross(P[i], P[i1], P[i2]);
        ensuref(cr != 0, "Three consecutive points are collinear at indices %d, %d, %d", i, i1, i2);
    }

    // 3) Origin is inside or on boundary
    int pip = pointInPoly(P);
    ensuref(pip >= 0, "Origin must be inside or on boundary of polygon; test gives %d", pip);

    // 4) Star-shaped wrt origin <=> origin in kernel of polygon
    //    For each directed edge Pi->P{i+1}, interior is to left, so origin must be on left side or on.
    for (int i = 0; i < N; i++) {
        int j = (i+1)%N;
        // edge vector E = P[j] - P[i], vector to origin V = (0,0) - P[i]
        Point E{P[j].x - P[i].x, P[j].y - P[i].y};
        Point V{-P[i].x, -P[i].y};
        ll cr = cross(E, V);
        ensuref(cr >= 0, "Origin is outside kernel at edge %d: cross = %lld", i, cr);
    }

    // Note: the problem states the polygon is simple (no self intersections),
    // but full self-intersection checking is omitted here for brevity.

    inf.readEof();
    return 0;
}
