#include "testlib.h"
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const double PI = acos(-1.0);
    int distType = rnd.next(0, 4);
    int n = 0;
    if (distType == 0) {
        n = rnd.next(2, 10);
    } else if (distType == 1) {
        n = rnd.next(20, 30);
    } else if (distType == 2) {
        n = rnd.next(20, 30);
    } else if (distType == 3) {
        n = rnd.next(10, 20);
    } else {
        n = rnd.next(10, 20);
    }
    set<pair<int,int>> seen;
    vector<pair<int,int>> pts;
    auto clampVal = [&](int v) {
        if (v < 0) return 0;
        if (v > 10000) return 10000;
        return v;
    };
    if (distType == 0 || distType == 1) {
        // pure random
        while ((int)pts.size() < n) {
            int x = rnd.next(0, 10000);
            int y = rnd.next(0, 10000);
            if (seen.insert({x,y}).second) {
                pts.emplace_back(x, y);
            }
        }
    } else if (distType == 2) {
        // two clusters
        int n1 = rnd.next(1, n-1), n2 = n - n1;
        int cx1 = rnd.next(0, 10000), cy1 = rnd.next(0, 10000);
        int cx2 = rnd.next(0, 10000), cy2 = rnd.next(0, 10000);
        int r1 = rnd.next(10, 100), r2 = rnd.next(10, 100);
        while ((int)pts.size() < n1) {
            double ang = rnd.next() * 2 * PI;
            double d = rnd.next() * r1;
            int x = clampVal(int(round(cx1 + cos(ang) * d)));
            int y = clampVal(int(round(cy1 + sin(ang) * d)));
            if (seen.insert({x,y}).second) pts.emplace_back(x,y);
        }
        while ((int)pts.size() < n) {
            double ang = rnd.next() * 2 * PI;
            double d = rnd.next() * r2;
            int x = clampVal(int(round(cx2 + cos(ang) * d)));
            int y = clampVal(int(round(cy2 + sin(ang) * d)));
            if (seen.insert({x,y}).second) pts.emplace_back(x,y);
        }
    } else if (distType == 3) {
        // circle with jitter
        int cx = rnd.next(0, 10000), cy = rnd.next(0, 10000);
        double rad = rnd.next(100, 500);
        for (int i = 0; i < n; i++) {
            double baseAng = 2 * PI * i / n;
            double angNoise = (rnd.next() - 0.5) * (2 * PI / n);
            double angle = baseAng + angNoise;
            double rNoise = (rnd.next() - 0.5) * (rad * 0.4);
            double curR = rad + rNoise;
            int x = clampVal(int(round(cx + cos(angle) * curR)));
            int y = clampVal(int(round(cy + sin(angle) * curR)));
            if (seen.insert({x,y}).second) pts.emplace_back(x,y);
            else i--; // retry this index
        }
    } else {
        // nearly colinear line with jitter
        int x0 = rnd.next(0, 10000), y0 = rnd.next(0, 10000);
        int x1 = rnd.next(0, 10000), y1 = rnd.next(0, 10000);
        double dx = x1 - x0, dy = y1 - y0;
        double len = sqrt(dx*dx + dy*dy);
        double nx = len > 0 ? -dy/len : 0;
        double ny = len > 0 ? dx/len : 0;
        for (int i = 0; i < n; i++) {
            double t = rnd.next();
            double bx = x0 + t * dx;
            double by = y0 + t * dy;
            double jitter = (rnd.next() - 0.5) * 100.0;
            int x = clampVal(int(round(bx + nx * jitter)));
            int y = clampVal(int(round(by + ny * jitter)));
            if (seen.insert({x,y}).second) pts.emplace_back(x,y);
            else i--;
        }
    }
    shuffle(pts.begin(), pts.end());
    println((int)pts.size());
    for (auto &p : pts) println(p.first, p.second);
    return 0;
}
