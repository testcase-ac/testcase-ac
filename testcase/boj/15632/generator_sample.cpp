#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

struct Circle {
    int x;
    int y;
    int r;
};

static Circle randomCircle(int minR, int maxR) {
    int r = rnd.next(minR, maxR);
    int x = rnd.next(r, 100 - r);
    int y = rnd.next(r, 100 - r);
    return {x, y, r};
}

static Circle nearCircle(const Circle& base, int minR, int maxR, int spread) {
    for (int attempt = 0; attempt < 200; ++attempt) {
        int r = rnd.next(minR, maxR);
        int x = base.x + rnd.next(-spread, spread);
        int y = base.y + rnd.next(-spread, spread);
        x = max(r, min(100 - r, x));
        y = max(r, min(100 - r, y));
        return {x, y, r};
    }
    return randomCircle(minR, maxR);
}

static Circle boundaryCircle() {
    int r = rnd.next(1, 35);
    int side = rnd.next(4);
    int x = rnd.next(r, 100 - r);
    int y = rnd.next(r, 100 - r);

    if (side == 0) x = r;
    if (side == 1) x = 100 - r;
    if (side == 2) y = r;
    if (side == 3) y = 100 - r;

    return {x, y, r};
}

static Circle containedCircle(const Circle& outer) {
    int r = rnd.next(1, outer.r);
    int slack = outer.r - r;
    int x = outer.x + rnd.next(-slack, slack);
    int y = outer.y + rnd.next(-slack, slack);
    x = max(r, min(100 - r, x));
    y = max(r, min(100 - r, y));
    return {x, y, r};
}

static Circle shiftedCircle(const Circle& base, int r, int distance) {
    double angle = rnd.next(0.0, 2.0 * acos(-1.0));
    int dx = static_cast<int>(round(cos(angle) * distance));
    int dy = static_cast<int>(round(sin(angle) * distance));
    int x = max(r, min(100 - r, base.x + dx));
    int y = max(r, min(100 - r, base.y + dy));
    return {x, y, r};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Circle> circles;
    int mode = rnd.next(5);

    if (mode == 0) {
        Circle center = randomCircle(8, 28);
        circles.push_back(center);
        circles.push_back(nearCircle(center, 1, 24, center.r + 8));
        circles.push_back(nearCircle(center, 1, 24, center.r + 8));
    } else if (mode == 1) {
        Circle outer = randomCircle(20, 50);
        circles.push_back(outer);
        circles.push_back(containedCircle(outer));
        circles.push_back(containedCircle(outer));
    } else if (mode == 2) {
        Circle first = randomCircle(4, 25);
        int r = rnd.next(4, 25);
        int distance = max(1, first.r + r + rnd.next(-2, 2));
        circles.push_back(first);
        circles.push_back(shiftedCircle(first, r, distance));
        circles.push_back(randomCircle(1, 25));
    } else if (mode == 3) {
        for (int i = 0; i < 3; ++i) {
            circles.push_back(randomCircle(1, 12));
        }
    } else {
        circles.push_back(boundaryCircle());
        circles.push_back(boundaryCircle());
        circles.push_back(randomCircle(1, 35));
    }

    shuffle(circles.begin(), circles.end());
    for (const Circle& c : circles) {
        println(c.x, c.y, c.r);
    }

    return 0;
}
