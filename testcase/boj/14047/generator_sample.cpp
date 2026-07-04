#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const int MIN_COORD = -100000;
const int MAX_COORD = 100000;

void addPoint(vector<pair<int, int>>& points, set<pair<int, int>>& used, int x, int y) {
    if (used.insert({x, y}).second) points.push_back({x, y});
}

int shiftedCoord(int base, int delta) {
    return max(MIN_COORD, min(MAX_COORD, base + delta));
}

void addCross(vector<pair<int, int>>& points, set<pair<int, int>>& used, int cx, int cy,
              int left, int right, int down, int up, int step) {
    addPoint(points, used, cx, cy);
    for (int i = 1; i <= left; ++i) addPoint(points, used, shiftedCoord(cx, -i * step), cy);
    for (int i = 1; i <= right; ++i) addPoint(points, used, shiftedCoord(cx, i * step), cy);
    for (int i = 1; i <= down; ++i) addPoint(points, used, cx, shiftedCoord(cy, -i * step));
    for (int i = 1; i <= up; ++i) addPoint(points, used, cx, shiftedCoord(cy, i * step));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> points;
    set<pair<int, int>> used;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        addPoint(points, used, rnd.next(-20, 20), rnd.next(-20, 20));
    } else if (mode == 1) {
        int n = rnd.next(4, 16);
        int y = rnd.next(-50, 50);
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, rnd.next(-100, 100), y);
        }
    } else if (mode == 2) {
        int cx = rnd.next(-60, 60);
        int cy = rnd.next(-60, 60);
        int step = rnd.next(1, 8);
        addCross(points, used, cx, cy, rnd.next(1, 5), rnd.next(1, 5),
                 rnd.next(1, 5), rnd.next(1, 5), step);
    } else if (mode == 3) {
        int rows = rnd.next(2, 5);
        int cols = rnd.next(2, 5);
        int sx = rnd.next(1, 7);
        int sy = rnd.next(1, 7);
        int startX = rnd.next(-80, 80);
        int startY = rnd.next(-80, 80);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                addPoint(points, used, startX + j * sx, startY + i * sy);
            }
        }
    } else if (mode == 4) {
        int centers = rnd.next(2, 4);
        int baseX = rnd.next(-200, 200);
        int baseY = rnd.next(-200, 200);
        for (int i = 0; i < centers; ++i) {
            int cx = baseX + i * rnd.next(5, 20);
            int cy = baseY + rnd.next(-10, 10);
            addCross(points, used, cx, cy, rnd.next(1, 3), rnd.next(1, 3),
                     rnd.next(1, 3), rnd.next(1, 3), rnd.next(1, 5));
        }
    } else {
        vector<int> xs = {MIN_COORD, -1, 0, 1, MAX_COORD};
        vector<int> ys = {MIN_COORD, -1, 0, 1, MAX_COORD};
        shuffle(xs.begin(), xs.end());
        shuffle(ys.begin(), ys.end());
        int takeX = rnd.next(2, 5);
        int takeY = rnd.next(2, 5);
        for (int i = 0; i < takeX; ++i) {
            for (int j = 0; j < takeY; ++j) {
                if (rnd.next(0, 2) != 0) addPoint(points, used, xs[i], ys[j]);
            }
        }
        if (points.empty()) addPoint(points, used, 0, 0);
    }

    int noise = rnd.next(0, 8);
    for (int i = 0; i < noise; ++i) {
        addPoint(points, used, rnd.next(-1000, 1000), rnd.next(-1000, 1000));
    }

    shuffle(points.begin(), points.end());

    println((int)points.size());
    for (auto [x, y] : points) {
        println(x, y);
    }

    return 0;
}
