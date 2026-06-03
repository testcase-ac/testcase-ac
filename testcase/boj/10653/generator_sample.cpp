#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

int clampCoord(int value) {
    return max(-1000, min(1000, value));
}

Point randomPoint(int lo = -1000, int hi = 1000) {
    return {rnd.next(lo, hi), rnd.next(lo, hi)};
}

int chooseK(int n) {
    int mode = rnd.next(5);
    if (mode == 0) return 0;
    if (mode == 1) return n - 1;
    if (mode == 2) return rnd.next(max(0, n - 4), n - 1);
    return rnd.next(0, n - 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode <= 1) {
        n = rnd.next(3, 14);
    } else if (mode == 2) {
        n = rnd.next(8, 30);
    } else {
        n = rnd.next(3, 20);
    }

    vector<Point> points;
    points.reserve(n);

    if (mode == 0) {
        int x = rnd.next(-30, 30);
        int y = rnd.next(-30, 30);
        int dx = rnd.next(-8, 8);
        int dy = rnd.next(-8, 8);
        if (dx == 0 && dy == 0) dx = 1;
        for (int i = 0; i < n; ++i) {
            points.push_back({
                clampCoord(x + i * dx + rnd.next(-2, 2)),
                clampCoord(y + i * dy + rnd.next(-2, 2)),
            });
        }
    } else if (mode == 1) {
        int x = rnd.next(-40, 40);
        int y = rnd.next(-40, 40);
        for (int i = 0; i < n; ++i) {
            int step = i % 2 == 0 ? rnd.next(8, 30) : -rnd.next(8, 30);
            x = clampCoord(x + step);
            y = clampCoord(y + rnd.next(-12, 12));
            points.push_back({x, y});
        }
    } else if (mode == 2) {
        vector<Point> pool;
        int poolSize = rnd.next(2, 5);
        for (int i = 0; i < poolSize; ++i) pool.push_back(randomPoint(-25, 25));
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 75) {
                points.push_back(rnd.any(pool));
            } else {
                points.push_back(randomPoint(-25, 25));
            }
        }
    } else if (mode == 3) {
        vector<Point> corners = {
            {-1000, -1000},
            {-1000, 1000},
            {1000, -1000},
            {1000, 1000},
        };
        for (int i = 0; i < n; ++i) {
            Point p = rnd.any(corners);
            p.first = clampCoord(p.first + rnd.next(-5, 5));
            p.second = clampCoord(p.second + rnd.next(-5, 5));
            points.push_back(p);
        }
    } else {
        Point center = randomPoint(-900, 900);
        int radius = rnd.next(0, 80);
        for (int i = 0; i < n; ++i) {
            points.push_back({
                clampCoord(center.first + rnd.next(-radius, radius)),
                clampCoord(center.second + rnd.next(-radius, radius)),
            });
        }
    }

    println(n, chooseK(n));
    for (const Point& p : points) println(p.first, p.second);

    return 0;
}
