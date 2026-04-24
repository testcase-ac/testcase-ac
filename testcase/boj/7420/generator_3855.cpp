#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of buildings and minimum distance
    int N = rnd.next(3, 10);
    int L = rnd.next(1, 1000);

    // bounding box sizes for diversity
    vector<int> Bchoices = {20, 200, 2000};
    int B = rnd.any(Bchoices);

    // pick a pattern for point distribution
    int pattern = rnd.next(0, 3);

    set<pair<int,int>> used;
    vector<pair<int,int>> pts;

    // try to add a point if unique and within global bounds
    auto add_point = [&](int x, int y) {
        if (x < -10000 || x > 10000 || y < -10000 || y > 10000)
            return false;
        pair<int,int> p = {x, y};
        if (used.insert(p).second) {
            pts.push_back(p);
            return true;
        }
        return false;
    };

    const double PI = acos(-1.0);

    if (pattern == 0) {
        // uniform random points in [-B, B]
        for (int i = 0; i < N; i++) {
            int x, y;
            do {
                x = rnd.next(-B, B);
                y = rnd.next(-B, B);
            } while (!add_point(x, y));
        }
    }
    else if (pattern == 1) {
        // clustered points
        int C = rnd.next(1, min(N, 3));
        vector<int> sizes(C, 1);
        int rem = N - C;
        while (rem-- > 0) {
            sizes[rnd.next(0, C - 1)]++;
        }
        for (int i = 0; i < C; i++) {
            int cx = rnd.next(-B, B);
            int cy = rnd.next(-B, B);
            vector<int> radii = { max(1, B/20), max(1, B/10), max(1, B/5) };
            int r = rnd.any(radii);
            for (int t = 0; t < sizes[i]; t++) {
                int tries = 0;
                while (tries++ < 1000) {
                    int x = cx + rnd.next(-r, r);
                    int y = cy + rnd.next(-r, r);
                    if (add_point(x, y)) break;
                }
            }
        }
    }
    else if (pattern == 2) {
        // mostly collinear points
        int k = rnd.next(2, N);
        int dx, dy;
        do {
            dx = rnd.next(-2, 2);
            dy = rnd.next(-2, 2);
        } while (dx == 0 && dy == 0);
        int x0 = rnd.next(-B, B);
        int y0 = rnd.next(-B, B);
        for (int i = 0; i < k; i++) {
            add_point(x0 + i*dx, y0 + i*dy);
        }
    }
    else {
        // roughly on a circle
        int cx = rnd.next(-B, B);
        int cy = rnd.next(-B, B);
        int R = rnd.next(1, max(1, B/2));
        for (int i = 0; i < N; i++) {
            double base = 2 * PI * i / N;
            double noise = (rnd.next(-100, 100) / 100.0) * (PI / N);
            double ang = base + noise;
            int x = int(round(cx + R * cos(ang)));
            int y = int(round(cy + R * sin(ang)));
            add_point(x, y);
        }
    }

    // fill any missing points uniformly
    while ((int)pts.size() < N) {
        int x = rnd.next(-B, B);
        int y = rnd.next(-B, B);
        add_point(x, y);
    }

    // shuffle and output
    shuffle(pts.begin(), pts.end());
    println(N, L);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
