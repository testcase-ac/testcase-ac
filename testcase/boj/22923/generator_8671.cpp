#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<tuple<int,int,int>> circles;
    vector<array<int,4>> rects;

    int style = rnd.next(0, 5);

    if (style == 0) {
        // General small random case
        int nTarget = rnd.next(1, 8);
        int qTarget = rnd.next(1, 8);
        int lim = rnd.any(vector<int>{5, 10, 20});

        for (int i = 0; i < nTarget; ++i) {
            int x = rnd.next(-lim, lim);
            int y = rnd.next(-lim, lim);
            int r = rnd.next(1, lim);
            circles.emplace_back(x, y, r);
        }
        for (int i = 0; i < qTarget; ++i) {
            int x = rnd.next(-lim, lim);
            int y = rnd.next(-lim, lim);
            int w = rnd.next(1, lim);
            int h = rnd.next(1, lim);
            rects.push_back({x, y, w, h});
        }
    } else if (style == 1) {
        // Many duplicate/similar circles around one center
        int nTarget = rnd.next(2, 8);
        int qTarget = rnd.next(3, 8);

        int cx = rnd.next(-20, 20);
        int cy = rnd.next(-20, 20);
        int baseR = rnd.next(3, 20);

        // Mostly identical circles
        for (int i = 0; i < nTarget - 1; ++i) {
            circles.emplace_back(cx, cy, baseR);
        }
        // One circle different and far
        int dx = rnd.next(40, 80);
        int dy = rnd.next(40, 80);
        int r2 = rnd.next(1, 25);
        circles.emplace_back(cx + dx, cy + dy, r2);

        // Rectangles: one inside, one exactly bounding, one far away, rest random
        // Inside-ish rectangle
        int w1 = baseR;
        int h1 = baseR;
        int x1 = cx - w1 / 2;
        int y1 = cy - h1 / 2;
        rects.push_back({x1, y1, w1, h1});

        // Bounding square of main circle
        int x2 = cx - baseR;
        int y2 = cy - baseR;
        int w2 = 2 * baseR;
        int h2 = 2 * baseR;
        rects.push_back({x2, y2, w2, h2});

        // Far away rectangle with no overlap
        int fx = cx + 5 * baseR + 50;
        int fy = cy + 5 * baseR + 50;
        int fw = baseR;
        int fh = baseR;
        rects.push_back({fx, fy, fw, fh});

        // Extra random rectangles
        while ((int)rects.size() < qTarget) {
            int rx = rnd.next(cx - 3 * baseR, cx + 3 * baseR);
            int ry = rnd.next(cy - 3 * baseR, cy + 3 * baseR);
            int rw = rnd.next(1, 2 * baseR + 5);
            int rh = rnd.next(1, 2 * baseR + 5);
            rects.push_back({rx, ry, rw, rh});
        }
    } else if (style == 2) {
        // Grid of circles
        int grid = rnd.next(0, 1) == 0 ? 2 : 3;
        int spacing = rnd.next(5, 15);
        int baseX = rnd.next(-10, 10);
        int baseY = rnd.next(-10, 10);

        for (int i = 0; i < grid; ++i) {
            for (int j = 0; j < grid; ++j) {
                if ((int)circles.size() >= 8) break;
                int x = baseX + i * spacing;
                int y = baseY + j * spacing;
                int maxR = max(1, spacing - 1);
                int r = rnd.next(1, maxR);
                circles.emplace_back(x, y, r);
            }
        }

        int qTarget = rnd.next(3, 8);

        int minX = baseX;
        int minY = baseY;
        int maxX = baseX + (grid - 1) * spacing;
        int maxY = baseY + (grid - 1) * spacing;

        // Full bounding rectangle around grid
        int pad = spacing;
        int bx = minX - pad;
        int by = minY - pad;
        int bw = (maxX - minX) + 2 * pad;
        int bh = (maxY - minY) + 2 * pad;
        rects.push_back({bx, by, bw, bh});

        // One horizontal strip
        int row = rnd.next(0, grid - 1);
        int hx = minX - 1;
        int hy = baseY + row * spacing - 1;
        int hw = (maxX - minX) + 2;
        int hh = 3;
        rects.push_back({hx, hy, hw, hh});

        // One vertical strip
        int col = rnd.next(0, grid - 1);
        int vx = baseX + col * spacing - 1;
        int vy = minY - 1;
        int vw = 3;
        int vh = (maxY - minY) + 2;
        rects.push_back({vx, vy, vw, vh});

        // Additional random rectangles around the grid
        while ((int)rects.size() < qTarget) {
            int rx = rnd.next(minX - 2 * spacing, maxX + 2 * spacing);
            int ry = rnd.next(minY - 2 * spacing, maxY + 2 * spacing);
            int rw = rnd.next(1, 2 * spacing * grid);
            int rh = rnd.next(1, 2 * spacing * grid);
            rects.push_back({rx, ry, rw, rh});
        }
    } else if (style == 3) {
        // Rectangle with circles tangent to sides
        int w = rnd.next(6, 20);
        int h = rnd.next(6, 20);
        int baseX = rnd.next(-10, 10);
        int baseY = rnd.next(-10, 10);

        int r = max(1, min(w, h) / 2);

        // Helper to clamp a value
        auto clamp = [](int v, int lo, int hi) {
            if (v < lo) return lo;
            if (v > hi) return hi;
            return v;
        };

        // Tangent to left
        {
            int ylo = baseY + r;
            int yhi = baseY + h - r;
            if (ylo > yhi) { ylo = yhi = baseY + h / 2; }
            int cy = rnd.next(ylo, yhi);
            int cx = baseX + r;
            circles.emplace_back(cx, cy, r);
        }
        // Tangent to right
        if ((int)circles.size() < 8) {
            int ylo = baseY + r;
            int yhi = baseY + h - r;
            if (ylo > yhi) { ylo = yhi = baseY + h / 2; }
            int cy = rnd.next(ylo, yhi);
            int cx = baseX + w - r;
            circles.emplace_back(cx, cy, r);
        }
        // Tangent to bottom
        if ((int)circles.size() < 8) {
            int xlo = baseX + r;
            int xhi = baseX + w - r;
            if (xlo > xhi) { xlo = xhi = baseX + w / 2; }
            int cx = rnd.next(xlo, xhi);
            int cy = baseY + r;
            circles.emplace_back(cx, cy, r);
        }
        // Tangent to top
        if ((int)circles.size() < 8) {
            int xlo = baseX + r;
            int xhi = baseX + w - r;
            if (xlo > xhi) { xlo = xhi = baseX + w / 2; }
            int cx = rnd.next(xlo, xhi);
            int cy = baseY + h - r;
            circles.emplace_back(cx, cy, r);
        }
        // One circle fully inside
        if ((int)circles.size() < 8) {
            int cx = clamp(baseX + w / 2, baseX + r, baseX + w - r);
            int cy = clamp(baseY + h / 2, baseY + r, baseY + h - r);
            circles.emplace_back(cx, cy, r / 2 + 1);
        }
        // One circle far outside
        if ((int)circles.size() < 8) {
            int cx = baseX + 5 * w;
            int cy = baseY + 5 * h;
            circles.emplace_back(cx, cy, r);
        }

        int qTarget = rnd.next(2, 6);

        // Base rectangle
        rects.push_back({baseX, baseY, w, h});

        // Slightly shifted overlapping rectangle
        int shift = rnd.next(-r, r);
        int x2 = baseX + shift;
        int y2 = baseY - shift;
        rects.push_back({x2, y2, w, h});

        // Far away rectangle
        if ((int)rects.size() < qTarget) {
            int x3 = baseX + 6 * w;
            int y3 = baseY + 6 * h;
            rects.push_back({x3, y3, w, h});
        }

        // Additional nearby random rectangles
        while ((int)rects.size() < qTarget) {
            int rx = rnd.next(baseX - 2 * w, baseX + 2 * w);
            int ry = rnd.next(baseY - 2 * h, baseY + 2 * h);
            int rw = rnd.next(1, 2 * max(w, h));
            int rh = rnd.next(1, 2 * max(w, h));
            rects.push_back({rx, ry, rw, rh});
        }
    } else if (style == 4) {
        // Extreme coordinates and large radii
        int nTarget = rnd.next(1, 3);
        vector<int> coordChoices = {-1000000, -999000, 0, 999000, 1000000};

        for (int i = 0; i < nTarget; ++i) {
            int cx = rnd.any(coordChoices);
            int cy = rnd.any(coordChoices);
            int r = rnd.next(500000, 1000000);
            circles.emplace_back(cx, cy, r);
        }

        int qTarget = rnd.next(1, 4);

        // One huge rectangle
        int x1 = rnd.any(coordChoices);
        int y1 = rnd.any(coordChoices);
        int w1 = rnd.next(500000, 1000000);
        int h1 = rnd.next(500000, 1000000);
        rects.push_back({x1, y1, w1, h1});

        // Possibly one tiny rectangle near origin
        if ((int)rects.size() < qTarget) {
            int x2 = rnd.next(-5, 5);
            int y2 = rnd.next(-5, 5);
            int w2 = rnd.next(1, 10);
            int h2 = rnd.next(1, 10);
            rects.push_back({x2, y2, w2, h2});
        }

        while ((int)rects.size() < qTarget) {
            int x = rnd.any(coordChoices);
            int y = rnd.any(coordChoices);
            int w = rnd.next(1, 1000000);
            int h = rnd.next(1, 1000000);
            rects.push_back({x, y, w, h});
        }
    } else if (style == 5) {
        // Sparse non-overlapping-ish circles along a diagonal
        int nTarget = rnd.next(2, 6);
        int spacing = rnd.next(10, 30);
        int baseX = rnd.next(-50, 0);
        int baseY = rnd.next(-50, 0);
        int rBase = rnd.next(1, 5);

        for (int i = 0; i < nTarget; ++i) {
            int cx = baseX + i * spacing;
            int cy = baseY + i * spacing;
            circles.emplace_back(cx, cy, rBase);
        }

        int qTarget = rnd.next(3, 8);

        int minX = baseX;
        int minY = baseY;
        int maxX = baseX + (nTarget - 1) * spacing;
        int maxY = baseY + (nTarget - 1) * spacing;

        // Big rectangle covering all circles
        int bigX = minX - rBase - 2;
        int bigY = minY - rBase - 2;
        int bigW = (maxX - minX) + 2 * (rBase + 2);
        int bigH = (maxY - minY) + 2 * (rBase + 2);
        rects.push_back({bigX, bigY, bigW, bigH});

        // Rectangles each around a single circle
        for (int i = 0; i < nTarget && (int)rects.size() < qTarget; ++i) {
            auto [cx, cy, r] = circles[i];
            int x = cx - r;
            int y = cy - r;
            int w = 2 * r;
            int h = 2 * r;
            rects.push_back({x, y, w, h});
        }

        // Some far-away rectangles with no coverage
        while ((int)rects.size() < qTarget) {
            int x = maxX + rnd.next(20, 60);
            int y = maxY + rnd.next(20, 60);
            int w = rnd.next(1, 20);
            int h = rnd.next(1, 20);
            rects.push_back({x, y, w, h});
        }
    }

    int n = (int)circles.size();
    int q = (int)rects.size();

    println(n, q);
    for (auto &c : circles) {
        int x, y, r;
        tie(x, y, r) = c;
        println(x, y, r);
    }
    for (auto &re : rects) {
        println(re[0], re[1], re[2], re[3]);
    }

    return 0;
}
