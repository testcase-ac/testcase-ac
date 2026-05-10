#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

struct Point {
    int x, y;
};

long long cross(const Point &a, const Point &b, const Point &c) {
    // cross product of AB x AC
    return (long long)(b.x - a.x) * (c.y - a.y) - (long long)(b.y - a.y) * (c.x - a.x);
}

bool onSegment(const Point &a, const Point &b, const Point &p) {
    // check if p lies on segment ab (assuming collinear)
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x)
        && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

bool segmentsIntersect(const Point &a1, const Point &a2,
                       const Point &b1, const Point &b2) {
    long long c1 = cross(a1, a2, b1);
    long long c2 = cross(a1, a2, b2);
    long long c3 = cross(b1, b2, a1);
    long long c4 = cross(b1, b2, a2);
    // proper intersection
    if (c1 > 0 && c2 < 0 || c1 < 0 && c2 > 0)
        if (c3 > 0 && c4 < 0 || c3 < 0 && c4 > 0)
            return true;
    // check collinear and overlapping
    if (c1 == 0 && onSegment(a1, a2, b1)) return true;
    if (c2 == 0 && onSegment(a1, a2, b2)) return true;
    if (c3 == 0 && onSegment(b1, b2, a1)) return true;
    if (c4 == 0 && onSegment(b1, b2, a2)) return true;
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    while (true) {
        // read number of vertices or 0
        int n = inf.readInt(0, 100, "n");
        inf.readEoln();
        if (n == 0) {
            break;
        }
        // real test case
        ++tc;
        setTestCase(tc);
        // Validate n
        ensuref(n >= 3, "Number of vertices n must be >= 3, found %d", n);

        vector<Point> pts(n);
        set<pair<int,int>> seen;
        for (int i = 0; i < n; i++) {
            pts[i].x = inf.readInt(0, 10000, "x_i");
            inf.readSpace();
            pts[i].y = inf.readInt(0, 10000, "y_i");
            inf.readEoln();
            // check distinct vertices
            pair<int,int> pr = make_pair(pts[i].x, pts[i].y);
            ensuref(!seen.count(pr),
                    "Duplicate vertex at index %d: (%d, %d)", i, pts[i].x, pts[i].y);
            seen.insert(pr);
        }

        // Check that the polygon is simple: no self-intersection
        for (int i = 0; i < n; i++) {
            int ni = (i + 1) % n;
            for (int j = i + 1; j < n; j++) {
                int nj = (j + 1) % n;
                // skip same edge
                if (i == j) continue;
                // skip adjacent edges (share a vertex)
                if (ni == j || nj == i) continue;
                // now edges (i,ni) and (j,nj) should not intersect
                if (segmentsIntersect(pts[i], pts[ni], pts[j], pts[nj])) {
                    ensuref(false,
                            "Edges (%d->%d) and (%d->%d) intersect or touch",
                            i, ni, j, nj);
                }
            }
        }
    }

    inf.readEof();
    return 0;
}
