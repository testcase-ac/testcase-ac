#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <map>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

const long long LIM = 1000000000LL;

Point normalizedSlope(const Point& a, const Point& b) {
    long long dx = b.first - a.first;
    long long dy = b.second - a.second;
    long long g = gcd(llabs(dx), llabs(dy));
    dx /= g;
    dy /= g;

    if (dx < 0 || (dx == 0 && dy < 0)) {
        dx = -dx;
        dy = -dy;
    }
    return {dx, dy};
}

bool inBounds(const Point& p) {
    return -LIM <= p.first && p.first <= LIM && -LIM <= p.second && p.second <= LIM;
}

bool hasNoFourCollinear(const vector<Point>& points) {
    int n = static_cast<int>(points.size());
    for (int i = 0; i < n; ++i) {
        map<Point, int> countBySlope;
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                continue;
            }
            Point slope = normalizedSlope(points[i], points[j]);
            if (++countBySlope[slope] > 2) {
                return false;
            }
        }
    }
    return true;
}

bool tryAddPoint(vector<Point>& points, set<Point>& seen, const Point& point) {
    if (!inBounds(point) || seen.count(point) != 0) {
        return false;
    }

    points.push_back(point);
    if (!hasNoFourCollinear(points)) {
        points.pop_back();
        return false;
    }

    seen.insert(point);
    return true;
}

void addAffineGrid(vector<Point>& points, set<Point>& seen, int width, int height) {
    while (true) {
        long long ax = rnd.next(-7, 7);
        long long ay = rnd.next(-7, 7);
        long long bx = rnd.next(-7, 7);
        long long by = rnd.next(-7, 7);
        if (ax * by - ay * bx == 0) {
            continue;
        }

        long long ox = rnd.next(-30, 30);
        long long oy = rnd.next(-30, 30);

        vector<Point> candidate = points;
        set<Point> candidateSeen = seen;
        bool ok = true;
        for (int i = 0; i < width && ok; ++i) {
            for (int j = 0; j < height && ok; ++j) {
                Point point = {ox + i * ax + j * bx, oy + i * ay + j * by};
                if (!tryAddPoint(candidate, candidateSeen, point)) {
                    ok = false;
                }
            }
        }

        if (ok) {
            points.swap(candidate);
            seen.swap(candidateSeen);
            return;
        }
    }
}

Point randomPoint(int mode) {
    if (mode == 0) {
        return {rnd.next(-20, 20), rnd.next(-20, 20)};
    }
    if (mode == 1) {
        long long x = rnd.next(-1000, 1000);
        long long y = x * x + rnd.next(-3, 3);
        return {x, y};
    }

    long long sx = rnd.next(0, 1) == 0 ? -LIM : LIM;
    long long sy = rnd.next(0, 1) == 0 ? -LIM : LIM;
    return {sx + rnd.next(-200, 0) * (sx > 0 ? 1 : -1),
            sy + rnd.next(-200, 0) * (sy > 0 ? 1 : -1)};
}

vector<Point> makeCase(int mode) {
    vector<Point> points;
    set<Point> seen;

    if (mode == 0) {
        tryAddPoint(points, seen, {rnd.next(-5, 5), rnd.next(-5, 5)});
        return points;
    }

    if (mode == 1) {
        addAffineGrid(points, seen, 2, 2);
    } else if (mode == 2) {
        addAffineGrid(points, seen, 3, 3);
    } else {
        int base = rnd.next(0, 1);
        if (base == 0) {
            addAffineGrid(points, seen, 2, 2);
        } else {
            addAffineGrid(points, seen, 3, 3);
        }
    }

    int target = static_cast<int>(points.size()) + rnd.next(0, mode == 3 ? 12 : 6);
    target = min(target, rnd.next(8, 24));

    int attempts = 0;
    while (static_cast<int>(points.size()) < target && attempts < 10000) {
        ++attempts;
        tryAddPoint(points, seen, randomPoint(mode == 3 ? rnd.next(0, 2) : 0));
    }

    shuffle(points.begin(), points.end());
    return points;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 6);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        vector<Point> points = makeCase(tc == 0 ? 0 : rnd.next(1, 3));
        println(static_cast<int>(points.size()));
        for (const Point& point : points) {
            println(point.first, point.second);
        }
    }

    return 0;
}
