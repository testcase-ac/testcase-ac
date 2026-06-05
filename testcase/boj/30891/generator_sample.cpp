#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

bool insideBoard(int x, int y) {
    return -100 <= x && x <= 100 && -100 <= y && y <= 100;
}

void addPoint(vector<Point>& points, set<Point>& used, int x, int y) {
    if (insideBoard(x, y) && used.insert({x, y}).second) {
        points.push_back({x, y});
    }
}

void addRandomPoint(vector<Point>& points, set<Point>& used) {
    while (true) {
        int x = rnd.next(-100, 100);
        int y = rnd.next(-100, 100);
        if (used.insert({x, y}).second) {
            points.push_back({x, y});
            return;
        }
    }
}

void printCase(int r, vector<Point> points) {
    shuffle(points.begin(), points.end());
    println((int)points.size(), r);
    for (auto [x, y] : points) {
        println(x, y);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int r = 1;
    vector<Point> points;
    set<Point> used;

    if (mode == 0) {
        r = rnd.next(1, 100);
        addRandomPoint(points, used);
    } else if (mode == 1) {
        r = rnd.next(1, 8);
        int cx = rnd.next(-80, 80);
        int cy = rnd.next(-80, 80);
        int n = rnd.next(3, 18);
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, cx + rnd.next(-r, r), cy + rnd.next(-r, r));
        }
        while ((int)points.size() < n) {
            addPoint(points, used, cx + rnd.next(-r - 2, r + 2), cy + rnd.next(-r - 2, r + 2));
        }
    } else if (mode == 2) {
        r = rnd.next(2, 20);
        int cx = rnd.next(-70, 70);
        int cy = rnd.next(-70, 70);
        vector<Point> candidates = {
            {cx, cy},
            {cx + r, cy},
            {cx - r, cy},
            {cx, cy + r},
            {cx, cy - r},
            {cx + r - 1, cy + 1},
            {cx - r + 1, cy - 1},
        };
        shuffle(candidates.begin(), candidates.end());
        for (auto [x, y] : candidates) {
            addPoint(points, used, x, y);
        }
        int target = rnd.next((int)points.size(), 14);
        while ((int)points.size() < target) {
            addRandomPoint(points, used);
        }
    } else if (mode == 3) {
        r = rnd.next(2, 15);
        int separation = rnd.next(r + 1, min(100, 3 * r + 8));
        int cx1 = rnd.next(-80, 80 - separation);
        int cy1 = rnd.next(-80, 80);
        int cx2 = cx1 + separation;
        int cy2 = cy1 + rnd.next(-r, r);
        int each = rnd.next(3, 8);
        for (int i = 0; i < each; ++i) {
            addPoint(points, used, cx1 + rnd.next(-r, r), cy1 + rnd.next(-r, r));
            addPoint(points, used, cx2 + rnd.next(-r, r), cy2 + rnd.next(-r, r));
        }
        while ((int)points.size() < each * 2) {
            addRandomPoint(points, used);
        }
    } else if (mode == 4) {
        r = rnd.next(1, 35);
        int n = rnd.next(8, 25);
        while ((int)points.size() < n) {
            addRandomPoint(points, used);
        }
    } else {
        r = rnd.next(1, 12);
        int step = rnd.next(1, max(1, r));
        int width = rnd.next(2, 5);
        int height = rnd.next(2, 5);
        int baseX = rnd.next(-100, 100 - step * (width - 1));
        int baseY = rnd.next(-100, 100 - step * (height - 1));
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                if (rnd.next(0, 99) < 85) {
                    addPoint(points, used, baseX + i * step, baseY + j * step);
                }
            }
        }
        if (points.empty()) {
            addPoint(points, used, baseX, baseY);
        }
    }

    printCase(r, points);
    return 0;
}
