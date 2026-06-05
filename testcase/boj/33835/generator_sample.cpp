#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

void addPoint(vector<Point>& points, set<Point>& used, long long x, long long y) {
    if (used.insert({x, y}).second) {
        points.push_back({x, y});
    }
}

void addRandomNear(vector<Point>& points, set<Point>& used, int targetSize,
                   long long baseX, long long baseY, int radius) {
    while ((int)points.size() < targetSize) {
        long long x = baseX + rnd.next(-radius, radius);
        long long y = baseY + rnd.next(-radius, radius);
        addPoint(points, used, x, y);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 15);

    vector<Point> points;
    set<Point> used;

    if (mode == 0) {
        n = rnd.next(2, 4);
        addRandomNear(points, used, n, 0, 0, 3);
    } else if (mode == 1) {
        long long start = rnd.next(-20, 20);
        long long step = rnd.next(1, 7);
        long long y = rnd.next(-5, 5);
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, start + step * i, y);
        }
    } else if (mode == 2) {
        long long x = rnd.next(-10, 10);
        long long start = rnd.next(-30, 30);
        long long step = rnd.next(1, 9);
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, x, start + step * i);
        }
    } else if (mode == 3) {
        vector<Point> candidates = {
            {-1000000000LL, -1000000000LL},
            {-1000000000LL, 1000000000LL},
            {1000000000LL, -1000000000LL},
            {1000000000LL, 1000000000LL},
            {0, 0},
            {-1, 1},
            {1, -1},
            {rnd.next(-1000, 1000), rnd.next(-1000, 1000)}
        };
        shuffle(candidates.begin(), candidates.end());
        n = rnd.next(2, (int)candidates.size());
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, candidates[i].first, candidates[i].second);
        }
        addRandomNear(points, used, n, 0, 0, 5);
    } else if (mode == 4) {
        int side = rnd.next(2, 4);
        long long dx = rnd.next(1, 5);
        long long dy = rnd.next(1, 5);
        long long ox = rnd.next(-20, 20);
        long long oy = rnd.next(-20, 20);
        vector<Point> grid;
        for (int i = 0; i < side; ++i) {
            for (int j = 0; j < side; ++j) {
                grid.push_back({ox + dx * i, oy + dy * j});
            }
        }
        shuffle(grid.begin(), grid.end());
        n = rnd.next(2, (int)grid.size());
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, grid[i].first, grid[i].second);
        }
    } else {
        long long x = rnd.next(-50, 50);
        long long y = rnd.next(-50, 50);
        for (int i = 0; i < n; ++i) {
            x += rnd.next(-8, 8);
            y += rnd.next(-8, 8);
            addPoint(points, used, x, y);
        }
        addRandomNear(points, used, n, x, y, 10);
    }

    if (rnd.next(0, 1)) {
        shuffle(points.begin(), points.end());
    }

    println((int)points.size());
    for (const auto& p : points) {
        println(p.first, p.second);
    }

    return 0;
}
