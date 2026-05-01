#include "testlib.h"
using namespace std;

struct Rect {
    long long x1, x2, y1, y2;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Rect> rects;
    rects.reserve(20);

    int type = rnd.next(0, 6);

    if (type == 0) {
        // Small random cluster
        int N = rnd.next(1, 6);
        for (int i = 0; i < N; ++i) {
            long long x1 = rnd.next(0, 8);
            long long x2 = rnd.next(x1 + 1, 10LL);
            long long y1 = rnd.next(0, 8);
            long long y2 = rnd.next(y1 + 1, 10LL);
            rects.push_back({x1, x2, y1, y2});
        }
    } else if (type == 1) {
        // Overlapping chain along x-axis
        int N = rnd.next(3, 8);
        long long curX = 0;
        for (int i = 0; i < N; ++i) {
            long long width = rnd.next(1, 4);
            long long x1 = curX;
            long long x2 = x1 + width;
            long long y1 = rnd.next(0, 3);
            long long y2 = y1 + rnd.next(2, 6);
            rects.push_back({x1, x2, y1, y2});
            curX += rnd.next(0, (int)width); // ensures overlap or touch
        }
    } else if (type == 2) {
        // Vertical and horizontal stripes crossing
        int v = rnd.next(2, 3);
        int h = rnd.next(2, 3);
        vector<long long> vx1(v), vx2(v), hy1(h), hy2(h);

        long long cur = 0;
        for (int i = 0; i < v; ++i) {
            long long w = rnd.next(3, 5);
            vx1[i] = cur;
            vx2[i] = cur + w;
            cur += rnd.next(1, 3);
        }
        long long Xmax = vx2.back() + 2;

        cur = 0;
        for (int i = 0; i < h; ++i) {
            long long w = rnd.next(3, 5);
            hy1[i] = cur;
            hy2[i] = cur + w;
            cur += rnd.next(1, 3);
        }
        long long Ymax = hy2.back() + 2;

        for (int i = 0; i < v; ++i) {
            rects.push_back({vx1[i], vx2[i], 0, Ymax});
        }
        for (int i = 0; i < h; ++i) {
            rects.push_back({0, Xmax, hy1[i], hy2[i]});
        }
    } else if (type == 3) {
        // Nested / contained rectangles
        long long Lx = rnd.next(6, 15);
        long long Ly = rnd.next(6, 15);
        int k = rnd.next(3, 7);

        // Outer big rectangle
        rects.push_back({0, Lx, 0, Ly});

        // Inner rectangles strictly inside
        for (int i = 1; i < k; ++i) {
            long long x1 = rnd.next(1LL, Lx - 2);
            long long x2 = rnd.next(x1 + 1, Lx - 1);
            long long y1 = rnd.next(1LL, Ly - 2);
            long long y2 = rnd.next(y1 + 1, Ly - 1);
            rects.push_back({x1, x2, y1, y2});
        }
    } else if (type == 4) {
        // Duplicates and shared borders
        rects.push_back({0, 10, 0, 10});   // R0
        rects.push_back({0, 10, 0, 10});   // duplicate of R0
        rects.push_back({10, 15, 0, 10});  // touches right edge of R0
        rects.push_back({0, 10, 10, 15});  // touches top edge of R0
        rects.push_back({5, 15, 5, 15});   // overlaps R0 and extends outside
        rects.push_back({10, 20, 10, 20}); // overlaps R4 and extends
    } else if (type == 5) {
        // Large coordinates to test 64-bit handling
        const long long B = 1000000000LL;
        rects.push_back({0, B, 0, B});                                   // Huge base rectangle
        rects.push_back({B / 2, B, 0, B});                               // Right half overlapping
        rects.push_back({0, B, B - 300000000LL, B});                     // Top stripe
        rects.push_back({100000000LL, 900000000LL, 100000000LL, 900000000LL}); // Central block
        rects.push_back({0, 500000000LL, 0, 500000000LL});               // Bottom-left
    } else if (type == 6) {
        // Grid-based random rectangles with shared coordinates
        int Xn = rnd.next(3, 6);
        int Yn = rnd.next(3, 6);

        vector<long long> xs(Xn), ys(Yn);
        xs[0] = 0;
        for (int i = 1; i < Xn; ++i)
            xs[i] = xs[i - 1] + rnd.next(1, 4);
        ys[0] = 0;
        for (int i = 1; i < Yn; ++i)
            ys[i] = ys[i - 1] + rnd.next(1, 4);

        int N = rnd.next(3, 10);
        for (int t = 0; t < N; ++t) {
            int i1 = rnd.next(0, Xn - 2);
            int i2 = rnd.next(i1 + 1, Xn - 1);
            int j1 = rnd.next(0, Yn - 2);
            int j2 = rnd.next(j1 + 1, Yn - 1);
            rects.push_back({xs[i1], xs[i2], ys[j1], ys[j2]});
        }
    }

    if (rects.empty()) {
        // Fallback (should not happen)
        rects.push_back({0, 1, 0, 1});
    }

    shuffle(rects.begin(), rects.end());

    int N = (int)rects.size();
    println(N);
    for (const auto& r : rects) {
        println(r.x1, r.x2, r.y1, r.y2);
    }

    return 0;
}
