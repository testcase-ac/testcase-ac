#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>

using namespace std;

using Point = array<int, 3>;
using Robot = array<int, 6>;

const int MIN_COORD = -1000;
const int MAX_COORD = 1000;

int clampCoord(int value) {
    return max(MIN_COORD, min(MAX_COORD, value));
}

Point randomPoint(int lo = MIN_COORD, int hi = MAX_COORD) {
    return Point{rnd.next(lo, hi), rnd.next(lo, hi), rnd.next(lo, hi)};
}

Point offsetPoint(Point p, int axis, int delta) {
    p[axis] = clampCoord(p[axis] + delta);
    return p;
}

Robot robot(Point start, Point finish) {
    return Robot{start[0], start[1], start[2], finish[0], finish[1], finish[2]};
}

bool validPair(const Robot& a, const Robot& b) {
    Point aStart{a[0], a[1], a[2]};
    Point bStart{b[0], b[1], b[2]};
    Point aFinish{a[3], a[4], a[5]};
    Point bFinish{b[3], b[4], b[5]};
    return aStart != bStart && aFinish != bFinish;
}

Point distinctFrom(Point forbidden, int radius) {
    Point p;
    do {
        p = randomPoint(-radius, radius);
    } while (p == forbidden);
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    Robot a{};
    Robot b{};

    if (mode == 0) {
        Point aStart = randomPoint(-8, 8);
        Point bStart = distinctFrom(aStart, 8);
        Point aFinish = randomPoint(-8, 8);
        Point bFinish = distinctFrom(aFinish, 8);
        a = robot(aStart, aFinish);
        b = robot(bStart, bFinish);
    } else if (mode == 1) {
        vector<int> edges = {MIN_COORD, MIN_COORD + 1, -999, 999, MAX_COORD - 1, MAX_COORD};
        Point aStart{rnd.any(edges), rnd.any(edges), rnd.any(edges)};
        Point bStart{rnd.any(edges), rnd.any(edges), rnd.any(edges)};
        Point aFinish{rnd.any(edges), rnd.any(edges), rnd.any(edges)};
        Point bFinish{rnd.any(edges), rnd.any(edges), rnd.any(edges)};
        a = robot(aStart, aFinish);
        b = robot(bStart, bFinish);
    } else if (mode == 2) {
        int axis = rnd.next(0, 2);
        int left = rnd.next(-20, -2);
        int right = rnd.next(2, 20);
        Point base = randomPoint(-5, 5);
        Point aStart = base;
        Point bStart = base;
        Point aFinish = base;
        Point bFinish = base;
        aStart[axis] = left;
        bStart[axis] = right;
        aFinish[axis] = right;
        bFinish[axis] = left;
        a = robot(aStart, aFinish);
        b = robot(bStart, bFinish);
    } else if (mode == 3) {
        Point aStart = randomPoint(-30, 30);
        Point bStart = distinctFrom(aStart, 30);
        a = robot(aStart, bStart);
        b = robot(bStart, aStart);
    } else if (mode == 4) {
        int axis = rnd.next(0, 2);
        int otherAxis = (axis + rnd.next(1, 2)) % 3;
        Point meet = randomPoint(-20, 20);
        Point aStart = offsetPoint(meet, axis, -rnd.next(1, 8));
        Point bStart = offsetPoint(meet, axis, rnd.next(1, 8));
        Point aFinish = offsetPoint(meet, otherAxis, rnd.next(1, 8));
        Point bFinish = offsetPoint(meet, otherAxis, -rnd.next(1, 8));
        a = robot(aStart, aFinish);
        b = robot(bStart, bFinish);
    } else {
        int axis = rnd.next(0, 2);
        Point aStart = randomPoint(-40, 40);
        Point bStart = offsetPoint(aStart, axis, rnd.any(vector<int>{-1, 1}));
        Point aFinish = offsetPoint(aStart, axis, rnd.next(2, 12));
        Point bFinish = offsetPoint(aStart, axis, -rnd.next(2, 12));
        a = robot(aStart, aFinish);
        b = robot(bStart, bFinish);
    }

    while (!validPair(a, b)) {
        Point bStart{b[0], b[1], b[2]};
        Point bFinish{b[3], b[4], b[5]};
        int axis = rnd.next(0, 2);
        bStart = offsetPoint(bStart, axis, rnd.any(vector<int>{-1, 1}));
        bFinish = offsetPoint(bFinish, (axis + 1) % 3, rnd.any(vector<int>{-1, 1}));
        b = robot(bStart, bFinish);
    }

    println(a[0], a[1], a[2], a[3], a[4], a[5]);
    println(b[0], b[1], b[2], b[3], b[4], b[5]);
    return 0;
}
