#include "testlib.h"

#include <set>

using namespace std;

using int64 = long long;

struct Point {
    int64 x;
    int64 y;
};

static int64 manhattan(Point a, Point b) {
    return llabs(a.x - b.x) + llabs(a.y - b.y);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();

    Point start;
    Point finish;
    start.x = inf.readLong(-1000000000LL, 1000000000LL, "s_x");
    inf.readSpace();
    start.y = inf.readLong(-1000000000LL, 1000000000LL, "s_y");
    inf.readSpace();
    finish.x = inf.readLong(-1000000000LL, 1000000000LL, "e_x");
    inf.readSpace();
    finish.y = inf.readLong(-1000000000LL, 1000000000LL, "e_y");
    inf.readEoln();

    set<int64> route_distances;
    for (int i = 1; i <= n; ++i) {
        int m = inf.readInt(1, 100, "M_i");
        inf.readEoln();

        Point current = start;
        int64 route_distance = 0;
        for (int j = 1; j <= m; ++j) {
            Point waypoint;
            waypoint.x = inf.readLong(-1000000000LL, 1000000000LL, "x_i_j");
            inf.readSpace();
            waypoint.y = inf.readLong(-1000000000LL, 1000000000LL, "y_i_j");
            inf.readEoln();

            route_distance += manhattan(current, waypoint);
            current = waypoint;
        }
        route_distance += manhattan(current, finish);

        ensuref(route_distances.insert(route_distance).second,
                "route distance for navigation %d is not distinct: %lld",
                i,
                route_distance);
    }

    inf.readEof();
}
