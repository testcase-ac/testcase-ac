#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <set>
#include <vector>

using namespace std;

using int64 = long long;

struct Point {
    int64 x;
    int64 y;
};

static int64 dist(Point a, Point b) {
    return llabs(a.x - b.x) + llabs(a.y - b.y);
}

static int64 routeDist(Point start, Point finish, const vector<Point>& route) {
    int64 total = 0;
    Point current = start;
    for (Point next : route) {
        total += dist(current, next);
        current = next;
    }
    return total + dist(current, finish);
}

static int64 coordNear(int64 base, int64 span) {
    return max(-1000000000LL, min(1000000000LL, base + rnd.next(-span, span)));
}

static Point clampPoint(Point p) {
    return {max(-1000000000LL, min(1000000000LL, p.x)),
            max(-1000000000LL, min(1000000000LL, p.y))};
}

static vector<Point> makeRoute(Point start, Point finish, int mode, int64 span) {
    vector<Point> route;

    if (mode == 0) {
        int64 x = rnd.next(min(start.x, finish.x), max(start.x, finish.x));
        int64 y = rnd.next(min(start.y, finish.y), max(start.y, finish.y));
        route.push_back({x, y});
    } else if (mode == 1) {
        int64 offset = rnd.next(1LL, max(1LL, span));
        if (rnd.next(2) == 0) offset = -offset;
        route.push_back(clampPoint({start.x + offset, start.y}));
        route.push_back(clampPoint({finish.x + offset, finish.y}));
    } else if (mode == 2) {
        route.push_back({start.x, coordNear(start.y, span)});
        route.push_back({coordNear(finish.x, span), route.back().y});
        route.push_back({route.back().x, finish.y});
    } else {
        int m = rnd.next(1, 6);
        Point current = start;
        for (int i = 0; i < m; ++i) {
            int64 x = coordNear((i % 2 == 0 ? current.x : finish.x), span);
            int64 y = coordNear((i % 2 == 0 ? finish.y : current.y), span);
            route.push_back({x, y});
            current = route.back();
        }
    }

    return route;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(2, mode == 3 ? 14 : 9);
    int64 span = mode == 3 ? rnd.next(1000LL, 1000000LL) : rnd.next(3LL, 30LL);

    Point start{rnd.next(-50LL, 50LL), rnd.next(-50LL, 50LL)};
    Point finish{rnd.next(-50LL, 50LL), rnd.next(-50LL, 50LL)};
    if (mode == 3 && rnd.next(3) == 0) {
        start = {rnd.next(-1000000000LL, -999999000LL), rnd.next(-1000000000LL, -999999000LL)};
        finish = {rnd.next(999999000LL, 1000000000LL), rnd.next(999999000LL, 1000000000LL)};
        span = rnd.next(1LL, 500LL);
    }

    vector<vector<Point>> routes;
    set<int64> distances;
    for (int i = 0; i < n; ++i) {
        for (int attempt = 0; attempt < 1000; ++attempt) {
            vector<Point> route = makeRoute(start, finish, (mode + i + rnd.next(4)) % 4, span + i);
            int64 total = routeDist(start, finish, route);
            if (distances.insert(total).second) {
                routes.push_back(route);
                break;
            }
        }
    }

    println((int)routes.size());
    println(start.x, start.y, finish.x, finish.y);
    for (const vector<Point>& route : routes) {
        println((int)route.size());
        for (Point p : route) {
            println(p.x, p.y);
        }
    }

    return 0;
}
