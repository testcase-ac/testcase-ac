#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Total number of rectangles
    int N = rnd.next(1, 12);

    // Decide number of clusters (groups of rectangles)
    int clusterCnt = rnd.next(1, min(N, 3));

    // Distribute N into clusterCnt positive sizes
    vector<int> clusterSizes;
    int rem = N;
    for (int i = 0; i < clusterCnt - 1; i++) {
        int mx = rem - (clusterCnt - i - 1);
        int take = rnd.next(1, mx);
        clusterSizes.push_back(take);
        rem -= take;
    }
    clusterSizes.push_back(rem);

    vector<array<int,4>> rects;

    for (int c = 0; c < clusterCnt; c++) {
        int sz = clusterSizes[c];
        int type = rnd.next(0, 2);

        if (type == 0) {
            // Scattered-overlapping cluster
            int bx1 = rnd.next(-400, 350);
            int by1 = rnd.next(-400, 350);
            int bw = rnd.next(2, min(100, 500 - bx1));
            int bh = rnd.next(2, min(100, 500 - by1));
            int bx2 = bx1 + bw;
            int by2 = by1 + bh;
            for (int i = 0; i < sz; i++) {
                int x1 = rnd.next(bx1, bx2 - 1);
                int x2 = rnd.next(x1 + 1, bx2);
                int y1 = rnd.next(by1, by2 - 1);
                int y2 = rnd.next(y1 + 1, by2);
                rects.push_back({x1, y1, x2, y2});
            }
        }
        else if (type == 1) {
            // Nested rectangles
            int bx1 = rnd.next(-400, 300);
            int by1 = rnd.next(-400, 300);
            int bw = rnd.next(5, min(200, 500 - bx1));
            int bh = rnd.next(5, min(200, 500 - by1));
            int bx2 = bx1 + bw;
            int by2 = by1 + bh;
            for (int i = 0; i < sz; i++) {
                // shrink margins growing with i
                int maxShrinkX = (bx2 - bx1 - 1) / 2;
                int maxShrinkY = (by2 - by1 - 1) / 2;
                int shrinkLow = i * maxShrinkX / sz;
                int shrinkHigh = i * maxShrinkY / sz;
                int l = rnd.next(shrinkLow, maxShrinkX);
                int r = rnd.next(shrinkLow, maxShrinkX);
                int d = rnd.next(shrinkHigh, maxShrinkY);
                int u = rnd.next(shrinkHigh, maxShrinkY);
                int x1 = bx1 + l;
                int x2 = bx2 - r;
                int y1 = by1 + d;
                int y2 = by2 - u;
                if (x1 >= x2) x2 = x1 + 1;
                if (y1 >= y2) y2 = y1 + 1;
                rects.push_back({x1, y1, x2, y2});
            }
        }
        else {
            // Chain of rectangles sharing edges
            bool horiz = rnd.next(0,1) == 0;
            int sx = rnd.next(-400, 400);
            int sy = rnd.next(-400, 400);
            int w = rnd.next(2, 50);
            int h = rnd.next(2, 50);
            int overlap = rnd.next(0, min(horiz ? w-1 : h-1, 2));
            int dx = horiz ? (w - overlap) : 0;
            int dy = horiz ? 0 : (h - overlap);
            for (int i = 0; i < sz; i++) {
                int x1 = sx + dx * i;
                int y1 = sy + dy * i;
                int x2 = x1 + w;
                int y2 = y1 + h;
                // clamp within bounds
                if (x1 < -500) { x2 += -500 - x1; x1 = -500; }
                if (y1 < -500) { y2 += -500 - y1; y1 = -500; }
                if (x2 > 500) { x1 -= x2 - 500; x2 = 500; }
                if (y2 > 500) { y1 -= y2 - 500; y2 = 500; }
                rects.push_back({x1, y1, x2, y2});
            }
        }
    }

    // Shuffle overall order
    shuffle(rects.begin(), rects.end());

    // Output
    println(N);
    for (auto &r : rects) {
        println(r[0], r[1], r[2], r[3]);
    }

    return 0;
}
