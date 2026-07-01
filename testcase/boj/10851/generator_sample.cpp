#include "testlib.h"

#include <cmath>
#include <iomanip>
#include <iostream>
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

bool isStrictlyConvexInOrder(const vector<Point>& p) {
    int n = (int)p.size();
    __int128 orientation = 0;
    for (int i = 0; i < n; ++i) {
        orientation += (__int128)p[i].x * p[(i + 1) % n].y -
                       (__int128)p[i].y * p[(i + 1) % n].x;
    }
    if (orientation == 0) return false;

    int sign = orientation > 0 ? 1 : -1;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        for (int k = 0; k < n; ++k) {
            if (k == i || k == j) continue;
            __int128 turn = cross(p[i], p[j], p[k]);
            if (turn == 0 || (turn > 0 ? 1 : -1) != sign) return false;
        }
    }
    return true;
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

vector<Point> makePolygon() {
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        int w = rnd.next(1, 80);
        int h = rnd.next(1, 80);
        int ox = rnd.next(0, 20);
        int oy = rnd.next(0, 20);
        return {{ox, oy}, {ox + w, oy}, {ox + w, oy + h}, {ox, oy + h}};
    }

    if (mode == 1) {
        int ax = rnd.next(1, 120);
        int by = rnd.next(1, 120);
        int ox = rnd.next(0, 20);
        int oy = rnd.next(0, 20);
        return {{ox, oy}, {ox + ax, oy}, {ox, oy + by}};
    }

    int n = rnd.next(5, 14);
    for (int attempt = 0; attempt < 200; ++attempt) {
        long double cx = rnd.next(250, 900);
        long double cy = rnd.next(250, 900);
        long double rx = rnd.next(20, 220);
        long double ry = rnd.next(20, 220);
        long double phase = rnd.next(0.0, 6.2831853071795864769);
        long double jitter = rnd.next(0.0, 0.18);

        vector<Point> p;
        for (int i = 0; i < n; ++i) {
            long double base = phase + 2.0L * 3.1415926535897932385L * i / n;
            long double angle = base + rnd.next((double)-jitter, (double)jitter);
            long long x = llround(cx + rx * cosl(angle));
            long long y = llround(cy + ry * sinl(angle));
            p.push_back({x, y});
        }
        if (isStrictlyConvexInOrder(p)) return p;
    }

    return {{0, 0}, {7, 0}, {11, 4}, {8, 9}, {2, 10}, {0, 4}};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> p = makePolygon();
    long double removedAt2 = removedFractionAtS2(p);
    long double minA = 1.0L - removedAt2;
    long double maxA = 1.0L - removedAt2 * 4.0L / (1000.0L * 1000.0L);

    long long lo = (long long)ceill(minA * 10000000.0L + 1e-9L);
    long long hi = (long long)floorl(maxA * 10000000.0L - 1e-9L);
    lo = max(lo, 2500000LL);
    hi = min(hi, 9999999LL);
    if (lo > hi) lo = hi = 2500000LL;

    long long scaledA = rnd.next(lo, hi);
    cout << "0." << setw(7) << setfill('0') << scaledA << " " << p.size() << "\n";
    for (const Point& point : p) {
        cout << point.x << " " << point.y << "\n";
    }

    return 0;
}
