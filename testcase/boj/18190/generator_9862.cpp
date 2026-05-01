#include "testlib.h"
using namespace std;

struct P {
    long long x, y;
};

long long cross(const P& a, const P& b, const P& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

long long area2(const vector<P>& poly) {
    long long s = 0;
    int n = (int)poly.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        s += poly[i].x * poly[j].y - poly[i].y * poly[j].x;
    }
    return s;
}

vector<P> convexHull(vector<P> pts) {
    if (pts.size() <= 1) return pts;
    sort(pts.begin(), pts.end(), [](const P& a, const P& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    pts.erase(unique(pts.begin(), pts.end(), [](const P& a, const P& b) {
        return a.x == b.x && a.y == b.y;
    }), pts.end());
    if (pts.size() <= 1) return pts;

    vector<P> lower, upper;
    for (const P& p : pts) {
        while (lower.size() >= 2 &&
               cross(lower[lower.size()-2], lower[lower.size()-1], p) <= 0)
            lower.pop_back();
        lower.push_back(p);
    }
    for (int i = (int)pts.size() - 1; i >= 0; --i) {
        P p = pts[i];
        while (upper.size() >= 2 &&
               cross(upper[upper.size()-2], upper[upper.size()-1], p) <= 0)
            upper.pop_back();
        upper.push_back(p);
    }
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

// Returns -1 outside, 0 on boundary, 1 inside for convex CCW polygon
int pointInConvex(const vector<P>& poly, const P& p) {
    int n = (int)poly.size();
    bool onBoundary = false;
    for (int i = 0; i < n; ++i) {
        const P& a = poly[i];
        const P& b = poly[(i + 1) % n];
        long long cr = cross(a, b, p);
        if (cr < 0) return -1;
        if (cr == 0) onBoundary = true;
    }
    return onBoundary ? 0 : 1;
}

bool strictlyInside(const vector<P>& poly, const P& p) {
    return pointInConvex(poly, p) == 1;
}

vector<P> generateBasePolygon() {
    const long double PI = acosl(-1.0L);

    while (true) {
        int K = rnd.next(6, 14); // generate K random points
        vector<P> pts;
        pts.reserve(K);
        for (int i = 0; i < K; ++i) {
            long double ang = rnd.next() * 2.0L * PI; // [0, 2π)
            int r = rnd.next(3, 10);
            long double x = (long double)r * cosl(ang);
            long double y = (long double)r * sinl(ang);
            long long ix = (long long)llroundl(x);
            long long iy = (long long)llroundl(y);
            if (ix == 0 && iy == 0) continue;
            pts.push_back({ix, iy});
        }
        if (pts.size() < 3) continue;

        vector<P> hull = convexHull(pts);
        int n = (int)hull.size();
        if (n < 3 || n > 10) continue;

        // Ensure CCW
        if (area2(hull) < 0) {
            reverse(hull.begin(), hull.end());
        }

        // Require origin strictly inside
        P origin{0, 0};
        if (!strictlyInside(hull, origin)) continue;

        return hull;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate a random convex polygon with origin strictly inside
    vector<P> base = generateBasePolygon();
    int N = (int)base.size();
    int M = N;

    // Choose scale factor so that blue is inside red
    int S = rnd.next(2, 10); // overall scale
    vector<P> red(N), blue(N);
    for (int i = 0; i < N; ++i) {
        blue[i].x = base[i].x * S;
        blue[i].y = base[i].y * S;
        red[i].x  = base[i].x * (2 * S);
        red[i].y  = base[i].y * (2 * S);
    }

    // Decide number of queries, small but variable
    int Q;
    if (rnd.next(0, 4) == 0) Q = rnd.next(1, 3);      // sometimes very small
    else                     Q = rnd.next(3, 10);     // otherwise medium-small

    // Prepare query types: 0 = OUT, 1 = IN, 2 = BETWEEN
    vector<int> types;
    if (Q == 1) {
        types.push_back(rnd.next(0, 2));
    } else if (Q == 2) {
        types = {0, 1};
        if (rnd.next(0, 1)) swap(types[0], types[1]);
    } else {
        types = {0, 1, 2};
        for (int i = 3; i < Q; ++i) types.push_back(rnd.next(0, 2));
        shuffle(types.begin(), types.end());
    }

    vector<P> queries;
    queries.reserve(Q);

    // Generate queries matching the desired types
    for (int t : types) {
        if (t == 1) {
            // IN: pick origin (guaranteed strictly inside both polygons)
            P p{0, 0};
            queries.push_back(p);
        } else if (t == 0) {
            // OUT: point clearly outside red, along some vertex ray
            P p;
            while (true) {
                int i = rnd.next(0, N - 1);
                // red vertex is at factor 2S; go further out
                int k = 2 * S + rnd.next(1, 5 * S);
                p.x = base[i].x * k;
                p.y = base[i].y * k;
                if (pointInConvex(red, p) == -1) break;
            }
            queries.push_back(p);
        } else {
            // BETWEEN: inside red but outside blue
            P p;
            while (true) {
                int i = rnd.next(0, N - 1);
                // choose integer factor strictly between S and 2S
                int k = S + rnd.next(1, S - 1); // since S>=2, this is valid
                p.x = base[i].x * k;
                p.y = base[i].y * k;
                int inRed = pointInConvex(red, p);
                int inBlue = pointInConvex(blue, p);
                if (inRed == 1 && inBlue == -1) break;
            }
            queries.push_back(p);
        }
    }

    // Output
    println(N, M, Q);
    for (int i = 0; i < N; ++i)
        println(red[i].x, red[i].y);
    for (int i = 0; i < M; ++i)
        println(blue[i].x, blue[i].y);
    for (int i = 0; i < Q; ++i)
        println(queries[i].x, queries[i].y);

    return 0;
}
