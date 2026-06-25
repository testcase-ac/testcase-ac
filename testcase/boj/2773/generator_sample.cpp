#include "testlib.h"
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

struct Point {
    double x;
    double y;
};

double distanceFromLine(Point p, Point a, Point b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double cross = dx * (p.y - a.y) - dy * (p.x - a.x);
    return fabs(cross) / hypot(dx, dy);
}

bool validTriangle(const array<Point, 3>& p) {
    return distanceFromLine(p[0], p[1], p[2]) >= 1.0 &&
           distanceFromLine(p[1], p[2], p[0]) >= 1.0 &&
           distanceFromLine(p[2], p[0], p[1]) >= 1.0;
}

double maybeFractional(int value) {
    if (rnd.next(3) == 0) {
        return value + rnd.any(vector<double>{0.125, 0.25, 0.5, 0.75, 0.875});
    }
    return value;
}

array<Point, 3> axisTriangle() {
    int x0 = rnd.next(-20, 20);
    int y0 = rnd.next(-20, 20);
    int width = rnd.next(2, 40);
    int height = rnd.next(2, 40);
    int sx = rnd.next(2) ? 1 : -1;
    int sy = rnd.next(2) ? 1 : -1;

    array<Point, 3> p = {
        Point{maybeFractional(x0), maybeFractional(y0)},
        Point{maybeFractional(x0 + sx * width), maybeFractional(y0)},
        Point{maybeFractional(x0), maybeFractional(y0 + sy * height)},
    };
    shuffle(p.begin(), p.end());
    return p;
}

array<Point, 3> generalTriangle() {
    while (true) {
        int scale = rnd.any(vector<int>{10, 100, 1000, 10000});
        array<Point, 3> p;
        for (Point& q : p) {
            q.x = maybeFractional(rnd.next(-scale, scale));
            q.y = maybeFractional(rnd.next(-scale, scale));
        }
        if (validTriangle(p)) {
            return p;
        }
    }
}

array<Point, 3> shallowValidTriangle() {
    double base = rnd.next(20, 80);
    double height = rnd.next(100, 250) / 100.0;
    double skew = rnd.next(-20, 20) / 10.0;
    double ox = rnd.next(-30, 30);
    double oy = rnd.next(-30, 30);

    array<Point, 3> p = {
        Point{ox, oy},
        Point{ox + base, oy},
        Point{ox + base / 2.0 + skew, oy + (rnd.next(2) ? height : -height)},
    };
    shuffle(p.begin(), p.end());
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 6);
    println(t);
    cout << fixed << setprecision(3);

    for (int tc = 0; tc < t; ++tc) {
        array<Point, 3> p;
        int mode = rnd.next(3);
        if (mode == 0) {
            p = axisTriangle();
        } else if (mode == 1) {
            p = shallowValidTriangle();
        } else {
            p = generalTriangle();
        }

        for (const Point& q : p) {
            cout << q.x << ' ' << q.y << '\n';
        }
    }

    return 0;
}
