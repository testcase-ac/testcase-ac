#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const int MIN_COORD = -10000;
const int MAX_COORD = 10000;

using Point = pair<int, int>;

bool inside(int x, int y) {
    return MIN_COORD <= x && x <= MAX_COORD && MIN_COORD <= y && y <= MAX_COORD;
}

void addPoint(vector<Point>& points, set<Point>& used, int x, int y) {
    if (inside(x, y) && used.insert({x, y}).second) {
        points.push_back({x, y});
    }
}

void addRandomPoint(vector<Point>& points, set<Point>& used) {
    while (true) {
        int x = rnd.next(MIN_COORD, MAX_COORD);
        int y = rnd.next(MIN_COORD, MAX_COORD);
        if (used.insert({x, y}).second) {
            points.push_back({x, y});
            return;
        }
    }
}

void addAxisSquare(vector<Point>& points, set<Point>& used) {
    int side = rnd.next(1, 120);
    int x = rnd.next(MIN_COORD, MAX_COORD - side);
    int y = rnd.next(MIN_COORD, MAX_COORD - side);

    addPoint(points, used, x, y);
    addPoint(points, used, x + side, y);
    addPoint(points, used, x, y + side);
    addPoint(points, used, x + side, y + side);
}

void addRotatedSquare(vector<Point>& points, set<Point>& used) {
    for (int tries = 0; tries < 200; ++tries) {
        int dx = rnd.next(-60, 60);
        int dy = rnd.next(-60, 60);
        if (dx == 0 && dy == 0) {
            continue;
        }

        int minX = min(0, min(dx, min(-dy, dx - dy)));
        int maxX = max(0, max(dx, max(-dy, dx - dy)));
        int minY = min(0, min(dy, min(dx, dx + dy)));
        int maxY = max(0, max(dy, max(dx, dx + dy)));

        int x = rnd.next(MIN_COORD - minX, MAX_COORD - maxX);
        int y = rnd.next(MIN_COORD - minY, MAX_COORD - maxY);

        addPoint(points, used, x, y);
        addPoint(points, used, x + dx, y + dy);
        addPoint(points, used, x - dy, y + dx);
        addPoint(points, used, x + dx - dy, y + dy + dx);
        return;
    }

    addAxisSquare(points, used);
}

void addGridNoise(vector<Point>& points, set<Point>& used, int target) {
    int width = rnd.next(2, 8);
    int height = rnd.next(2, 8);
    int step = rnd.next(1, 40);
    int x0 = rnd.next(MIN_COORD, MAX_COORD - width * step);
    int y0 = rnd.next(MIN_COORD, MAX_COORD - height * step);

    vector<Point> candidates;
    for (int i = 0; i <= width; ++i) {
        for (int j = 0; j <= height; ++j) {
            candidates.push_back({x0 + i * step, y0 + j * step});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    for (Point p : candidates) {
        if ((int)points.size() >= target) {
            break;
        }
        addPoint(points, used, p.first, p.second);
    }
}

vector<Point> makeCase() {
    int target = rnd.next(4, 80);
    int mode = rnd.next(0, 5);

    vector<Point> points;
    set<Point> used;

    if (mode == 0) {
        addAxisSquare(points, used);
    } else if (mode == 1) {
        addRotatedSquare(points, used);
    } else if (mode == 2) {
        addAxisSquare(points, used);
        addRotatedSquare(points, used);
    } else if (mode == 3) {
        addPoint(points, used, MIN_COORD, MIN_COORD);
        addPoint(points, used, MIN_COORD + 1, MIN_COORD);
        addPoint(points, used, MIN_COORD, MIN_COORD + 1);
        addPoint(points, used, MIN_COORD + 1, MIN_COORD + 1);
    } else if (mode == 4) {
        addGridNoise(points, used, target);
    }

    if (mode != 4 && rnd.next(0, 2) == 0) {
        addGridNoise(points, used, min(target, rnd.next(4, target)));
    }

    while ((int)points.size() < target) {
        addRandomPoint(points, used);
    }

    shuffle(points.begin(), points.end());
    return points;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        vector<Point> points = makeCase();
        println((int)points.size());
        for (Point p : points) {
            println(p.first, p.second);
        }
    }

    return 0;
}
