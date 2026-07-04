#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

using Point = pair<long long, long long>;

const long long COORD_LIMIT = 1000000000LL;

void addPoint(vector<Point>& points, set<Point>& used, long long x, long long y) {
    if (x < -COORD_LIMIT || x > COORD_LIMIT || y < -COORD_LIMIT || y > COORD_LIMIT) return;
    if (used.insert({x, y}).second) points.push_back({x, y});
}

void addRandomPoint(vector<Point>& points, set<Point>& used, long long lo, long long hi) {
    for (int tries = 0; tries < 200; ++tries) {
        long long x = rnd.next(lo, hi);
        long long y = rnd.next(lo, hi);
        if (!used.count({x, y})) {
            addPoint(points, used, x, y);
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> points;
    set<Point> used;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int width = rnd.next(2, 5);
        int height = rnd.next(2, 5);
        long long step = rnd.next(1, 5);
        long long ox = rnd.next(-20, 20);
        long long oy = rnd.next(-20, 20);
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                addPoint(points, used, ox + i * step, oy + j * step);
            }
        }
    } else if (mode == 1) {
        long long cy = rnd.next(-20, 20);
        int arms = rnd.next(2, 6);
        long long step = rnd.next(1, 8);
        addPoint(points, used, rnd.next(-5, 5), cy + rnd.next(1, 8));
        for (int k = -arms; k <= arms; ++k) {
            addPoint(points, used, k * step, cy);
        }
        int extra = rnd.next(0, 5);
        for (int i = 0; i < extra; ++i) addRandomPoint(points, used, -30, 30);
    } else if (mode == 2) {
        long long cx = rnd.next(-50, 50);
        long long cy = rnd.next(-50, 50);
        int radius = rnd.next(1, 12);
        vector<Point> offsets = {
            {radius, 0}, {-radius, 0}, {0, radius}, {0, -radius},
            {radius, radius}, {-radius, radius}, {radius, -radius}, {-radius, -radius},
        };
        shuffle(offsets.begin(), offsets.end());
        addPoint(points, used, cx, cy);
        int take = rnd.next(3, (int)offsets.size());
        for (int i = 0; i < take; ++i) {
            addPoint(points, used, cx + offsets[i].first, cy + offsets[i].second);
        }
        int extra = rnd.next(0, 6);
        for (int i = 0; i < extra; ++i) addRandomPoint(points, used, cx - 20, cx + 20);
    } else if (mode == 3) {
        int n = rnd.next(8, 25);
        long long baseX = rnd.next(-1000, 1000);
        long long baseY = rnd.next(-1000, 1000);
        for (int i = 0; i < n; ++i) {
            long long dx = rnd.next(-40, 40);
            long long dy = rnd.next(-40, 40);
            if (rnd.next(0, 3) == 0) dy = dx;
            addPoint(points, used, baseX + dx, baseY + dy);
        }
    } else if (mode == 4) {
        vector<Point> corners = {
            {-COORD_LIMIT, -COORD_LIMIT},
            {-COORD_LIMIT, COORD_LIMIT},
            {COORD_LIMIT, -COORD_LIMIT},
            {COORD_LIMIT, COORD_LIMIT},
            {0, 0},
        };
        for (Point p : corners) addPoint(points, used, p.first, p.second);
        int extra = rnd.next(0, 8);
        for (int i = 0; i < extra; ++i) addRandomPoint(points, used, -1000, 1000);
    } else {
        int n = rnd.next(3, 35);
        long long lo = rnd.next(-200, 0);
        long long hi = rnd.next(0, 200);
        for (int i = 0; i < n; ++i) addRandomPoint(points, used, lo, hi);
    }

    while ((int)points.size() < 3) addRandomPoint(points, used, -10, 10);
    shuffle(points.begin(), points.end());

    println((int)points.size());
    for (Point p : points) println(p.first, p.second);

    return 0;
}
