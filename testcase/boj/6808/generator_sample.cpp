#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
    int z;
};

Point randomPoint(int limit) {
    return {rnd.next(-limit, limit), rnd.next(-limit, limit), rnd.next(-limit, limit)};
}

Point clampPoint(Point p) {
    p.x = max(-1000, min(1000, p.x));
    p.y = max(-1000, min(1000, p.y));
    p.z = max(-1000, min(1000, p.z));
    return p;
}

Point offsetPoint(Point p, int distance) {
    vector<Point> directions = {
        {distance, 0, 0}, {-distance, 0, 0}, {0, distance, 0},
        {0, -distance, 0}, {0, 0, distance}, {0, 0, -distance},
        {distance, distance, 0}, {-distance, distance, 0},
        {distance, 0, -distance}, {0, -distance, distance},
    };
    Point d = rnd.any(directions);
    return clampPoint({p.x + d.x, p.y + d.y, p.z + d.z});
}

Point segmentPoint(Point a, Point b) {
    int den = rnd.next(2, 5);
    int num = rnd.next(0, den);
    return {
        (a.x * (den - num) + b.x * num) / den,
        (a.y * (den - num) + b.y * num) / den,
        (a.z * (den - num) + b.z * num) / den,
    };
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, mode == 4 ? 12 : 7);
    int d = rnd.next(1, 50);

    vector<Point> path;
    path.push_back({0, 0, 0});
    for (int i = 0; i < n; ++i) {
        Point next;
        if (mode == 1 && i % 2 == 0) {
            next = randomPoint(1000);
        } else if (mode == 2) {
            next = {rnd.next(-1000, 1000), rnd.next(-30, 30), rnd.next(-30, 30)};
        } else if (mode == 3) {
            next = offsetPoint(path.back(), rnd.next(1, 80));
        } else {
            next = randomPoint(250);
        }
        if (next.x == path.back().x && next.y == path.back().y && next.z == path.back().z) {
            next.x = next.x == 1000 ? 999 : next.x + 1;
        }
        path.push_back(next);
    }

    int m = rnd.next(4, mode == 4 ? 20 : 12);
    vector<tuple<int, int, int, int, int>> planets;
    for (int i = 0; i < m; ++i) {
        Point center;
        int value = rnd.next(1, 10000);
        int radius = rnd.next(1, 100);

        int kind = rnd.next(0, 5);
        if (kind <= 2) {
            int seg = rnd.next(0, n - 1);
            center = segmentPoint(path[seg], path[seg + 1]);
            if (kind == 1) {
                center = offsetPoint(center, rnd.next(1, min(120, d + radius)));
            } else if (kind == 2) {
                center = offsetPoint(center, rnd.next(d + radius + 1, min(300, d + radius + 160)));
            }
        } else if (kind == 3) {
            center = rnd.any(path);
        } else if (kind == 4) {
            center = randomPoint(1000);
        } else {
            center = rnd.any(vector<Point>{{-1000, -1000, -1000}, {1000, 1000, 1000},
                                           {-1000, 1000, -1000}, {1000, -1000, 1000}});
        }

        planets.emplace_back(center.x, center.y, center.z, value, radius);
    }

    println(m);
    for (auto [x, y, z, value, radius] : planets) {
        println(x, y, z, value, radius);
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        println(path[i].x, path[i].y, path[i].z);
    }
    println(d);

    return 0;
}
