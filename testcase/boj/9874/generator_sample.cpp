#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

const long long MAX_COORD = 1000000000LL;

void addPoint(vector<Point>& points, set<Point>& used, long long x, long long y) {
    if (used.insert({x, y}).second) {
        points.push_back({x, y});
    }
}

long long randomCoord(long long lo = 0, long long hi = MAX_COORD) {
    return rnd.next(lo, hi);
}

void fillRandom(vector<Point>& points, set<Point>& used, int n) {
    while ((int)points.size() < n) {
        addPoint(points, used, randomCoord(), randomCoord());
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = 2 * rnd.next(1, 6);
    int mode = rnd.next(5);

    vector<Point> points;
    set<Point> used;

    if (mode == 0) {
        fillRandom(points, used, n);
    } else if (mode == 1) {
        int rows = rnd.next(1, min(4, n));
        vector<long long> ys;
        while ((int)ys.size() < rows) {
            long long y = randomCoord();
            if (find(ys.begin(), ys.end(), y) == ys.end()) {
                ys.push_back(y);
            }
        }
        long long baseX = randomCoord(0, MAX_COORD - 20);
        int gap = rnd.next(1, 7);
        for (int i = 0; i < n; ++i) {
            long long x = baseX + gap * (i / rows);
            long long y = ys[i % rows];
            addPoint(points, used, x, y);
        }
    } else if (mode == 2) {
        int width = rnd.next(2, 4);
        long long baseX = randomCoord(0, MAX_COORD - 100);
        long long baseY = randomCoord(0, MAX_COORD - 100);
        int dx = rnd.next(1, 9);
        int dy = rnd.next(1, 9);
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, baseX + dx * (i % width), baseY + dy * (i / width));
        }
    } else if (mode == 3) {
        vector<Point> candidates = {
            {0, 0},
            {0, MAX_COORD},
            {MAX_COORD, 0},
            {MAX_COORD, MAX_COORD},
            {1, 0},
            {MAX_COORD - 1, 0},
            {0, 1},
            {0, MAX_COORD - 1},
            {1, MAX_COORD},
            {MAX_COORD - 1, MAX_COORD},
            {MAX_COORD, 1},
            {MAX_COORD, MAX_COORD - 1},
        };
        shuffle(candidates.begin(), candidates.end());
        for (Point p : candidates) {
            if ((int)points.size() == n) break;
            addPoint(points, used, p.first, p.second);
        }
    } else {
        int rows = rnd.next(2, min(6, n));
        long long baseX = randomCoord(0, MAX_COORD - 1000);
        long long baseY = randomCoord(0, MAX_COORD - 1000);
        for (int i = 0; i < n; ++i) {
            int row = i % rows;
            int col = i / rows;
            long long x = baseX + 3LL * col + (row % 2);
            long long y = baseY + 5LL * row;
            addPoint(points, used, x, y);
        }
    }

    fillRandom(points, used, n);
    shuffle(points.begin(), points.end());

    println(n);
    for (Point p : points) {
        println(p.first, p.second);
    }

    return 0;
}
