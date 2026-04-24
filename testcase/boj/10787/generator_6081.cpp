#include "testlib.h"
#include <vector>
#include <tuple>
#include <cstdint>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of holes and slices
    int n = rnd.next(0, 15);
    int s = rnd.next(1, 15);

    vector<tuple<int,int,int,int>> holes;
    holes.reserve(n);
    const int LIM = 100000;
    // try placing holes without overlap
    for (int i = 0; i < n; i++) {
        bool placed = false;
        for (int it = 0; it < 2000; it++) {
            // radius: either small or large
            int r;
            if (rnd.next(0,2) == 0) r = rnd.next(100, 5000);
            else r = rnd.next(5001, 20000);
            // choose z-region: low, high, or full
            int region = rnd.next(0,2);
            int z;
            if (region == 0) {
                int zlo = r;
                int zhi = min(LIM - r, r + 20000);
                z = rnd.next(zlo, zhi);
            } else if (region == 1) {
                int zlo = max(r, LIM - r - 20000);
                int zhi = LIM - r;
                z = rnd.next(zlo, zhi);
            } else {
                z = rnd.next(r, LIM - r);
            }
            // x and y full
            int x = rnd.next(r, LIM - r);
            int y = rnd.next(r, LIM - r);
            // check overlap with existing
            bool ok = true;
            for (auto &h : holes) {
                int r2, x2, y2, z2;
                tie(r2, x2, y2, z2) = h;
                int64_t dx = x - x2;
                int64_t dy = y - y2;
                int64_t dz = z - z2;
                int64_t d2 = dx*dx + dy*dy + dz*dz;
                int64_t rr = int64_t(r) + r2;
                if (d2 < rr*rr) { ok = false; break; }
            }
            if (!ok) continue;
            // place it
            holes.emplace_back(r, x, y, z);
            placed = true;
            break;
        }
        if (!placed) break;
    }
    // actual count
    n = holes.size();
    // shuffle order
    shuffle(holes.begin(), holes.end());
    // output
    println(n, s);
    for (auto &h : holes) {
        int r, x, y, z;
        tie(r, x, y, z) = h;
        println(r, x, y, z);
    }
    return 0;
}
