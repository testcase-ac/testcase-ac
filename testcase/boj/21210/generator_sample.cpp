#include "testlib.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct Point {
    double x;
    double y;
};

double coord(int limit) {
    int style = rnd.next(0, 4);
    if (style == 0) return 0.0;
    if (style == 1) return limit;
    if (style == 2) return rnd.next(0, limit);
    return rnd.next(0, limit * 1000) / 1000.0;
}

Point clampPoint(double x, double y, int X, int Y) {
    x = max(0.0, min<double>(X, x));
    y = max(0.0, min<double>(Y, y));
    return {x, y};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int X = rnd.next(1, 40);
    int Y = rnd.next(1, 40);
    vector<Point> points;

    if (mode == 0) {
        int n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            points.push_back({coord(X), coord(Y)});
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 10);
        double cx = rnd.next(0, X * 1000) / 1000.0;
        double cy = rnd.next(0, Y * 1000) / 1000.0;
        double spread = rnd.next(0, 3000) / 1000.0;
        for (int i = 0; i < n; ++i) {
            double dx = rnd.next(-3000, 3000) / 1000.0 * spread;
            double dy = rnd.next(-3000, 3000) / 1000.0 * spread;
            points.push_back(clampPoint(cx + dx, cy + dy, X, Y));
        }
    } else if (mode == 2) {
        int n = rnd.next(3, 12);
        for (int i = 0; i < n; ++i) {
            double t = (n == 1 ? 0.0 : static_cast<double>(i) / (n - 1));
            double jitterX = rnd.next(-750, 750) / 1000.0;
            double jitterY = rnd.next(-750, 750) / 1000.0;
            points.push_back(clampPoint(t * X + jitterX, (1.0 - t) * Y + jitterY, X, Y));
        }
    } else if (mode == 3) {
        int n = rnd.next(4, 14);
        for (int i = 0; i < n; ++i) {
            int side = rnd.next(0, 3);
            if (side == 0) points.push_back({0.0, coord(Y)});
            if (side == 1) points.push_back({static_cast<double>(X), coord(Y)});
            if (side == 2) points.push_back({coord(X), 0.0});
            if (side == 3) points.push_back({coord(X), static_cast<double>(Y)});
        }
    } else {
        int n = rnd.next(6, 18);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                points.push_back({coord(X), coord(Y)});
            } else {
                points.push_back({rnd.next(0, X * 1000) / 1000.0,
                                  rnd.next(0, Y * 1000) / 1000.0});
            }
        }
    }

    shuffle(points.begin(), points.end());

    println(X, Y);
    println(static_cast<int>(points.size()));
    cout << fixed << setprecision(3);
    for (const Point& p : points) {
        cout << p.x << ' ' << p.y << '\n';
    }

    return 0;
}
