#include "testlib.h"

#include <algorithm>
#include <cmath>
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

bool isConvex(const vector<Point>& points) {
    int orientation = 0;
    int n = (int)points.size();
    for (int i = 0; i < n; ++i) {
        __int128 value = cross(points[i], points[(i + 1) % n], points[(i + 2) % n]);
        if (value == 0) {
            return false;
        }
        int turn = value > 0 ? 1 : -1;
        if (orientation == 0) {
            orientation = turn;
        } else if (turn != orientation) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long double pi = acosl(-1.0L);
    int n = rnd.next(4, 12);
    int mode = rnd.next(0, 4);

    vector<Point> points;
    for (int attempt = 0; attempt < 10000; ++attempt) {
        points.clear();

        long double baseAngle = rnd.next(0.0, 2.0 * (double)pi);
        long double radiusX = rnd.next(6, 24);
        long double radiusY = rnd.next(6, 24);
        long long scale = mode == 0 ? 1 : rnd.next(1, 5);
        long long shiftX = rnd.next(-25, 25);
        long long shiftY = rnd.next(-25, 25);

        for (int i = 0; i < n; ++i) {
            long double sector = (2.0L * pi * i) / n;
            long double jitter = rnd.next(-0.18, 0.18) * (2.0L * pi / n);
            long double radius = rnd.next(0.82, 1.18);
            long double angle = baseAngle + sector + jitter;
            long long x = llround(cosl(angle) * radiusX * radius) * scale + shiftX;
            long long y = llround(sinl(angle) * radiusY * radius) * scale + shiftY;
            points.push_back({x, y});
        }

        sort(points.begin(), points.end());
        if (unique(points.begin(), points.end()) != points.end()) {
            continue;
        }

        Point center = {0, 0};
        for (const Point& point : points) {
            center.first += point.first;
            center.second += point.second;
        }

        sort(points.begin(), points.end(), [&](const Point& a, const Point& b) {
            long long ax = a.first * n - center.first;
            long long ay = a.second * n - center.second;
            long long bx = b.first * n - center.first;
            long long by = b.second * n - center.second;
            bool upperA = ay > 0 || (ay == 0 && ax >= 0);
            bool upperB = by > 0 || (by == 0 && bx >= 0);
            if (upperA != upperB) {
                return upperA > upperB;
            }
            __int128 value = (__int128)ax * by - (__int128)ay * bx;
            if (value != 0) {
                return value > 0;
            }
            return ax * ax + ay * ay < bx * bx + by * by;
        });

        if (mode == 3) {
            reverse(points.begin(), points.end());
        }

        if (isConvex(points)) {
            break;
        }
    }

    ensuref((int)points.size() == n && isConvex(points), "failed to generate a convex polygon");

    println(n);
    for (const Point& point : points) {
        println(point.first, point.second);
    }

    return 0;
}
