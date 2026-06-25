#include "testlib.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Point {
    long double x;
    long double y;
};

struct Case {
    long double bx;
    long double cx;
    long double cy;
    long double dx;
    long double dy;
    int decimals;
};

long double cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool isConvex(const Case& tc) {
    vector<Point> p = {{0.0L, 0.0L}, {tc.bx, 0.0L}, {tc.cx, tc.cy}, {tc.dx, tc.dy}};
    for (int i = 0; i < 4; ++i) {
        if (cross(p[i], p[(i + 1) % 4], p[(i + 2) % 4]) <= 0.0L) {
            return false;
        }
    }
    return true;
}

string formatDecimal(long double value, int decimals) {
    if (decimals == 0) {
        return to_string(static_cast<long long>(llround(value)));
    }

    ostringstream out;
    out << fixed << setprecision(decimals) << static_cast<double>(value);
    string s = out.str();
    while (s.size() > 1 && s.back() == '0') {
        s.pop_back();
    }
    if (!s.empty() && s.back() == '.') {
        s.pop_back();
    }
    return s;
}

Case randomIntegerCase() {
    Case tc{};
    tc.decimals = 0;
    tc.bx = rnd.next(1, 300);
    tc.cx = rnd.next(0, 450);
    tc.cy = rnd.next(1, 300);
    tc.dx = rnd.next(-200, static_cast<int>(tc.cx) - 1);
    tc.dy = rnd.next(1, 350);
    return tc;
}

Case randomDecimalCase() {
    int scale = rnd.any(vector<int>{10, 100, 1000});
    Case tc{};
    tc.decimals = scale == 10 ? 1 : (scale == 100 ? 2 : 3);
    tc.bx = rnd.next(10, 2500) / static_cast<long double>(scale);
    tc.cx = rnd.next(-500, 3500) / static_cast<long double>(scale);
    tc.cy = rnd.next(10, 2500) / static_cast<long double>(scale);
    tc.dx = rnd.next(-2000, 500) / static_cast<long double>(scale);
    tc.dy = rnd.next(10, 3000) / static_cast<long double>(scale);
    return tc;
}

Case randomRectangleLikeCase() {
    Case tc{};
    tc.decimals = rnd.next(0, 1);
    tc.bx = rnd.next(1, 500);
    tc.cx = tc.bx + rnd.next(-20, 80);
    tc.cy = rnd.next(1, 500);
    tc.dx = rnd.next(-80, 20);
    tc.dy = tc.cy + rnd.next(-20, 80);
    if (tc.dy <= 0) {
        tc.dy = 1;
    }
    return tc;
}

Case randomLargeCase() {
    Case tc{};
    tc.decimals = 0;
    tc.bx = rnd.next(100000, 1000000);
    tc.cx = rnd.next(0, 1000000);
    tc.cy = rnd.next(100000, 1000000);
    tc.dx = rnd.next(-1000000, 0);
    tc.dy = rnd.next(100000, 1000000);
    return tc;
}

Case makeCase() {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        int mode = rnd.next(0, 3);
        Case tc = mode == 0 ? randomIntegerCase()
                            : mode == 1 ? randomDecimalCase()
                                        : mode == 2 ? randomRectangleLikeCase()
                                                    : randomLargeCase();
        if (isConvex(tc)) {
            return tc;
        }
    }

    return {1.0L, 1.0L, 1.0L, 0.0L, 1.0L, 0};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);
    for (int i = 0; i < t; ++i) {
        Case tc = makeCase();
        cout << formatDecimal(tc.bx, tc.decimals) << ' '
             << formatDecimal(tc.cx, tc.decimals) << ' '
             << formatDecimal(tc.cy, tc.decimals) << ' '
             << formatDecimal(tc.dx, tc.decimals) << ' '
             << formatDecimal(tc.dy, tc.decimals) << '\n';
    }

    return 0;
}
