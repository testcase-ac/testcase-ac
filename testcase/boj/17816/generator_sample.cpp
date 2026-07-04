#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

const int MIN_COORD = -1000;
const int MAX_COORD = 1000;

Point randomPoint(int lo = -20, int hi = 20) {
    return {rnd.next(lo, hi), rnd.next(lo, hi)};
}

void addPoint(set<Point>& points, int x, int y) {
    if (MIN_COORD <= x && x <= MAX_COORD && MIN_COORD <= y && y <= MAX_COORD) {
        points.insert({x, y});
    }
}

void fillRandom(set<Point>& points, int targetSize, int lo = -20, int hi = 20) {
    while ((int)points.size() < targetSize) {
        points.insert(randomPoint(lo, hi));
    }
}

vector<Point> shuffledPoints(const set<Point>& points) {
    vector<Point> result(points.begin(), points.end());
    shuffle(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    set<Point> points;

    if (mode == 0) {
        int n = rnd.next(1, 35);
        fillRandom(points, n, -30, 30);
    } else if (mode == 1) {
        int baseSize = rnd.next(1, 18);
        int dx = 0;
        int dy = 0;
        while (dx == 0 && dy == 0) {
            dx = rnd.next(-8, 8);
            dy = rnd.next(-8, 8);
        }

        vector<Point> base;
        set<Point> usedBase;
        fillRandom(usedBase, baseSize, -25, 25);
        base.assign(usedBase.begin(), usedBase.end());

        for (auto [x, y] : base) {
            addPoint(points, x, y);
            addPoint(points, x + dx, y + dy);
        }
        if (rnd.next(0, 1)) {
            fillRandom(points, rnd.next((int)points.size(), min(45, (int)points.size() + 8)), -30, 30);
        }
    } else if (mode == 2) {
        int width = rnd.next(1, 7);
        int height = rnd.next(1, 7);
        int stepX = rnd.next(1, 5);
        int stepY = rnd.next(1, 5);
        int startX = rnd.next(-30, 30);
        int startY = rnd.next(-30, 30);

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                if (rnd.next(0, 99) < 75) {
                    addPoint(points, startX + i * stepX, startY + j * stepY);
                }
            }
        }
        if (points.empty()) {
            addPoint(points, startX, startY);
        }
    } else if (mode == 3) {
        int n = rnd.next(1, 45);
        int x0 = rnd.next(-40, 40);
        int y0 = rnd.next(-40, 40);
        int dx = rnd.next(-4, 4);
        int dy = rnd.next(-4, 4);
        if (dx == 0 && dy == 0) {
            dx = 1;
        }
        for (int i = 0; i < n; ++i) {
            addPoint(points, x0 + i * dx, y0 + i * dy);
        }
    } else {
        vector<Point> corners = {
            {-1000, -1000},
            {-1000, 1000},
            {1000, -1000},
            {1000, 1000},
            {0, 0},
        };
        shuffle(corners.begin(), corners.end());
        int n = rnd.next(1, (int)corners.size());
        for (int i = 0; i < n; ++i) {
            points.insert(corners[i]);
        }
        fillRandom(points, rnd.next(n, n + 8), -10, 10);
    }

    vector<Point> output = shuffledPoints(points);
    println((int)output.size());
    for (auto [x, y] : output) {
        println(x, y);
    }

    return 0;
}
