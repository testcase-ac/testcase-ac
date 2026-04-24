#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Room dimensions
    int W = rnd.next(5, 20);
    int H = rnd.next(5, 20);
    // Carpet size hyper-parameter: small, medium or large
    int mm = min(W, H);
    int smallMax = max(1, mm / 4);
    int mediumMin = smallMax;
    int mediumMax = max(1, mm / 2);
    int largeMin = mediumMax;
    int largeMax = mm;
    double tl = rnd.next();
    int L;
    if (tl < 0.3) {
        L = rnd.next(1, smallMax);
    } else if (tl < 0.7) {
        L = rnd.next(mediumMin, mediumMax);
    } else {
        L = rnd.next(largeMin, largeMax);
    }

    // Number of stains
    int N = rnd.next(1, 10);
    vector<array<int,4>> rects; // store as {x0, y0, x1, y1}

    // Generate non-overlapping stains
    for (int i = 0; i < N; i++) {
        int tries = 0;
        while (tries < 500) {
            tries++;
            // Size category: small / medium / large
            double tc = rnd.next();
            int w, h;
            if (tc < 0.3) {
                // small
                int maxw = max(1, W / 4);
                int maxh = max(1, H / 4);
                w = rnd.next(1, maxw);
                h = rnd.next(1, maxh);
            } else if (tc < 0.7) {
                // medium
                int minw = max(1, W / 4);
                int minh = max(1, H / 4);
                int maxw = max(1, W / 2);
                int maxh = max(1, H / 2);
                w = rnd.next(minw, maxw);
                h = rnd.next(minh, maxh);
            } else {
                // large
                int minw = max(1, W / 2);
                int minh = max(1, H / 2);
                w = rnd.next(minw, W);
                h = rnd.next(minh, H);
            }
            if (w > W || h > H) continue;
            int x0 = rnd.next(0, W - w);
            int y0 = rnd.next(0, H - h);
            int x1 = x0 + w;
            int y1 = y0 + h;
            bool ok = true;
            for (auto &r : rects) {
                // r = {rx0, ry0, rx1, ry1}
                if (x0 < r[2] && r[0] < x1 && y0 < r[3] && r[1] < y1) {
                    ok = false;
                    break;
                }
            }
            if (!ok) continue;
            rects.push_back({x0, y0, x1, y1});
            break;
        }
    }

    // Output
    // Room: left-top (0,H), right-bottom (W,0)
    println(0, H, W, 0);
    println(L);
    println((int)rects.size());
    for (auto &r : rects) {
        int x0 = r[0], y0 = r[1], x1 = r[2], y1 = r[3];
        // stain as left-top (x0,y1) and right-bottom (x1,y0)
        println(x0, y1, x1, y0);
    }

    return 0;
}
