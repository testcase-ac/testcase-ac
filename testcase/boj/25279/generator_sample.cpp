#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

const int MIN_COORD = -10000;
const int MAX_COORD = 10000;

bool inside(int x, int y) {
    return MIN_COORD <= x && x <= MAX_COORD && MIN_COORD <= y && y <= MAX_COORD;
}

void addPoint(set<Point>& points, int x, int y) {
    if (inside(x, y)) {
        points.insert({x, y});
    }
}

void addAxisSquare(set<Point>& points, int x, int y, int side) {
    addPoint(points, x, y);
    addPoint(points, x + side, y);
    addPoint(points, x, y + side);
    addPoint(points, x + side, y + side);
}

void addRotatedSquare(set<Point>& points, int cx, int cy, int dx, int dy) {
    addPoint(points, cx + dx, cy + dy);
    addPoint(points, cx - dy, cy + dx);
    addPoint(points, cx - dx, cy - dy);
    addPoint(points, cx + dy, cy - dx);
}

void fillRandom(set<Point>& points, int target, int lo, int hi) {
    while ((int)points.size() < target) {
        addPoint(points, rnd.next(lo, hi), rnd.next(lo, hi));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    set<Point> points;
    int mode = rnd.next(0, 3);
    int target = rnd.next(4, 60);

    if (mode == 0) {
        fillRandom(points, target, -25, 25);
    } else if (mode == 1) {
        int squares = rnd.next(1, 8);
        for (int i = 0; i < squares; ++i) {
            int side = rnd.next(1, 12);
            int x = rnd.next(-30, 30 - side);
            int y = rnd.next(-30, 30 - side);
            addAxisSquare(points, x, y, side);
        }
        fillRandom(points, target, -35, 35);
    } else if (mode == 2) {
        int squares = rnd.next(1, 8);
        for (int i = 0; i < squares; ++i) {
            int dx = rnd.next(-8, 8);
            int dy = rnd.next(-8, 8);
            if (dx == 0 && dy == 0) {
                dx = 1;
            }
            int cx = rnd.next(-40, 40);
            int cy = rnd.next(-40, 40);
            addRotatedSquare(points, cx, cy, dx, dy);
        }
        fillRandom(points, target, -45, 45);
    } else {
        vector<int> edges = {MIN_COORD, MIN_COORD + 1, -1, 0, 1, MAX_COORD - 1, MAX_COORD};
        int fixedX = rnd.any(edges);
        int fixedY = rnd.any(edges);
        for (int i = 0; i < target / 2; ++i) {
            addPoint(points, fixedX, rnd.next(-10000, 10000));
            addPoint(points, rnd.next(-10000, 10000), fixedY);
        }
        fillRandom(points, target, -10000, 10000);
    }

    while ((int)points.size() < 4) {
        fillRandom(points, 4, -10, 10);
    }

    vector<Point> out(points.begin(), points.end());
    shuffle(out.begin(), out.end());

    println((int)out.size());
    for (const auto& [x, y] : out) {
        println(x, y);
    }

    return 0;
}
