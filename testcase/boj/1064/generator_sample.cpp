#include "testlib.h"
#include <algorithm>
#include <array>
#include <vector>
using namespace std;

struct Point {
    int x;
    int y;
};

bool samePoint(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

long long cross(const Point& a, const Point& b, const Point& c) {
    return 1LL * (b.x - a.x) * (c.y - a.y) - 1LL * (b.y - a.y) * (c.x - a.x);
}

bool valid(const array<Point, 3>& p) {
    return !samePoint(p[0], p[1]) && !samePoint(p[0], p[2]) && !samePoint(p[1], p[2]);
}

Point randomPoint(int lo, int hi) {
    return {rnd.next(lo, hi), rnd.next(lo, hi)};
}

array<Point, 3> randomDistinctPoints(int lo, int hi) {
    array<Point, 3> p;
    do {
        p = {randomPoint(lo, hi), randomPoint(lo, hi), randomPoint(lo, hi)};
    } while (!valid(p));
    return p;
}

array<Point, 3> makeAxisAligned() {
    int x = rnd.next(-20, 20);
    int y = rnd.next(-20, 20);
    int dx = rnd.next(1, 25);
    int dy = rnd.next(1, 25);
    return {{{x, y}, {x + dx, y}, {x, y + dy}}};
}

array<Point, 3> makeCollinear() {
    Point base = randomPoint(-30, 30);
    Point dir;
    do {
        dir = {rnd.next(-10, 10), rnd.next(-10, 10)};
    } while (dir.x == 0 && dir.y == 0);

    vector<int> steps = {-3, -2, -1, 1, 2, 3};
    shuffle(steps.begin(), steps.end());
    return {{{base.x + steps[0] * dir.x, base.y + steps[0] * dir.y},
             {base.x + steps[1] * dir.x, base.y + steps[1] * dir.y},
             {base.x + steps[2] * dir.x, base.y + steps[2] * dir.y}}};
}

array<Point, 3> makeNearCollinear() {
    int x = rnd.next(-30, 30);
    int y = rnd.next(-30, 30);
    int gap = rnd.next(1, 40);
    int wiggle = rnd.next(1, 2);
    return {{{x, y}, {x + gap, y}, {x + 2 * gap, y + wiggle}}};
}

array<Point, 3> makeBoundary() {
    vector<Point> corners = {{-5000, -5000}, {-5000, 5000}, {5000, -5000}, {5000, 5000}};
    shuffle(corners.begin(), corners.end());
    array<Point, 3> p = {corners[0], corners[1], corners[2]};
    if (rnd.next(2) == 0) {
        p[rnd.next(3)] = {rnd.next(-5000, 5000), rnd.next(-5000, 5000)};
    }
    if (!valid(p)) {
        p = {Point{-5000, -5000}, Point{5000, 5000}, Point{5000, rnd.next(4997, 4999)}};
    }
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    array<Point, 3> p;
    int mode = rnd.next(5);
    if (mode == 0) {
        p = randomDistinctPoints(-50, 50);
    } else if (mode == 1) {
        p = makeAxisAligned();
    } else if (mode == 2) {
        p = makeCollinear();
    } else if (mode == 3) {
        p = makeNearCollinear();
    } else {
        p = makeBoundary();
    }

    if (cross(p[0], p[1], p[2]) != 0 && rnd.next(3) == 0) {
        shuffle(p.begin(), p.end());
    }

    println(p[0].x, p[0].y, p[1].x, p[1].y, p[2].x, p[2].y);
    return 0;
}
