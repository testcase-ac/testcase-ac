#include "testlib.h"

#include <algorithm>
#include <array>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

void translateInside(vector<Point>& p) {
    int minX = p[0].first, maxX = p[0].first;
    int minY = p[0].second, maxY = p[0].second;
    for (const auto& [x, y] : p) {
        minX = min(minX, x);
        maxX = max(maxX, x);
        minY = min(minY, y);
        maxY = max(maxY, y);
    }

    int addX = rnd.next(-10000 - minX, 10000 - maxX);
    int addY = rnd.next(-10000 - minY, 10000 - maxY);
    for (auto& [x, y] : p) {
        x += addX;
        y += addY;
    }
}

long long cross(const Point& a, const Point& b, const Point& c) {
    long long ux = b.first - a.first;
    long long uy = b.second - a.second;
    long long vx = c.first - b.first;
    long long vy = c.second - b.second;
    return ux * vy - uy * vx;
}

bool isStrictlyConvex(const vector<Point>& p) {
    long long first = cross(p[0], p[1], p[2]);
    if (first == 0) {
        return false;
    }
    for (int i = 1; i < 4; ++i) {
        long long turn = cross(p[i], p[(i + 1) % 4], p[(i + 2) % 4]);
        if (turn == 0 || (turn > 0) != (first > 0)) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<Point> p;

    if (mode == 0) {
        int w = rnd.next(1, 400);
        int h = rnd.next(1, 400);
        p = {{0, 0}, {w, 0}, {w, h}, {0, h}};
    } else if (mode == 1) {
        Point u = {rnd.next(1, 250), rnd.next(-80, 80)};
        Point v = {rnd.next(-80, 80), rnd.next(1, 250)};
        while (u.first * v.second - u.second * v.first == 0) {
            v = {rnd.next(-80, 80), rnd.next(1, 250)};
        }
        p = {{0, 0}, u, {u.first + v.first, u.second + v.second}, v};
    } else if (mode == 2) {
        int bottom = rnd.next(4, 500);
        int top = rnd.next(1, 500);
        int h = rnd.next(1, 300);
        int leftShift = rnd.next(-200, 200);
        p = {{0, 0}, {bottom, 0}, {leftShift + top, h}, {leftShift, h}};
    } else if (mode == 3) {
        int up = rnd.next(1, 350);
        int right = rnd.next(1, 350);
        int down = rnd.next(1, 350);
        int left = rnd.next(1, 350);
        p = {{0, up}, {right, 0}, {0, -down}, {-left, 0}};
    } else {
        int w = rnd.next(2, 900);
        int upperRightX = w + rnd.next(-3, 3);
        int upperLeftX = rnd.next(-3, 3);
        int upperY = rnd.next(1, 4);
        p = {{0, 0}, {w, 0}, {upperRightX, upperY}, {upperLeftX, upperY + rnd.next(1, 4)}};
    }

    if (rnd.next(2) == 1) {
        reverse(p.begin(), p.end());
    }
    translateInside(p);
    ensure(isStrictlyConvex(p));

    for (int i = 0; i < 4; ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << p[i].first << ' ' << p[i].second;
    }
    cout << '\n';

    return 0;
}
