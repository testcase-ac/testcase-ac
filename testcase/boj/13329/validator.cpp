#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct P {
    long long x, y;
};

struct BBox {
    long long minX, maxX, minY, maxY;
};

struct Polygon {
    vector<P> p;
    BBox box;
};

__int128 cross(const P &a, const P &b, const P &c) {
    return (__int128)(b.x - a.x) * (c.y - a.y) -
           (__int128)(b.y - a.y) * (c.x - a.x);
}

__int128 crossO(const P &a, const P &b) {
    return (__int128)a.x * b.y - (__int128)a.y * b.x;
}

int sgn(__int128 v) {
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

pair<long long, long long> normalizedRay(const P &p) {
    long long g = gcd(llabs(p.x), p.y);
    return {p.x / g, p.y / g};
}

BBox boundsOf(const vector<P> &poly) {
    BBox box{poly[0].x, poly[0].x, poly[0].y, poly[0].y};
    for (const P &p : poly) {
        box.minX = min(box.minX, p.x);
        box.maxX = max(box.maxX, p.x);
        box.minY = min(box.minY, p.y);
        box.maxY = max(box.maxY, p.y);
    }
    return box;
}

bool boxesOverlap(const BBox &a, const BBox &b) {
    return max(a.minX, b.minX) <= min(a.maxX, b.maxX) &&
           max(a.minY, b.minY) <= min(a.maxY, b.maxY);
}

bool onSegment(const P &a, const P &b, const P &p) {
    return cross(a, b, p) == 0 &&
           min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

bool segmentsIntersect(const P &a, const P &b, const P &c, const P &d) {
    int abC = sgn(cross(a, b, c));
    int abD = sgn(cross(a, b, d));
    int cdA = sgn(cross(c, d, a));
    int cdB = sgn(cross(c, d, b));

    if (abC == 0 && onSegment(a, b, c)) return true;
    if (abD == 0 && onSegment(a, b, d)) return true;
    if (cdA == 0 && onSegment(c, d, a)) return true;
    if (cdB == 0 && onSegment(c, d, b)) return true;
    return abC * abD < 0 && cdA * cdB < 0;
}

bool pointInConvexPolygon(const vector<P> &poly, const P &q) {
    for (int i = 0; i < (int)poly.size(); ++i) {
        int j = (i + 1) % (int)poly.size();
        if (cross(poly[i], poly[j], q) < 0) return false;
    }
    return true;
}

bool polygonsIntersect(const vector<P> &a, const vector<P> &b) {
    for (int i = 0; i < (int)a.size(); ++i) {
        int ni = (i + 1) % (int)a.size();
        for (int j = 0; j < (int)b.size(); ++j) {
            int nj = (j + 1) % (int)b.size();
            if (segmentsIntersect(a[i], a[ni], b[j], b[nj])) return true;
        }
    }
    return pointInConvexPolygon(a, b[0]) || pointInConvexPolygon(b, a[0]);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    const long long COORD_MIN_X = -100000000LL;
    const long long COORD_MAX_X =  100000000LL;
    const long long COORD_MIN_Y = 1LL;
    const long long COORD_MAX_Y = 100000000LL;

    long long totalVertices = 0;
    set<pair<long long, long long>> vertexRays;
    vector<Polygon> polygons;

    for (int i = 0; i < n; ++i) {
        setTestCase(i + 1);

        int m = inf.readInt(3, 100000, "m");
        totalVertices += m;
        ensuref(totalVertices <= 1000000LL,
                "Total number of vertices exceeds 1e6 after polygon %d", i + 1);

        vector<P> poly(m);
        for (int j = 0; j < m; ++j) {
            inf.readSpace();
            long long x = inf.readLong(COORD_MIN_X, COORD_MAX_X, "x_ij");
            inf.readSpace();
            long long y = inf.readLong(COORD_MIN_Y, COORD_MAX_Y, "y_ij");
            poly[j] = {x, y};
        }
        inf.readEoln();

        __int128 area2 = 0;
        for (int j = 0; j < m; ++j) {
            int k = (j + 1) % m;
            area2 += cross({0,0}, poly[j], poly[k]);
        }
        ensuref(area2 > 0,
                "Polygon %d is degenerate or not in counter-clockwise order", i + 1);

        set<pair<long long, long long>> pointsInPolygon;
        for (int j = 0; j < m; ++j) {
            ensuref(pointsInPolygon.insert({poly[j].x, poly[j].y}).second,
                    "Polygon %d repeats vertex %d", i + 1, j + 1);

            auto ray = normalizedRay(poly[j]);
            ensuref(vertexRays.insert(ray).second,
                    "Vertex %d of polygon %d is collinear with the origin and another vertex",
                    j + 1, i + 1);
        }

        for (int j = 0; j < m; ++j) {
            int k = (j + 1) % m;
            int l = (j + 2) % m;
            ensuref(cross(poly[j], poly[k], poly[l]) >= 0,
                    "Polygon %d is not convex at vertex %d", i + 1, k + 1);
        }

        for (int j = 0; j < m; ++j) {
            int k = (j + 1) % m;
            ensuref(crossO(poly[j], poly[k]) != 0,
                    "Edge after vertex %d of polygon %d has a supporting line through the origin",
                    j + 1, i + 1);
        }

        BBox box = boundsOf(poly);
        for (int j = 0; j < (int)polygons.size(); ++j) {
            if (!boxesOverlap(box, polygons[j].box)) continue;
            ensuref(!polygonsIntersect(poly, polygons[j].p),
                    "Polygon %d intersects polygon %d", i + 1, j + 1);
        }
        polygons.push_back({poly, box});
    }

    inf.readEof();
}
