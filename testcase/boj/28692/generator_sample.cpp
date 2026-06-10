#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

static int clampCoord(int v) {
    return max(-1000, min(1000, v));
}

static void printPoints(const vector<pair<int, int>>& points) {
    println((int)points.size());
    for (auto [x, y] : points) {
        println(x, y);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    vector<pair<int, int>> points;

    if (mode == 0) {
        int n = rnd.next(2, 16);
        int x = rnd.next(-1000, 1000);
        int lo = rnd.next(-1000, 800);
        int hi = rnd.next(lo, 1000);
        for (int i = 0; i < n; ++i) {
            points.push_back({x, rnd.next(lo, hi)});
        }
    } else if (mode == 1) {
        int x1 = rnd.next(-1000, 999);
        int x2 = rnd.next(x1 + 1, 1000);
        if (rnd.next(0, 1)) {
            swap(x1, x2);
        }
        points.push_back({x1, rnd.next(-1000, 1000)});
        points.push_back({x2, rnd.next(-1000, 1000)});
    } else if (mode == 2) {
        int n = rnd.next(3, 18);
        int baseX = rnd.next(-20, 20);
        int outlierX = baseX;
        while (outlierX == baseX) {
            outlierX = rnd.next(-1000, 1000);
        }
        for (int i = 0; i + 1 < n; ++i) {
            points.push_back({baseX, rnd.next(-1000, 1000)});
        }
        points.push_back({outlierX, rnd.next(-1000, 1000)});
        shuffle(points.begin(), points.end());
    } else if (mode == 3) {
        int n = rnd.next(3, 20);
        int a = rnd.next(-10, 10);
        int b = rnd.next(-200, 200);
        int minX = max(-1000, (-1000 - b + (a > 0 ? a - 1 : 0)) / (a == 0 ? 1 : a));
        int maxX = min(1000, (1000 - b - (a > 0 ? 0 : a + 1)) / (a == 0 ? 1 : a));
        if (a < 0) {
            swap(minX, maxX);
        }
        minX = max(minX, -1000);
        maxX = min(maxX, 1000);
        if (minX > maxX) {
            minX = -30;
            maxX = 30;
            a = rnd.next(-5, 5);
            b = rnd.next(-100, 100);
        }
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(minX, maxX);
            points.push_back({x, a * x + b});
        }
    } else if (mode == 4) {
        int n = rnd.next(4, 22);
        int a = rnd.next(-8, 8);
        int b = rnd.next(-100, 100);
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(-100, 100);
            int noise = rnd.next(-20, 20);
            points.push_back({x, clampCoord(a * x + b + noise)});
        }
    } else if (mode == 5) {
        int n = rnd.next(4, 20);
        vector<pair<int, int>> pool = {
            {-1000, -1000}, {-1000, 1000}, {1000, -1000}, {1000, 1000},
            {-1000, 0}, {1000, 0}, {0, -1000}, {0, 1000}, {0, 0}
        };
        for (int i = 0; i < n; ++i) {
            points.push_back(rnd.any(pool));
        }
    } else {
        int n = rnd.next(6, 24);
        int clusters = rnd.next(2, 4);
        vector<pair<int, int>> centers;
        for (int i = 0; i < clusters; ++i) {
            centers.push_back({rnd.next(-900, 900), rnd.next(-900, 900)});
        }
        for (int i = 0; i < n; ++i) {
            auto [cx, cy] = rnd.any(centers);
            points.push_back({clampCoord(cx + rnd.next(-30, 30)),
                              clampCoord(cy + rnd.next(-30, 30))});
        }
    }

    printPoints(points);
    return 0;
}
