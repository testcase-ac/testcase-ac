#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

long long cross(const Point& a, const Point& b, const Point& c) {
    return 1LL * (b.x - a.x) * (c.y - a.y) - 1LL * (b.y - a.y) * (c.x - a.x);
}

int clampCoord(int v) {
    return max(0, min(10000, v));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<Point> p(3);

    if (mode == 0) {
        int x = rnd.next(0, 12);
        int y = rnd.next(0, 12);
        int w = rnd.next(1, 12);
        int h = rnd.next(1, 12);
        p = {{x, y}, {clampCoord(x + w), y}, {x, clampCoord(y + h)}};
    } else if (mode == 1) {
        int baseX = rnd.next(0, 9990);
        int baseY = rnd.next(0, 9990);
        int len = rnd.next(2, 10);
        int height = rnd.next(1, 3);
        p = {{baseX, baseY}, {baseX + len, baseY}, {baseX + rnd.next(0, len), baseY + height}};
    } else if (mode == 2) {
        int high = rnd.next(9985, 10000);
        int low = rnd.next(0, 15);
        p = {{low, low}, {high, rnd.next(0, 25)}, {rnd.next(0, 25), high}};
    } else if (mode == 3) {
        int x1 = rnd.next(0, 30);
        int y1 = rnd.next(0, 30);
        int dx1 = rnd.next(1, 15);
        int dy1 = rnd.next(1, 15);
        int dx2 = rnd.next(1, 15);
        int dy2 = rnd.next(1, 15);
        p = {{x1, y1}, {x1 + dx1, y1 + dy1}, {x1 + dx2, y1 + dy2}};
        if (cross(p[0], p[1], p[2]) == 0) p[2].y = clampCoord(p[2].y + 1);
    } else if (mode == 4) {
        int x = rnd.next(0, 9995);
        int y = rnd.next(0, 9995);
        int span = rnd.next(1, 5);
        p = {{x, y}, {x + span, y + rnd.next(0, span)}, {x + rnd.next(0, span), y + span}};
    } else {
        do {
            for (Point& q : p) {
                q.x = rnd.next(0, 10000);
                q.y = rnd.next(0, 10000);
            }
        } while (cross(p[0], p[1], p[2]) == 0);
    }

    if (cross(p[0], p[1], p[2]) == 0) {
        p[2].y = p[2].y == 10000 ? p[2].y - 1 : p[2].y + 1;
    }

    shuffle(p.begin(), p.end());

    println(p[0].x, p[0].y, p[1].x, p[1].y, p[2].x, p[2].y);
    return 0;
}
