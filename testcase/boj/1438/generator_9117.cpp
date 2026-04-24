#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose even N, small for readability
    vector<int> candN = {2, 4, 6, 8, 10, 12, 14};
    int N = rnd.any(candN);

    int pattern = rnd.next(0, 5);

    vector<pair<int,int>> pts;
    set<long long> used;

    auto addPoint = [&](int x, int y) -> bool {
        if (x < 0 || x > 10000 || y < 0 || y > 10000) return false;
        long long key = (long long)x * 100001 + y;
        if (used.insert(key).second) {
            pts.push_back({x, y});
            return true;
        }
        return false;
    };

    if (pattern == 0) {
        // Pattern 0: half points near (0,0), half near (10000,10000)
        int half = N / 2;
        while ((int)pts.size() < N) {
            int x, y;
            if ((int)pts.size() < half) {
                x = rnd.next(0, 5);
                y = rnd.next(0, 5);
            } else {
                x = rnd.next(9995, 10000);
                y = rnd.next(9995, 10000);
            }
            addPoint(x, y);
        }
    } else if (pattern == 1) {
        // Pattern 1: small grid plus some random around it
        int gx = rnd.next(2, 4);
        int gy = rnd.next(2, 4);
        int baseX = rnd.next(0, 10);
        int baseY = rnd.next(0, 10);
        vector<pair<int,int>> all;
        for (int i = 0; i < gx; ++i)
            for (int j = 0; j < gy; ++j)
                all.push_back({baseX + i, baseY + j});
        shuffle(all.begin(), all.end());
        int idx = 0;
        while ((int)pts.size() < N && idx < (int)all.size()) {
            addPoint(all[idx].first, all[idx].second);
            ++idx;
        }
        // Fill remaining near the grid
        int xl = max(0, baseX - 2);
        int xr = min(10000, baseX + gx + 2);
        int yl = max(0, baseY - 2);
        int yr = min(10000, baseY + gy + 2);
        while ((int)pts.size() < N) {
            int x = rnd.next(xl, xr);
            int y = rnd.next(yl, yr);
            addPoint(x, y);
        }
    } else if (pattern == 2) {
        // Pattern 2: cross shape (one vertical and one horizontal line)
        int baseX = rnd.next(0, 20);
        int baseY = rnd.next(0, 20);
        addPoint(baseX, baseY); // center
        // Extend vertically upwards
        for (int d = 1; (int)pts.size() < N && baseY + d <= 10000; ++d)
            addPoint(baseX, baseY + d);
        // Extend horizontally to the right
        for (int d = 1; (int)pts.size() < N && baseX + d <= 10000; ++d)
            addPoint(baseX + d, baseY);
        // If still not enough (unlikely), fill randomly
        while ((int)pts.size() < N) {
            int x = rnd.next(0, 50);
            int y = rnd.next(0, 50);
            addPoint(x, y);
        }
    } else if (pattern == 3) {
        // Pattern 3: all points on same horizontal line
        int baseX = rnd.next(0, 20);
        int baseY = rnd.next(0, 20);
        int i = 0;
        while ((int)pts.size() < N) {
            int x = baseX + i * 2;
            int y = baseY;
            if (x > 10000) break;
            addPoint(x, y);
            ++i;
        }
        while ((int)pts.size() < N) {
            int x = rnd.next(0, 10000);
            int y = baseY;
            addPoint(x, y);
        }
    } else if (pattern == 4) {
        // Pattern 4: two separated clusters
        int cx1 = rnd.next(0, 20);
        int cy1 = rnd.next(0, 20);
        int cx2 = rnd.next(30, 50);
        int cy2 = rnd.next(30, 50);
        int c1 = N / 2;
        int c2 = N - c1;
        int got1 = 0, got2 = 0;
        while (got1 < c1) {
            int dx = rnd.next(-2, 2);
            int dy = rnd.next(-2, 2);
            int x = cx1 + dx;
            int y = cy1 + dy;
            if (addPoint(x, y)) ++got1;
        }
        while (got2 < c2) {
            int dx = rnd.next(-2, 2);
            int dy = rnd.next(-2, 2);
            int x = cx2 + dx;
            int y = cy2 + dy;
            if (addPoint(x, y)) ++got2;
        }
    } else if (pattern == 5) {
        // Pattern 5: many points on rectangle border, some inside
        int x1 = rnd.next(0, 20);
        int y1 = rnd.next(0, 20);
        int w = rnd.next(4, 8);
        int h = rnd.next(4, 8);
        int x2 = min(10000, x1 + w);
        int y2 = min(10000, y1 + h);
        // Ensure at least one interior point, if possible
        if (x2 - x1 >= 2 && y2 - y1 >= 2) {
            addPoint(x1 + 1, y1 + 1);
        }
        // Edges: bottom and top
        for (int x = x1; x <= x2 && (int)pts.size() < N; ++x)
            addPoint(x, y1);
        for (int x = x1; x <= x2 && (int)pts.size() < N; ++x)
            addPoint(x, y2);
        // Left and right vertical edges (excluding corners already covered)
        for (int y = y1 + 1; y <= y2 - 1 && (int)pts.size() < N; ++y)
            addPoint(x1, y);
        for (int y = y1 + 1; y <= y2 - 1 && (int)pts.size() < N; ++y)
            addPoint(x2, y);
        // More interior points if space
        for (int x = x1 + 1; x <= x2 - 1 && (int)pts.size() < N; ++x)
            for (int y = y1 + 1; y <= y2 - 1 && (int)pts.size() < N; ++y)
                addPoint(x, y);
    }

    // Final safety: fill up to N with completely random distinct points
    while ((int)pts.size() < N) {
        int x = rnd.next(0, 10000);
        int y = rnd.next(0, 10000);
        addPoint(x, y);
    }

    shuffle(pts.begin(), pts.end());

    println((int)pts.size());
    for (auto &p : pts)
        println(p.first, p.second);

    return 0;
}
