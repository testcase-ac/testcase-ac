#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

__int128 cross(const Point& a, const Point& b, const Point& c) {
    __int128 abx = (__int128)b.first - a.first;
    __int128 aby = (__int128)b.second - a.second;
    __int128 bcx = (__int128)c.first - b.first;
    __int128 bcy = (__int128)c.second - b.second;
    return abx * bcy - aby * bcx;
}

int sign(__int128 value) {
    if (value < 0) {
        return -1;
    }
    if (value > 0) {
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 200000, "n");
    inf.readEoln();

    vector<Point> points;
    points.reserve(n);
    set<Point> seen;
    for (int i = 0; i < n; ++i) {
        long long x = inf.readLong(-1000000000LL, 1000000000LL, "x_i");
        inf.readSpace();
        long long y = inf.readLong(-1000000000LL, 1000000000LL, "y_i");
        inf.readEoln();

        Point point = {x, y};
        ensuref(seen.insert(point).second, "duplicate vertex at index %d: (%lld, %lld)", i + 1, x, y);
        points.push_back(point);
    }

    int orientation = 0;
    for (int i = 0; i < n; ++i) {
        const Point& a = points[i];
        const Point& b = points[(i + 1) % n];
        const Point& c = points[(i + 2) % n];
        int turn = sign(cross(a, b, c));

        // CHECK: the statement says polygon vertices, so listed points are treated as corners.
        ensuref(turn != 0, "collinear consecutive vertices at indices %d, %d, %d",
                i + 1, (i + 1) % n + 1, (i + 2) % n + 1);
        if (orientation == 0) {
            orientation = turn;
        }
        ensuref(turn == orientation, "polygon is not convex in traversal order near indices %d, %d, %d",
                i + 1, (i + 1) % n + 1, (i + 2) % n + 1);
    }

    inf.readEof();
}
