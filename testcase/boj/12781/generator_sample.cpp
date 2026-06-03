#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

int orient(const Point& a, const Point& b, const Point& c) {
    long long cross = 1LL * (b.first - a.first) * (c.second - a.second) -
                      1LL * (b.second - a.second) * (c.first - a.first);
    if (cross > 0) return 1;
    if (cross < 0) return -1;
    return 0;
}

bool distinct(const vector<Point>& points) {
    return set<Point>(points.begin(), points.end()).size() == points.size();
}

bool strictlyCrosses(const vector<Point>& p) {
    return orient(p[0], p[1], p[2]) * orient(p[0], p[1], p[3]) < 0 &&
           orient(p[2], p[3], p[0]) * orient(p[2], p[3], p[1]) < 0;
}

Point randomPoint(int lo, int hi) {
    return {rnd.next(lo, hi), rnd.next(lo, hi)};
}

vector<Point> randomDistinctPoints(int lo, int hi) {
    vector<Point> points;
    set<Point> used;
    while ((int)points.size() < 4) {
        Point p = randomPoint(lo, hi);
        if (used.insert(p).second) points.push_back(p);
    }
    return points;
}

vector<Point> crossingCase() {
    int cx = rnd.next(-20, 20);
    int cy = rnd.next(-20, 20);
    int dx = rnd.next(1, 20);
    int dy = rnd.next(1, 20);
    vector<Point> points = {
        {cx - dx, cy},
        {cx + dx, cy},
        {cx, cy - dy},
        {cx, cy + dy},
    };

    if (rnd.next(2)) swap(points[0], points[1]);
    if (rnd.next(2)) swap(points[2], points[3]);
    return points;
}

vector<Point> nonCrossingCase() {
    int x1 = rnd.next(-30, -1);
    int x2 = rnd.next(x1 + 1, 30);
    int y = rnd.next(-30, 30);
    int gap = rnd.next(1, 15);
    int tilt = rnd.next(-5, 5);
    vector<Point> points = {
        {x1, y},
        {x2, y + tilt},
        {x1, y + gap},
        {x2, y + gap + tilt},
    };

    if (rnd.next(2)) swap(points[0], points[1]);
    if (rnd.next(2)) swap(points[2], points[3]);
    return points;
}

vector<Point> collinearCase() {
    int base = rnd.next(-50, 47);
    int y = rnd.next(-50, 50);
    vector<Point> points = {
        {base, y},
        {base + rnd.next(1, 3), y},
        {base + rnd.next(4, 6), y},
        {base + rnd.next(7, 10), y},
    };
    shuffle(points.begin(), points.end());
    return points;
}

vector<Point> boundaryCase() {
    int side = rnd.next(4);
    int a = rnd.next(-10000, -9990);
    int b = rnd.next(9990, 10000);
    if (side == 0) return {{-10000, a}, {10000, b}, {a, 10000}, {b, -10000}};
    if (side == 1) return {{a, -10000}, {b, 10000}, {-10000, b}, {10000, a}};
    if (side == 2) return {{-10000, -10000}, {10000, 10000}, {-10000, b}, {10000, a}};
    return {{-10000, 10000}, {10000, -10000}, {a, -10000}, {b, 10000}};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> points;
    int mode = rnd.next(5);
    for (int tries = 0; tries < 200; ++tries) {
        if (mode == 0) {
            points = crossingCase();
        } else if (mode == 1) {
            points = nonCrossingCase();
        } else if (mode == 2) {
            points = collinearCase();
        } else if (mode == 3) {
            points = boundaryCase();
        } else {
            points = randomDistinctPoints(-100, 100);
        }

        if (distinct(points)) break;
    }

    if (mode == 4 && rnd.next(3) == 0) {
        while (!strictlyCrosses(points)) points = randomDistinctPoints(-100, 100);
    }

    vector<int> output;
    for (const Point& point : points) {
        output.push_back(point.first);
        output.push_back(point.second);
    }
    println(output);
    return 0;
}
