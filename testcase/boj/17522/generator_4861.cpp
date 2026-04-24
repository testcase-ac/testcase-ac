#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of houses
    int n = rnd.next(1, 10);
    // choose a pattern for diversity
    int pattern = rnd.next(0, 3);
    // parameters for patterns
    int cx = 0, cy = 0, vr = 0;
    int vx = 0;
    int g1 = 1, g2 = 1, d1 = 1, d2 = 1;
    if (pattern == 1) {
        // cluster pattern
        cx = rnd.next(-1000, 1000);
        cy = rnd.next(-1000, 1000);
        vr = rnd.next(0, 1000);
    } else if (pattern == 2) {
        // vertical line pattern
        vx = rnd.next(-1000, 1000);
    } else if (pattern == 3) {
        // small grid pattern
        g1 = rnd.next(1, min(3, n));
        g2 = max(1, (n + g1 - 1) / g1);
        d1 = rnd.next(1, 1000);
        d2 = rnd.next(1, 1000);
    }
    vector<pair<int,int>> pts;
    pts.reserve(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        // base generation
        if (pattern == 0) {
            // uniform random
            x = rnd.next(-1000000, 1000000);
            y = rnd.next(-1000000, 1000000);
        } else if (pattern == 1) {
            // clustered
            x = cx + rnd.next(-vr, vr);
            y = cy + rnd.next(-vr, vr);
        } else if (pattern == 2) {
            // vertical line
            x = vx;
            y = rnd.next(-1000000, 1000000);
        } else {
            // grid
            int gx = i % g1;
            int gy = i / g1;
            x = gx * d1;
            y = gy * d2;
        }
        // occasionally duplicate an existing point
        if (!pts.empty() && rnd.next(0, 4) == 0) {
            auto p = rnd.any(pts);
            x = p.first;
            y = p.second;
        }
        pts.emplace_back(x, y);
    }
    // shuffle to avoid any order bias
    shuffle(pts.begin(), pts.end());
    // output
    println(n);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
