#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

static pair<long long, long long> normalizedSlope(const Point& from, const Point& to) {
    long long dx = to.first - from.first;
    long long dy = to.second - from.second;
    long long g = gcd(llabs(dx), llabs(dy));
    dx /= g;
    dy /= g;
    if (dx < 0 || (dx == 0 && dy < 0)) {
        dx = -dx;
        dy = -dy;
    }
    return {dx, dy};
}

static void ensureNoThreeCollinear(const vector<Point>& points, int testCase) {
    for (int i = 0; i < (int)points.size(); ++i) {
        set<pair<long long, long long>> slopes;
        for (int j = i + 1; j < (int)points.size(); ++j) {
            auto slope = normalizedSlope(points[i], points[j]);
            ensuref(slopes.insert(slope).second,
                    "case %d has three collinear points including indices %d and %d",
                    testCase, i + 1, j + 1);
        }
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives only sum(n) <= 10000, so T is capped by the same
    // aggregate because each test case has n >= 1.
    int t = inf.readInt(1, 10000, "T");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000, "n");
        inf.readEoln();
        totalN += n;
        ensuref(totalN <= 10000, "sum of n exceeds 10000 after case %d", tc);

        vector<Point> points;
        points.reserve(3 * n);
        set<Point> seen;
        for (int i = 0; i < 3 * n; ++i) {
            long long x = inf.readLong(-1000000000LL, 1000000000LL, "x_i");
            inf.readSpace();
            long long y = inf.readLong(-1000000000LL, 1000000000LL, "y_i");
            inf.readEoln();

            Point point = {x, y};
            ensuref(seen.insert(point).second,
                    "case %d has duplicate point at index %d: (%lld, %lld)",
                    tc, i + 1, x, y);
            points.push_back(point);
        }

        ensureNoThreeCollinear(points, tc);
    }

    inf.readEof();
    return 0;
}
