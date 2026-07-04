#include "testlib.h"

#include <algorithm>
#include <map>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

Point normalizedSlope(const Point& a, const Point& b) {
    long long dx = b.first - a.first;
    long long dy = b.second - a.second;
    long long g = gcd(abs(dx), abs(dy));
    dx /= g;
    dy /= g;

    if (dx < 0 || (dx == 0 && dy < 0)) {
        dx = -dx;
        dy = -dy;
    }
    return {dx, dy};
}

void ensureNoFourCollinear(const vector<Point>& points) {
    int n = static_cast<int>(points.size());
    for (int i = 0; i < n; ++i) {
        map<Point, int> countBySlope;
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                continue;
            }
            Point slope = normalizedSlope(points[i], points[j]);
            int count = ++countBySlope[slope];
            ensuref(count <= 2,
                    "four collinear points found through point %d with slope (%lld, %lld)",
                    i + 1, slope.first, slope.second);
        }
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000, "n");
        inf.readEoln();

        vector<Point> points;
        points.reserve(n);
        set<Point> seen;

        for (int i = 0; i < n; ++i) {
            long long x = inf.readLong(-1000000000LL, 1000000000LL, "x");
            inf.readSpace();
            long long y = inf.readLong(-1000000000LL, 1000000000LL, "y");
            inf.readEoln();

            Point point = {x, y};
            ensuref(seen.insert(point).second,
                    "duplicate point at test case %d index %d: (%lld, %lld)",
                    tc, i + 1, x, y);
            points.push_back(point);
        }

        ensureNoFourCollinear(points);
    }

    inf.readEof();
}
