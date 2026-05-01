#include "testlib.h"
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(3, 7);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // start and end points, distinct
        int x1, y1, x2, y2;
        do {
            x1 = rnd.next(-1000, 1000);
            y1 = rnd.next(-1000, 1000);
            x2 = rnd.next(-1000, 1000);
            y2 = rnd.next(-1000, 1000);
        } while (x1 == x2 && y1 == y2);

        // number of circles
        int n = rnd.next(1, 12);
        vector<tuple<int,int,int>> circles;

        // occasionally force a small nested pair to test nesting
        if (n >= 2 && rnd.next(1,5) == 1) {
            int cx = rnd.next(-800, 800);
            int cy = rnd.next(-800, 800);
            int r_big = rnd.next(100, 300);
            int r_small = rnd.next(1, r_big - 1);
            circles.emplace_back(cx, cy, r_big);
            circles.emplace_back(cx, cy, r_small);
        }

        // helper to check boundary conflict with start/end
        auto onBoundary = [&](int cx, int cy, int r, int x, int y) {
            long long dx = x - cx, dy = y - cy;
            return dx*dx + dy*dy == 1LL * r * r;
        };

        // generate remaining circles
        while ((int)circles.size() < n) {
            int cx = rnd.next(-800, 800);
            int cy = rnd.next(-800, 800);
            int t = rnd.next(-1, 1);
            int r = rnd.wnext(300, t) + 1;  // radius in [1,300]
            // avoid start/end exactly on boundary
            if (onBoundary(cx, cy, r, x1, y1) || onBoundary(cx, cy, r, x2, y2))
                continue;
            bool ok = true;
            for (auto &c : circles) {
                int cxj, cyj, rj;
                tie(cxj, cyj, rj) = c;
                long long dx = cx - cxj, dy = cy - cyj;
                long long d2 = dx*dx + dy*dy;
                long long sum = r + rj;
                long long diff = abs(r - rj);
                long long sum2 = sum * sum;
                long long diff2 = diff * diff;
                // must be either strictly disjoint or strictly nested
                if (!(d2 > sum2 || d2 < diff2)) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                circles.emplace_back(cx, cy, r);
            }
        }

        // output one test
        println(x1, y1, x2, y2);
        println((int)circles.size());
        for (auto &c : circles) {
            int cx, cy, r;
            tie(cx, cy, r) = c;
            println(cx, cy, r);
        }
    }

    return 0;
}
