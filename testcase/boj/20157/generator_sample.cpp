#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

const int COORD_LIMIT = 1000000;

pair<int, int> normalize(int x, int y) {
    int g = gcd(abs(x), abs(y));
    return {x / g, y / g};
}

int maxScale(pair<int, int> dir) {
    int limitX = dir.first == 0 ? COORD_LIMIT : COORD_LIMIT / abs(dir.first);
    int limitY = dir.second == 0 ? COORD_LIMIT : COORD_LIMIT / abs(dir.second);
    return min(limitX, limitY);
}

void addPoint(set<pair<int, int>>& used, vector<pair<int, int>>& points, int x, int y) {
    if ((x != 0 || y != 0) && used.insert({x, y}).second) {
        points.push_back({x, y});
    }
}

void addRayPoints(set<pair<int, int>>& used, vector<pair<int, int>>& points,
                  pair<int, int> dir, int count) {
    int mx = maxScale(dir);
    if (mx <= 0) return;

    vector<int> scales;
    for (int k = 1; k <= mx && (int)scales.size() < max(count * 3, count); ++k) {
        scales.push_back(k);
    }
    shuffle(scales.begin(), scales.end());

    for (int scale : scales) {
        if ((int)points.size() >= 100000) return;
        addPoint(used, points, dir.first * scale, dir.second * scale);
        if (--count == 0) return;
    }
}

pair<int, int> randomDirection() {
    while (true) {
        int x = rnd.next(-12, 12);
        int y = rnd.next(-12, 12);
        if (x == 0 && y == 0) continue;
        return normalize(x, y);
    }
}

void fillScattered(set<pair<int, int>>& used, vector<pair<int, int>>& points, int target) {
    while ((int)points.size() < target) {
        pair<int, int> dir = randomDirection();
        int scale = rnd.next(1, maxScale(dir));
        addPoint(used, points, dir.first * scale, dir.second * scale);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int target = rnd.next(1, 80);

    set<pair<int, int>> used;
    vector<pair<int, int>> points;

    if (mode == 0) {
        pair<int, int> mainDir = randomDirection();
        addRayPoints(used, points, mainDir, rnd.next(1, max(1, target * 2 / 3)));
        fillScattered(used, points, target);
    } else if (mode == 1) {
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        shuffle(dirs.begin(), dirs.end());
        for (pair<int, int> dir : dirs) {
            addRayPoints(used, points, dir, rnd.next(1, max(1, target / 2)));
        }
        fillScattered(used, points, target);
    } else if (mode == 2) {
        pair<int, int> dir = randomDirection();
        pair<int, int> opposite = {-dir.first, -dir.second};
        addRayPoints(used, points, dir, rnd.next(1, max(1, target / 2)));
        addRayPoints(used, points, opposite, rnd.next(1, max(1, target / 2)));
        fillScattered(used, points, target);
    } else if (mode == 3) {
        vector<pair<int, int>> dirs = {{1, 1}, {-1, -1}, {1, -1}, {-1, 1},
                                      {1, 2}, {-1, 2}, {2, -1}, {-2, -1}};
        shuffle(dirs.begin(), dirs.end());
        for (pair<int, int> dir : dirs) {
            if ((int)points.size() >= target) break;
            addRayPoints(used, points, dir, rnd.next(1, 6));
        }
        fillScattered(used, points, target);
    } else {
        vector<pair<int, int>> boundary = {
            {COORD_LIMIT, 1}, {-COORD_LIMIT, 1}, {1, COORD_LIMIT},
            {1, -COORD_LIMIT}, {COORD_LIMIT, COORD_LIMIT},
            {-COORD_LIMIT, -COORD_LIMIT}, {COORD_LIMIT, -COORD_LIMIT},
            {-COORD_LIMIT, COORD_LIMIT},
        };
        shuffle(boundary.begin(), boundary.end());
        for (pair<int, int> point : boundary) {
            if ((int)points.size() >= target) break;
            addPoint(used, points, point.first, point.second);
        }
        fillScattered(used, points, target);
    }

    shuffle(points.begin(), points.end());
    println((int)points.size());
    for (pair<int, int> point : points) {
        println(point.first, point.second);
    }

    return 0;
}
