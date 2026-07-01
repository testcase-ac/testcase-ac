#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;
const long long MIN_COORD = -1000000000LL;
const long long MAX_COORD = 1000000000LL;

void addPoint(vector<Point>& points, set<Point>& used, long long x, long long y) {
    if (used.emplace(x, y).second) {
        points.emplace_back(x, y);
    }
}

long long pickCoord(bool wide, int margin = 0) {
    long long lo = MIN_COORD + margin;
    long long hi = MAX_COORD - margin;
    if (!wide) {
        return rnd.next(-20, 20);
    }
    int choice = rnd.next(0, 4);
    if (choice == 0) return lo + rnd.next(0, 30);
    if (choice == 1) return hi - rnd.next(0, 30);
    return rnd.next(-1000000, 1000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    bool wide = rnd.next(0, 9) == 0;
    vector<Point> points;
    set<Point> used;

    if (mode == 0) {
        int n = rnd.next(1, 4);
        int step = rnd.next(1, 4);
        long long x = pickCoord(wide, (n - 1) * step);
        long long y = pickCoord(wide);
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, x + i * step, y);
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 8);
        int step = rnd.next(1, 5);
        bool vertical = rnd.next(0, 1);
        int margin = (n - 1) * step;
        long long x = pickCoord(wide, vertical ? 0 : margin);
        long long y = pickCoord(wide, vertical ? margin : 0);
        for (int i = 0; i < n; ++i) {
            if (vertical) {
                addPoint(points, used, x, y + i * step);
            } else {
                addPoint(points, used, x + i * step, y);
            }
        }
    } else if (mode == 2) {
        int w = rnd.next(1, 8);
        int h = rnd.next(1, 8);
        long long x1 = pickCoord(wide, w);
        long long y1 = pickCoord(wide, h);
        addPoint(points, used, x1, y1);
        addPoint(points, used, x1 + w, y1);
        addPoint(points, used, x1, y1 + h);
        addPoint(points, used, x1 + w, y1 + h);
        int extra = rnd.next(0, 5);
        for (int i = 0; i < extra; ++i) {
            int side = rnd.next(0, 3);
            long long x = x1 + rnd.next(0, w);
            long long y = y1 + rnd.next(0, h);
            if (side == 0) y = y1;
            if (side == 1) y = y1 + h;
            if (side == 2) x = x1;
            if (side == 3) x = x1 + w;
            addPoint(points, used, x, y);
        }
    } else if (mode == 3) {
        int n = rnd.next(3, 12);
        long long x = pickCoord(wide, (n - 1) * 3);
        long long y = pickCoord(wide, 2);
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, x + i * rnd.next(1, 3), y + rnd.next(-2, 2));
        }
    } else if (mode == 4) {
        int clusters = rnd.next(2, 4);
        for (int c = 0; c < clusters; ++c) {
            long long cx = pickCoord(wide, 3);
            long long cy = pickCoord(wide, 3);
            int count = rnd.next(2, 5);
            for (int i = 0; i < count; ++i) {
                addPoint(points, used, cx + rnd.next(-3, 3), cy + rnd.next(-3, 3));
            }
        }
    } else {
        addPoint(points, used, MIN_COORD, MIN_COORD);
        addPoint(points, used, MAX_COORD, MAX_COORD);
        int extra = rnd.next(0, 4);
        for (int i = 0; i < extra; ++i) {
            addPoint(points, used, pickCoord(true), pickCoord(true));
        }
    }

    shuffle(points.begin(), points.end());
    println(static_cast<int>(points.size()));
    for (const Point& point : points) {
        println(point.first, point.second);
    }

    return 0;
}
