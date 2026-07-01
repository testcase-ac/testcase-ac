#include "testlib.h"

#include <cmath>
#include <string>
#include <vector>
using namespace std;

struct Point {
    long long x;
    long long y;
};

__int128 cross(const Point& a, const Point& b, const Point& c) {
    return (__int128)(b.x - a.x) * (c.y - a.y) -
           (__int128)(b.y - a.y) * (c.x - a.x);
}

long double polygonArea2(const vector<Point>& p) {
    __int128 sum = 0;
    int n = (int)p.size();
    for (int i = 0; i < n; ++i) {
        const Point& a = p[i];
        const Point& b = p[(i + 1) % n];
        sum += (__int128)a.x * b.y - (__int128)a.y * b.x;
    }
    long double value = (long double)sum;
    return fabsl(value);
}

long double triangleArea2(const Point& a, const Point& b, const Point& c) {
    __int128 value = cross(a, b, c);
    if (value < 0) value = -value;
    return (long double)value;
}

void ensureStrictlyConvexInOrder(const vector<Point>& p) {
    int n = (int)p.size();
    __int128 orientation = 0;
    for (int i = 0; i < n; ++i) {
        orientation += (__int128)p[i].x * p[(i + 1) % n].y -
                       (__int128)p[i].y * p[(i + 1) % n].x;
    }
    ensuref(orientation != 0, "polygon area must be positive");

    int sign = orientation > 0 ? 1 : -1;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        for (int k = 0; k < n; ++k) {
            if (k == i || k == j) continue;
            __int128 turn = cross(p[i], p[j], p[k]);
            ensuref(turn != 0,
                    "vertex %d lies on edge line %d-%d",
                    k + 1, i + 1, j + 1);
            ensuref((turn > 0 ? 1 : -1) == sign,
                    "vertex %d is on the wrong side of edge %d-%d",
                    k + 1, i + 1, j + 1);
        }
    }
}

long double removedFractionAtS2(const vector<Point>& p) {
    int n = (int)p.size();
    long double area2 = polygonArea2(p);
    long double removed2 = 0.0L;
    for (int i = 0; i < n; ++i) {
        const Point& prev = p[(i + n - 1) % n];
        const Point& cur = p[i];
        const Point& next = p[(i + 1) % n];
        removed2 += triangleArea2(prev, cur, next) / 4.0L;
    }
    return removed2 / area2;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string aToken = inf.readToken("0\\.[0-9]{1,7}", "a");
    long double a = stold(aToken);
    ensuref(a >= 0.25L && a < 1.0L,
            "a must satisfy 0.25 <= a < 1, got %s",
            aToken.c_str());
    inf.readSpace();
    int n = inf.readInt(3, 100, "N");
    inf.readEoln();

    vector<Point> p(n);
    for (int i = 0; i < n; ++i) {
        p[i].x = inf.readLong(0LL, 100000000LL, "x_i");
        inf.readSpace();
        p[i].y = inf.readLong(0LL, 100000000LL, "y_i");
        inf.readEoln();
    }

    ensureStrictlyConvexInOrder(p);

    long double removedAt2 = removedFractionAtS2(p);
    long double remainingAt2 = 1.0L - removedAt2;
    long double remainingAt1000 = 1.0L - removedAt2 * 4.0L / (1000.0L * 1000.0L);
    const long double eps = 1e-12L;
    ensuref(a + eps >= remainingAt2,
            "no solution with s >= 2: a=%.12Lf, minimum remaining fraction=%.12Lf",
            a, remainingAt2);
    ensuref(a <= remainingAt1000 + eps,
            "no solution with s <= 1000: a=%.12Lf, maximum remaining fraction=%.12Lf",
            a, remainingAt1000);

    inf.readEof();
}
