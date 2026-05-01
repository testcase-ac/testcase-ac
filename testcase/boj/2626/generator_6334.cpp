#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of islands
    int N = rnd.next(2, 15);
    // Possible maximum coordinate radii
    vector<int> Rs = {10, 100, 1000, 10000, 30000};
    int Rmax = rnd.any(Rs);

    // Choose a generation pattern
    int caseType = rnd.next(0, 3);
    vector<pair<int,int>> pts;
    const double PI = acos(-1.0);

    if (caseType == 0) {
        // Uniform random points
        for (int i = 0; i < N; i++) {
            int x = rnd.next(-Rmax, Rmax);
            int y = rnd.next(-Rmax, Rmax);
            pts.emplace_back(x, y);
        }
    } else if (caseType == 1) {
        // All colinear: either vertical or horizontal
        bool vertical = rnd.next(0, 1) == 0;
        if (vertical) {
            int x0 = rnd.next(-Rmax, Rmax);
            for (int i = 0; i < N; i++) {
                int y = rnd.next(-Rmax, Rmax);
                pts.emplace_back(x0, y);
            }
        } else {
            int y0 = rnd.next(-Rmax, Rmax);
            for (int i = 0; i < N; i++) {
                int x = rnd.next(-Rmax, Rmax);
                pts.emplace_back(x, y0);
            }
        }
    } else if (caseType == 2) {
        // Two clusters
        int half = N / 2;
        int x1 = rnd.next(-Rmax, Rmax), y1 = rnd.next(-Rmax, Rmax);
        int x2 = rnd.next(-Rmax, Rmax), y2 = rnd.next(-Rmax, Rmax);
        int dev = max(1, Rmax / 10);
        for (int i = 0; i < N; i++) {
            int cx = (i < half ? x1 : x2);
            int cy = (i < half ? y1 : y2);
            int x = cx + rnd.next(-dev, dev);
            int y = cy + rnd.next(-dev, dev);
            // Clamp to valid coordinate range
            x = max(-30000, min(30000, x));
            y = max(-30000, min(30000, y));
            pts.emplace_back(x, y);
        }
    } else {
        // Circle-like distribution
        int cx = rnd.next(-Rmax/2, Rmax/2);
        int cy = rnd.next(-Rmax/2, Rmax/2);
        int rad = rnd.next(1, max(1, Rmax/2));
        int devr = max(1, rad / 10);
        for (int i = 0; i < N; i++) {
            double baseAng = 2 * PI * i / N;
            double jitterAng = rnd.next(-1000, 1000) / 1000.0;
            double rr = rad + rnd.next(-devr, devr);
            double ang = baseAng + jitterAng;
            int x = int(round(cx + rr * cos(ang)));
            int y = int(round(cy + rr * sin(ang)));
            // Clamp to valid coordinate range
            x = max(-30000, min(30000, x));
            y = max(-30000, min(30000, y));
            pts.emplace_back(x, y);
        }
    }

    // Shuffle to avoid any ordering bias
    shuffle(pts.begin(), pts.end());

    // Output
    println(N);
    for (auto &p : pts) {
        println(p.first, p.second);
    }

    return 0;
}
