#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

const long long MIN_COORD = -1000000000LL;
const long long MAX_COORD = 1000000000LL;

void addPoint(vector<Point>& points, set<Point>& used, long long x, long long y) {
    x = max(MIN_COORD, min(MAX_COORD, x));
    y = max(MIN_COORD, min(MAX_COORD, y));
    if (used.insert({x, y}).second) {
        points.push_back({x, y});
    }
}

long long smallCoord() {
    return rnd.next(-30, 30);
}

void fillRandom(vector<Point>& points, set<Point>& used, int n, long long lo, long long hi) {
    while ((int)points.size() < n) {
        addPoint(points, used, rnd.next(lo, hi), rnd.next(lo, hi));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 24);
    vector<Point> points;
    set<Point> used;

    if (mode == 0) {
        long long cx = rnd.next(-1000, 1000);
        long long cy = rnd.next(-1000, 1000);
        while ((int)points.size() < n) {
            addPoint(points, used, cx + rnd.next(-6, 6), cy + rnd.next(-6, 6));
        }
    } else if (mode == 1) {
        long long y = smallCoord();
        long long step = rnd.next(1, 5);
        long long start = -step * n / 2;
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, start + step * i, y);
        }
    } else if (mode == 2) {
        int rows = rnd.next(2, 5);
        int cols = rnd.next(2, 5);
        n = rnd.next(2, rows * cols);
        vector<Point> grid;
        long long sx = rnd.next(1, 4);
        long long sy = rnd.next(1, 4);
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                grid.push_back({c * sx, r * sy});
            }
        }
        shuffle(grid.begin(), grid.end());
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, grid[i].first, grid[i].second);
        }
    } else if (mode == 3) {
        vector<Point> anchors = {
            {MIN_COORD, MIN_COORD},
            {MIN_COORD, MAX_COORD},
            {MAX_COORD, MIN_COORD},
            {MAX_COORD, MAX_COORD},
            {0, 0},
            {1, 0},
            {0, 1},
        };
        shuffle(anchors.begin(), anchors.end());
        for (Point p : anchors) {
            if ((int)points.size() == n) break;
            addPoint(points, used, p.first, p.second);
        }
        fillRandom(points, used, n, -1000000, 1000000);
    } else {
        long long x = smallCoord();
        long long y = smallCoord();
        addPoint(points, used, x, y);
        while ((int)points.size() < n) {
            long long dx = rnd.next(-20, 20);
            long long dy = rnd.next(-20, 20);
            if (dx == 0 && dy == 0) continue;
            x += dx;
            y += dy;
            addPoint(points, used, x, y);
        }
    }

    shuffle(points.begin(), points.end());
    println((int)points.size());
    for (Point p : points) {
        println(p.first, p.second);
    }

    return 0;
}
