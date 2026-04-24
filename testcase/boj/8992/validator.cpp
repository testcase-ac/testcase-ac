#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct HSeg {
    int y, xl, xr, w, idx;
};

struct VSeg {
    int x, yl, yr, w, idx;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // read n, m
        int n = inf.readInt(1, 200, "n");
        inf.readSpace();
        int m = inf.readInt(1, 200, "m");
        inf.readEoln();

        vector<HSeg> H;
        H.reserve(n);
        for (int i = 0; i < n; i++) {
            int x1 = inf.readInt(1, 100000, "x1");
            inf.readSpace();
            int y1 = inf.readInt(1, 100000, "y1");
            inf.readSpace();
            int x2 = inf.readInt(1, 100000, "x2");
            inf.readSpace();
            int y2 = inf.readInt(1, 100000, "y2");
            inf.readSpace();
            int w  = inf.readInt(1, 20,     "w");
            inf.readEoln();

            // must be horizontal: y1 == y2, x1 != x2
            ensuref(y1 == y2, "Horizontal segment %d: y1 != y2 (%d vs %d)", i, y1, y2);
            ensuref(x1 != x2, "Horizontal segment %d is degenerate: x1 == x2 == %d", i, x1);
            int xl = min(x1, x2);
            int xr = max(x1, x2);
            H.push_back({y1, xl, xr, w, i});
        }

        vector<VSeg> V;
        V.reserve(m);
        for (int j = 0; j < m; j++) {
            int x1 = inf.readInt(1, 100000, "x1");
            inf.readSpace();
            int y1 = inf.readInt(1, 100000, "y1");
            inf.readSpace();
            int x2 = inf.readInt(1, 100000, "x2");
            inf.readSpace();
            int y2 = inf.readInt(1, 100000, "y2");
            inf.readSpace();
            int w  = inf.readInt(1, 20,     "w");
            inf.readEoln();

            // must be vertical: x1 == x2, y1 != y2
            ensuref(x1 == x2, "Vertical segment %d: x1 != x2 (%d vs %d)", j, x1, x2);
            ensuref(y1 != y2, "Vertical segment %d is degenerate: y1 == y2 == %d", j, y1);
            int yl = min(y1, y2);
            int yr = max(y1, y2);
            V.push_back({x1, yl, yr, w, j});
        }

        // Check horizontal segments on same y do not overlap or touch
        sort(H.begin(), H.end(), [](const HSeg &a, const HSeg &b){
            if (a.y != b.y) return a.y < b.y;
            return a.xl < b.xl;
        });
        for (int i = 1; i < n; i++) {
            if (H[i].y == H[i-1].y) {
                // ensure no common point: H[i].xl > H[i-1].xr
                ensuref(H[i].xl > H[i-1].xr,
                    "Horizontal segments %d and %d on y=%d overlap or touch: [%d,%d] vs [%d,%d]",
                    H[i-1].idx, H[i].idx, H[i].y,
                    H[i-1].xl, H[i-1].xr, H[i].xl, H[i].xr);
            }
        }

        // Check vertical segments on same x do not overlap or touch
        sort(V.begin(), V.end(), [](const VSeg &a, const VSeg &b){
            if (a.x != b.x) return a.x < b.x;
            return a.yl < b.yl;
        });
        for (int i = 1; i < m; i++) {
            if (V[i].x == V[i-1].x) {
                // ensure no common point: V[i].yl > V[i-1].yr
                ensuref(V[i].yl > V[i-1].yr,
                    "Vertical segments %d and %d on x=%d overlap or touch: [%d,%d] vs [%d,%d]",
                    V[i-1].idx, V[i].idx, V[i].x,
                    V[i-1].yl, V[i-1].yr, V[i].yl, V[i].yr);
            }
        }

        // Check that any intersection of H and V is interior-to-interior, not at endpoints
        for (const auto &h : H) {
            for (const auto &v : V) {
                // check if bounding boxes intersect
                if (v.x >= h.xl && v.x <= h.xr && h.y >= v.yl && h.y <= v.yr) {
                    // then must be strict interior intersection
                    bool strict = (v.x > h.xl && v.x < h.xr && h.y > v.yl && h.y < v.yr);
                    ensuref(strict,
                        "Intersection at endpoint between H-seg %d and V-seg %d at point (%d,%d)",
                        h.idx, v.idx, v.x, h.y);
                }
            }
        }
    }
    inf.readEof();
    return 0;
}
