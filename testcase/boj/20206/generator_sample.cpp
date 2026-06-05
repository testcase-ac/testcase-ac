#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <vector>

using namespace std;

struct Rect {
    int x1;
    int x2;
    int y1;
    int y2;
};

struct Line {
    int a;
    int b;
    int c;
};

Rect smallRect(bool needsInterior) {
    int minSide = needsInterior ? 2 : 1;
    int x1 = rnd.next(-20, 10);
    int y1 = rnd.next(-20, 10);
    int x2 = x1 + rnd.next(minSide, 30);
    int y2 = y1 + rnd.next(minSide, 30);
    return {x1, x2, y1, y2};
}

Rect variedRect(bool needsInterior) {
    if (rnd.next(10) == 0) {
        int minSide = needsInterior ? 2 : 1;
        int x1 = rnd.next(-100000, 99999 - minSide);
        int x2 = rnd.next(x1 + minSide, 100000);
        int y1 = rnd.next(-100000, 99999 - minSide);
        int y2 = rnd.next(y1 + minSide, 100000);
        return {x1, x2, y1, y2};
    }
    return smallRect(needsInterior);
}

Line normalizedLineThrough(int x1, int y1, int x2, int y2) {
    int a = y1 - y2;
    int b = x2 - x1;
    int c = -(a * x1 + b * y1);

    int g = std::abs(a);
    g = std::gcd(g, std::abs(b));
    g = std::gcd(g, std::abs(c));
    if (g > 1) {
        a /= g;
        b /= g;
        c /= g;
    }
    if (a < 0 || (a == 0 && b < 0)) {
        a = -a;
        b = -b;
        c = -c;
    }
    return {a, b, c};
}

Line randomLine() {
    int a = 0;
    int b = 0;
    while (a == 0 && b == 0) {
        a = rnd.next(-10000, 10000);
        b = rnd.next(-10000, 10000);
    }
    int c = rnd.next(-100000, 100000);
    return {a, b, c};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    Rect r = (mode == 3 || mode == 7) ? smallRect(true) : variedRect(false);
    if (mode == 5) r = smallRect(false);
    Line line = randomLine();

    if (mode == 1) {
        vector<int> xs = {r.x1, r.x2};
        if (r.x1 + 1 <= r.x2 - 1) xs.push_back(rnd.next(r.x1 + 1, r.x2 - 1));
        int x = rnd.any(xs);
        line = {1, 0, -x};
    } else if (mode == 2) {
        vector<int> ys = {r.y1, r.y2};
        if (r.y1 + 1 <= r.y2 - 1) ys.push_back(rnd.next(r.y1 + 1, r.y2 - 1));
        int y = rnd.any(ys);
        line = {0, 1, -y};
    } else if (mode == 3) {
        int x1 = rnd.next(r.x1 + 1, r.x2 - 1);
        int y1 = rnd.next(r.y1 + 1, r.y2 - 1);
        int x2 = x1;
        int y2 = y1;
        while (x1 == x2 && y1 == y2) {
            x2 = rnd.next(r.x1 + 1, r.x2 - 1);
            y2 = rnd.next(r.y1 + 1, r.y2 - 1);
        }
        line = normalizedLineThrough(x1, y1, x2, y2);
    } else if (mode == 4) {
        int side = rnd.next(4);
        if (side == 0) line = {1, 0, -r.x1};
        if (side == 1) line = {1, 0, -r.x2};
        if (side == 2) line = {0, 1, -r.y1};
        if (side == 3) line = {0, 1, -r.y2};
    } else if (mode == 5) {
        vector<pair<int, int>> corners = {
            {r.x1, r.y1},
            {r.x1, r.y2},
            {r.x2, r.y1},
            {r.x2, r.y2},
        };
        auto p = rnd.any(corners);
        int dx = rnd.next(1, 20);
        int dy = rnd.next(1, 20);
        line = normalizedLineThrough(p.first, p.second, p.first + dx, p.second + dy);
    } else if (mode == 6) {
        int a = rnd.next(1, 10000);
        int b = rnd.next(1, 10000);
        if (rnd.next(2)) a = -a;
        if (rnd.next(2)) b = -b;
        int c = rnd.any(vector<int>{-100000, 100000, rnd.next(-100000, 100000)});
        line = {a, b, c};
    } else if (mode == 7) {
        vector<pair<int, int>> points = {
            {r.x1 + 1, r.y1 + 1},
            {r.x1 + 1, r.y2 - 1},
            {r.x2 - 1, r.y1 + 1},
            {r.x2 - 1, r.y2 - 1},
        };
        auto p1 = rnd.any(points);
        auto p2 = rnd.any(points);
        while (p1 == p2) p2 = rnd.any(points);
        line = normalizedLineThrough(p1.first, p1.second, p2.first, p2.second);
    }

    println(line.a, line.b, line.c);
    println(r.x1, r.x2, r.y1, r.y2);
    return 0;
}
