#include "testlib.h"

#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

struct Point {
    long long x;
    long long y;
};

__int128 cross(const Point& a, const Point& b, const Point& c) {
    long long bax = b.x - a.x;
    long long bay = b.y - a.y;
    long long cbx = c.x - b.x;
    long long cby = c.y - b.y;
    return static_cast<__int128>(bax) * cby - static_cast<__int128>(bay) * cbx;
}

bool isStrictlyConvex(const vector<Point>& points) {
    int count = static_cast<int>(points.size());
    for (int i = 0; i < count; ++i) {
        if (cross(points[i], points[(i + 1) % count], points[(i + 2) % count]) <= 0) {
            return false;
        }
    }
    return true;
}

Point makePoint(long long centerX, long long centerY, long long radiusX, long long radiusY,
                double angle) {
    long long x = llround(centerX + radiusX * cos(angle));
    long long y = llround(centerY + radiusY * sin(angle));
    return {x, y};
}

void printCoord(long long value) {
    printf("%lld.%04lld", value / 10000, value % 10000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const double pi = acos(-1.0);
    int mode = rnd.next(0, 4);

    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 6);
    } else if (mode == 2) {
        n = rnd.next(7, 14);
    } else if (mode == 3) {
        n = rnd.any(vector<int>{20, 30, 50});
    } else {
        n = 100;
    }

    int vertices = 2 * n;
    vector<Point> points;
    for (int attempt = 0; attempt < 200; ++attempt) {
        long long centerX = rnd.next(2500, 7500) * 10000LL;
        long long centerY = rnd.next(2500, 7500) * 10000LL;
        long long maxRadiusX = min(centerX, 10000LL * 10000LL - centerX);
        long long maxRadiusY = min(centerY, 10000LL * 10000LL - centerY);

        long long radiusX;
        long long radiusY;
        if (mode == 1) {
            radiusX = rnd.next(1200, 4200) * 10000LL;
            radiusY = rnd.next(1200, 4200) * 10000LL;
        } else if (mode == 2) {
            radiusX = rnd.next(2500, 4700) * 10000LL;
            radiusY = rnd.next(300, 1300) * 10000LL;
            if (rnd.next(0, 1) == 1) {
                swap(radiusX, radiusY);
            }
        } else {
            radiusX = rnd.next(3000, 4800) * 10000LL;
            radiusY = rnd.next(3000, 4800) * 10000LL;
        }
        radiusX = min(radiusX, maxRadiusX - 10000);
        radiusY = min(radiusY, maxRadiusY - 10000);
        if (radiusX <= 0 || radiusY <= 0) {
            continue;
        }

        double offset = rnd.next(0.0, 2.0 * pi);
        double jitterLimit = (mode == 0 || mode == 4) ? 0.0 : pi / vertices / 3.0;

        points.clear();
        for (int i = 0; i < vertices; ++i) {
            double angle = offset + 2.0 * pi * i / vertices;
            if (jitterLimit > 0.0) {
                angle += rnd.next(-jitterLimit, jitterLimit);
            }
            points.push_back(makePoint(centerX, centerY, radiusX, radiusY, angle));
        }

        if (isStrictlyConvex(points)) {
            break;
        }
    }

    ensuref(isStrictlyConvex(points), "failed to generate a strictly convex polygon");

    println(n);
    for (const Point& point : points) {
        printCoord(point.x);
        putchar(' ');
        printCoord(point.y);
        putchar('\n');
    }

    return 0;
}
