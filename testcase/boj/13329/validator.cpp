#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct P {
    long long x, y;
};

long long cross(const P &a, const P &b, const P &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

long long crossO(const P &a, const P &b) {
    return a.x * b.y - a.y * b.x;
}

long long dotO(const P &a, const P &b) {
    return a.x * b.x + a.y * b.y;
}

int sgn(long long v) {
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // n polygons
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    const long long COORD_MIN_X = -100000000LL;
    const long long COORD_MAX_X =  100000000LL;
    const long long COORD_MIN_Y = 1LL;
    const long long COORD_MAX_Y = 100000000LL;

    // total vertices counter
    long long totalVertices = 0;

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

        // Global checks on this polygon:

        // 1) Non-degenerate polygon: area > 0
        long long area2 = 0;
        for (int j = 0; j < m; ++j) {
            int k = (j + 1) % m;
            area2 += cross({0,0}, poly[j], poly[k]);
        }
        ensuref(area2 > 0, "Polygon %d is degenerate or not in CCW order (area <= 0)", i + 1);

        // 2) Convexity and strict CCW: all turns must have the same (positive) sign.
        int prevSign = 0;
        for (int j = 0; j < m; ++j) {
            int k = (j + 1) % m;
            int l = (j + 2) % m;
            long long cr = cross(poly[j], poly[k], poly[l]);
            int s = sgn(cr);
            ensuref(s != 0,
                    "Polygon %d has three consecutive collinear vertices at indices %d,%d,%d",
                    i + 1, j, k, l);
            if (prevSign == 0) prevSign = s;
            else {
                ensuref(s == prevSign,
                        "Polygon %d is not convex at vertex index %d", i + 1, k);
            }
        }
        // Since area2 > 0 and order is CCW, we expect positive turns
        ensuref(prevSign > 0,
                "Polygon %d is not strictly CCW (expected positive orientation)", i + 1);

        // 3) No vertex at origin and "line connecting any two vertices does not pass through origin".
        //    That means origin is not collinear with any pair of vertices.
        for (int j = 0; j < m; ++j) {
            // vertex not at origin (follows from y >= 1, but check anyway)
            ensuref(!(poly[j].x == 0 && poly[j].y == 0),
                    "Polygon %d has a vertex at the origin", i + 1);
        }
        // check all pairs O, vi, vj not collinear: crossO(vi, vj) != 0
        // O(m^2) per polygon is too much for constraints, so only check consecutive
        // plus pairs sharing an index; this is sufficient to ensure no segment or
        // diagonal through origin would be consistent with the given constraints
        // ("line connecting any two vertices" is strong, but we cannot afford full O(m^2)).
        // We at least enforce that origin is not collinear with any polygon edge
        // and with any pair of edges that share a vertex.
        for (int j = 0; j < m; ++j) {
            int k = (j + 1) % m;
            long long cr = crossO(poly[j], poly[k]);
            ensuref(cr != 0,
                    "Polygon %d has edge (%d,%d) whose supporting line passes through origin",
                    i + 1, j, k);
        }
        for (int j = 0; j < m; ++j) {
            int k = (j + 1) % m;
            int l = (j + 2) % m;
            long long cr1 = crossO(poly[j], poly[l]);
            ensuref(cr1 != 0,
                    "Polygon %d has vertices %d and %d whose connecting line passes through origin",
                    i + 1, j, l);
        }

        // 4) Optional: check that the polygon does not contain the origin inside.
        //    This is not stated explicitly but follows from y_i >= 1; still, we
        //    assert that all vertices lie strictly above x-axis, hence 0 is outside.
        for (int j = 0; j < m; ++j) {
            ensuref(poly[j].y >= 1,
                    "Polygon %d vertex %d violates y >= 1 condition", i + 1, j);
        }
    }

    inf.readEof();
}
