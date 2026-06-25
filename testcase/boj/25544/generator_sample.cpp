#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

void addPoint(vector<Point>& points, set<Point>& used, long long x, long long y) {
    if (used.insert({x, y}).second) {
        points.push_back({x, y});
    }
}

void addRandomPoint(vector<Point>& points, set<Point>& used, long long lo, long long hi) {
    while (true) {
        long long x = rnd.next(lo, hi);
        long long y = rnd.next(lo, hi);
        if (used.insert({x, y}).second) {
            points.push_back({x, y});
            return;
        }
    }
}

void addArm(vector<Point>& points, set<Point>& used, long long cx, long long cy,
            int dx, int dy, int count) {
    long long x = cx;
    long long y = cy;
    for (int i = 0; i < count; ++i) {
        x += dx * rnd.next(1, 4);
        y += dy * rnd.next(1, 4);
        addPoint(points, used, x, y);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> points;
    set<Point> used;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 4);
        long long y = rnd.next(-5, 5);
        long long start = rnd.next(-8, -2);
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, start + i * rnd.next(1, 3), y);
        }
    } else if (mode == 1) {
        long long cx = rnd.next(-3, 3);
        long long cy = rnd.next(-3, 3);
        addPoint(points, used, cx, cy);
        for (long long dx = -1; dx <= 1; ++dx) {
            for (long long dy = -1; dy <= 1; ++dy) {
                if (dx != 0 || dy != 0) {
                    addPoint(points, used, cx + dx, cy + dy);
                }
            }
        }
    } else if (mode == 2) {
        long long cx = rnd.next(-10, 10);
        long long cy = rnd.next(-10, 10);
        addPoint(points, used, cx, cy);
        for (int sx : {-1, 1}) {
            for (int sy : {-1, 1}) {
                addArm(points, used, cx, cy, sx, sy, rnd.next(1, 5));
            }
        }
    } else if (mode == 3) {
        vector<Point> corners = {
            {-1000000000LL, -1000000000LL},
            {-1000000000LL, 1000000000LL},
            {1000000000LL, -1000000000LL},
            {1000000000LL, 1000000000LL},
        };
        shuffle(corners.begin(), corners.end());
        int n = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, corners[i].first, corners[i].second);
        }
    } else {
        int n = rnd.next(8, 35);
        long long span = rnd.next(6, 40);
        while ((int)points.size() < n) {
            addRandomPoint(points, used, -span, span);
        }
    }

    shuffle(points.begin(), points.end());
    println((int)points.size());
    for (Point point : points) {
        println(point.first, point.second);
    }

    return 0;
}
