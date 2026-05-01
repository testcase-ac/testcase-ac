#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;

struct Point { int x, y; };

vector<Point> genConvex(int n, int coordMax) {
    vector<int> xs(n), ys(n);
    for (int i = 0; i < n; i++) {
        xs[i] = rnd.next(1, coordMax);
        ys[i] = rnd.next(1, coordMax);
    }
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    vector<int> xVec(n), yVec(n);
    int minX = xs[0], maxX = xs[n-1];
    int minY = ys[0], maxY = ys[n-1];
    int lastX = minX, lastY = minY;
    for (int i = 1; i < n-1; i++) {
        int xv = xs[i] - lastX; xVec[i] = xv; lastX = xs[i];
        int yv = ys[i] - lastY; yVec[i] = yv; lastY = ys[i];
    }
    xVec[0] = xs[0] - minX;         // zero
    xVec[n-1] = maxX - lastX;
    yVec[0] = ys[0] - minY;         // zero
    yVec[n-1] = maxY - lastY;
    shuffle(xVec.begin(), xVec.end());
    shuffle(yVec.begin(), yVec.end());
    struct Vec { int x, y; };
    vector<Vec> vecs(n);
    for (int i = 0; i < n; i++) vecs[i] = { xVec[i], yVec[i] };
    sort(vecs.begin(), vecs.end(), [](const Vec &a, const Vec &b) {
        return atan2(a.y, a.x) < atan2(b.y, b.x);
    });
    vector<Point> pts(n);
    int curX = 0, curY = 0;
    for (int i = 0; i < n; i++) {
        pts[i] = { curX, curY };
        curX += vecs[i].x;
        curY += vecs[i].y;
    }
    long long sumX = 0, sumY = 0;
    for (auto &p : pts) { sumX += p.x; sumY += p.y; }
    int offX = coordMax/2 - int(sumX / n);
    int offY = coordMax/2 - int(sumY / n);
    for (auto &p : pts) {
        p.x += offX;
        p.y += offY;
    }
    return pts;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters
    int n = rnd.wnext(8, 1) + 4; // n in [4..12] biased
    int coordMax = rnd.any(vector<int>{20, 50, 100, 500, 1000});
    vector<Point> poly;
    // Retry if invalid (duplicates or out of bounds)
    while (true) {
        poly = genConvex(n, coordMax);
        set<pair<int,int>> seen;
        bool ok = true;
        for (auto &p : poly) {
            if (p.x < 1 || p.x > coordMax || p.y < 1 || p.y > coordMax) {
                ok = false; break;
            }
            seen.insert({p.x, p.y});
        }
        if (ok && int(seen.size()) == n) break;
    }
    // Convert CCW to CW
    reverse(poly.begin(), poly.end());
    // Output
    println(n);
    for (auto &p : poly) println(p.x, p.y);
    return 0;
}
