#include "testlib.h"
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y, z;
};

double dist(const Point &a, const Point &b) {
    long double dx = (long double)a.x - (long double)b.x;
    long double dy = (long double)a.y - (long double)b.y;
    long double dz = (long double)a.z - (long double)b.z;
    return sqrt((long double)(dx * dx + dy * dy + dz * dz));
}

// Compute minimal total distance from some point in R^3 to three points p[0..2].
// Minimal sum of distances to three points in 3D is obtained in their affine span,
// which is at most 2D, so treating them geometrically is safe.
// We'll use Weiszfeld-like gradient descent with multiple restarts to ensure
// numerical robustness sufficient for validation of basic guarantees.
double minimalTotalDistance(const vector<Point> &p) {
    // If there are duplicate points, it's still fine: the sum is minimized at that point.
    // Simple multi-start gradient descent around centroid and each point.
    const int STARTS = 7;
    const int STEPS = 2000;
    const double INIT_STEP = 1e9; // size scale comparable with |coords|
    const double STEP_DECAY = 0.5;

    struct DPoint { double x, y, z; };
    auto totalDist = [&](const DPoint &q) {
        long double s = 0.0L;
        for (int i = 0; i < 3; ++i) {
            long double dx = q.x - (long double)p[i].x;
            long double dy = q.y - (long double)p[i].y;
            long double dz = q.z - (long double)p[i].z;
            s += sqrt(dx * dx + dy * dy + dz * dz);
        }
        return (double)s;
    };

    vector<DPoint> starts;
    // centroid
    {
        DPoint c;
        c.x = (p[0].x + p[1].x + p[2].x) / 3.0;
        c.y = (p[0].y + p[1].y + p[2].y) / 3.0;
        c.z = (p[0].z + p[1].z + p[2].z) / 3.0;
        starts.push_back(c);
    }
    // each vertex
    for (int i = 0; i < 3; ++i) {
        DPoint v;
        v.x = p[i].x;
        v.y = p[i].y;
        v.z = p[i].z;
        starts.push_back(v);
    }
    // midpoints
    for (int i = 0; i < 3; ++i) {
        DPoint m;
        int j = (i + 1) % 3;
        m.x = (p[i].x + p[j].x) / 2.0;
        m.y = (p[i].y + p[j].y) / 2.0;
        m.z = (p[i].z + p[j].z) / 2.0;
        starts.push_back(m);
    }

    double best = 1e300;
    for (int si = 0; si < (int)starts.size(); ++si) {
        DPoint cur = starts[si];
        double step = INIT_STEP;
        double curVal = totalDist(cur);
        for (int it = 0; it < STEPS; ++it) {
            bool improved = false;
            // Explore 6 directions
            static const int DIRS = 6;
            static const int dx[DIRS] = {1,-1,0,0,0,0};
            static const int dy[DIRS] = {0,0,1,-1,0,0};
            static const int dz[DIRS] = {0,0,0,0,1,-1};
            for (int d = 0; d < DIRS; ++d) {
                DPoint nxt = cur;
                nxt.x += dx[d] * step;
                nxt.y += dy[d] * step;
                nxt.z += dz[d] * step;
                double val = totalDist(nxt);
                if (val + 1e-12 < curVal) {
                    cur = nxt;
                    curVal = val;
                    improved = true;
                }
            }
            if (!improved) step *= STEP_DECAY;
            if (step < 1e-4) break;
        }
        best = min(best, curVal);
    }
    return best;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MINC = -1000000000LL;
    const long long MAXC =  1000000000LL;

    vector<Point> pts(3);
    for (int i = 0; i < 3; ++i) {
        pts[i].x = inf.readLong(MINC, MAXC, "x");
        inf.readSpace();
        pts[i].y = inf.readLong(MINC, MAXC, "y");
        inf.readSpace();
        pts[i].z = inf.readLong(MINC, MAXC, "z");
        inf.readEoln();
    }

    // There is always a finite minimal total distance; we can compute it.
    // The problem has no claim like "answer <= X" or "always exists" that needs
    // further nontrivial validation beyond that the sum of distances is finite,
    // which is guaranteed for any three finite points. Still, we verify that our
    // computation gives a finite value to catch pathological coordinates if any.
    double ans = minimalTotalDistance(pts);
    ensuref(isfinite(ans), "Computed minimal total distance is not finite");

    inf.readEof();
}
