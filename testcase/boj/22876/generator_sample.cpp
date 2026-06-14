#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Swallow {
    int x;
    int y;
    int v;
};

int randomCoord(bool boundaryBiased) {
    if (boundaryBiased && rnd.next(100) < 35) {
        vector<int> coords = {0, 1, 2, 999998, 999999, 1000000};
        return rnd.any(coords);
    }
    return rnd.next(0, 1000000);
}

int randomValue(bool highBiased) {
    if (highBiased && rnd.next(100) < 45) {
        return rnd.next(6500, 7000);
    }
    if (rnd.next(100) < 25) {
        return rnd.next(1, 20);
    }
    return rnd.next(1, 7000);
}

void addPoint(vector<Swallow>& points, set<pair<int, int>>& used, int x, int y, int v) {
    x = max(0, min(1000000, x));
    y = max(0, min(1000000, y));
    if (used.insert({x, y}).second) {
        points.push_back({x, y, v});
    }
}

void addRandomPoint(vector<Swallow>& points, set<pair<int, int>>& used, bool boundaryBiased, bool highBiased) {
    while (true) {
        int x = randomCoord(boundaryBiased);
        int y = randomCoord(boundaryBiased);
        if (!used.count({x, y})) {
            addPoint(points, used, x, y, randomValue(highBiased));
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<Swallow> points;
    set<pair<int, int>> used;

    if (mode == 0) {
        addRandomPoint(points, used, true, true);
    } else if (mode == 1) {
        int rows = rnd.next(2, 5);
        int cols = rnd.next(2, 5);
        vector<int> xs, ys;
        while ((int)xs.size() < cols) {
            int x = randomCoord(true);
            if (find(xs.begin(), xs.end(), x) == xs.end()) xs.push_back(x);
        }
        while ((int)ys.size() < rows) {
            int y = randomCoord(true);
            if (find(ys.begin(), ys.end(), y) == ys.end()) ys.push_back(y);
        }
        for (int x : xs) {
            for (int y : ys) {
                if (rnd.next(100) < 80) {
                    addPoint(points, used, x, y, randomValue(true));
                }
            }
        }
    } else if (mode == 2) {
        int heavyX = randomCoord(true);
        int heavyY = randomCoord(true);
        int n = rnd.next(8, 35);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 45) {
                addRandomPoint(points, used, true, false);
            } else if (rnd.next(2) == 0) {
                addPoint(points, used, heavyX, randomCoord(false), randomValue(i % 3 == 0));
            } else {
                addPoint(points, used, randomCoord(false), heavyY, randomValue(i % 3 == 0));
            }
        }
    } else if (mode == 3) {
        int baseX = rnd.next(0, 999950);
        int baseY = rnd.next(0, 999950);
        int n = rnd.next(10, 45);
        for (int i = 0; i < n; ++i) {
            int x = baseX + rnd.next(0, 50);
            int y = baseY + rnd.next(0, 50);
            addPoint(points, used, x, y, randomValue(true));
        }
    } else if (mode == 4) {
        int n = rnd.next(25, 80);
        vector<int> xs, ys;
        while ((int)xs.size() < 6) {
            int x = randomCoord(false);
            if (find(xs.begin(), xs.end(), x) == xs.end()) xs.push_back(x);
        }
        while ((int)ys.size() < 6) {
            int y = randomCoord(false);
            if (find(ys.begin(), ys.end(), y) == ys.end()) ys.push_back(y);
        }
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(100) < 70 ? rnd.any(xs) : randomCoord(true);
            int y = rnd.next(100) < 70 ? rnd.any(ys) : randomCoord(true);
            addPoint(points, used, x, y, randomValue(true));
        }
    } else {
        int n = rnd.next(2, 70);
        bool boundaryBiased = rnd.next(2);
        bool highBiased = rnd.next(2);
        for (int i = 0; i < n; ++i) {
            addRandomPoint(points, used, boundaryBiased, highBiased);
        }
    }

    while (points.empty()) {
        addRandomPoint(points, used, true, true);
    }

    shuffle(points.begin(), points.end());
    println((int)points.size());
    for (const Swallow& point : points) {
        println(point.x, point.y, point.v);
    }

    return 0;
}
