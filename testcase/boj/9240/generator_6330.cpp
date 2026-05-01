#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of arrows
    int C = rnd.next(2, 30);
    int type = rnd.next(0, 3);
    vector<pair<int,int>> pts;
    pts.reserve(C);

    if (type == 0) {
        // Uniform points in a box
        int R = rnd.next(0, 1000);
        for (int i = 0; i < C; i++) {
            int x = rnd.next(-R, R);
            int y = rnd.next(-R, R);
            pts.emplace_back(x, y);
        }
    } else if (type == 1) {
        // Points roughly on a circle with small jitter
        const double PI = acos(-1.0);
        int R = rnd.next(1, 1000);
        int jit = rnd.next(0, 10);
        for (int i = 0; i < C; i++) {
            double theta = 2 * PI * i / C;
            double dx = R * cos(theta) + rnd.next(-jit, jit);
            double dy = R * sin(theta) + rnd.next(-jit, jit);
            int x = int(round(dx));
            int y = int(round(dy));
            x = max(-1000, min(1000, x));
            y = max(-1000, min(1000, y));
            pts.emplace_back(x, y);
        }
        shuffle(pts.begin(), pts.end());
    } else if (type == 2) {
        // Collinear points between two random endpoints
        int x1 = rnd.next(-1000, 1000);
        int y1 = rnd.next(-1000, 1000);
        int x2, y2;
        do {
            x2 = rnd.next(-1000, 1000);
            y2 = rnd.next(-1000, 1000);
        } while (x2 == x1 && y2 == y1);
        for (int i = 0; i < C; i++) {
            double t = rnd.next(); // [0,1)
            double xd = x1 * (1 - t) + x2 * t;
            double yd = y1 * (1 - t) + y2 * t;
            int xi = int(round(xd));
            int yi = int(round(yd));
            pts.emplace_back(xi, yi);
        }
        // Maybe sprinkle small noise on a few points
        int noiseCount = rnd.next(0, C/4);
        for (int i = 0; i < noiseCount; i++) {
            int idx = rnd.next(0, C-1);
            pts[idx].first += rnd.next(-3, 3);
            pts[idx].second += rnd.next(-3, 3);
        }
    } else {
        // Two clusters far apart
        int cx1 = rnd.next(-1000, 1000);
        int cy1 = rnd.next(-1000, 1000);
        int cx2, cy2;
        do {
            cx2 = rnd.next(-1000, 1000);
            cy2 = rnd.next(-1000, 1000);
        } while (hypot(cx2-cx1, cy2-cy1) < 300);
        int c1 = rnd.next(1, C-1), c2 = C - c1;
        int jit = rnd.next(0, 50);
        for (int i = 0; i < c1; i++)
            pts.emplace_back(
                max(-1000, min(1000, cx1 + rnd.next(-jit, jit))),
                max(-1000, min(1000, cy1 + rnd.next(-jit, jit)))
            );
        for (int i = 0; i < c2; i++)
            pts.emplace_back(
                max(-1000, min(1000, cx2 + rnd.next(-jit, jit))),
                max(-1000, min(1000, cy2 + rnd.next(-jit, jit)))
            );
        shuffle(pts.begin(), pts.end());
    }

    // Output
    println(C);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
