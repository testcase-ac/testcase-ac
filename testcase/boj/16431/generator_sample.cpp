#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

using namespace std;

struct Point {
    int r;
    int c;
};

const int kMinCoord = 1;
const int kMaxCoord = 1000;

int clampCoord(int x) {
    return max(kMinCoord, min(kMaxCoord, x));
}

bool same(Point a, Point b) {
    return a.r == b.r && a.c == b.c;
}

int bessieDistance(Point cow, Point john) {
    return max(abs(cow.r - john.r), abs(cow.c - john.c));
}

int daisyDistance(Point cow, Point john) {
    return abs(cow.r - john.r) + abs(cow.c - john.c);
}

Point randomPoint() {
    return {rnd.next(kMinCoord, kMaxCoord), rnd.next(kMinCoord, kMaxCoord)};
}

Point randomPointDifferentFrom(Point p) {
    Point q = randomPoint();
    while (same(q, p)) {
        q = randomPoint();
    }
    return q;
}

Point pointAtOffset(Point origin, int dr, int dc) {
    return {clampCoord(origin.r + dr), clampCoord(origin.c + dc)};
}

Point randomChebyshevPoint(Point origin, int distance) {
    vector<Point> candidates;
    for (int dr = -distance; dr <= distance; ++dr) {
        for (int dc = -distance; dc <= distance; ++dc) {
            if (max(abs(dr), abs(dc)) != distance) {
                continue;
            }
            Point p = pointAtOffset(origin, dr, dc);
            if (!same(p, origin) && bessieDistance(p, origin) == distance) {
                candidates.push_back(p);
            }
        }
    }
    return rnd.any(candidates);
}

Point randomManhattanPoint(Point origin, int distance) {
    vector<Point> candidates;
    for (int dr = -distance; dr <= distance; ++dr) {
        int dcAbs = distance - abs(dr);
        for (int sign : {-1, 1}) {
            int dc = sign * dcAbs;
            Point p = pointAtOffset(origin, dr, dc);
            if (!same(p, origin) && daisyDistance(p, origin) == distance) {
                candidates.push_back(p);
            }
        }
    }
    return rnd.any(candidates);
}

Point randomInteriorJohn(int margin) {
    return {rnd.next(kMinCoord + margin, kMaxCoord - margin),
            rnd.next(kMinCoord + margin, kMaxCoord - margin)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    Point bessie;
    Point daisy;
    Point john;

    int mode = rnd.next(0, 6);
    if (mode == 0) {
        john = randomInteriorJohn(30);
        int bDist = rnd.next(1, 12);
        int dDist = rnd.next(bDist + 1, bDist + 20);
        bessie = randomChebyshevPoint(john, bDist);
        daisy = randomManhattanPoint(john, dDist);
    } else if (mode == 1) {
        john = randomInteriorJohn(30);
        int dDist = rnd.next(1, 12);
        int bDist = rnd.next(dDist + 1, dDist + 20);
        bessie = randomChebyshevPoint(john, bDist);
        daisy = randomManhattanPoint(john, dDist);
    } else if (mode == 2) {
        john = randomInteriorJohn(30);
        int dist = rnd.next(1, 20);
        bessie = randomChebyshevPoint(john, dist);
        daisy = randomManhattanPoint(john, dist);
    } else if (mode == 3) {
        john = rnd.any(vector<Point>{{1, 1}, {1, 1000}, {1000, 1}, {1000, 1000}});
        bessie = randomPointDifferentFrom(john);
        daisy = randomPointDifferentFrom(john);
    } else if (mode == 4) {
        john = randomInteriorJohn(50);
        int diagonal = rnd.next(1, 40);
        int axis = rnd.next(1, 80);
        bessie = pointAtOffset(john, rnd.any(vector<int>{-diagonal, diagonal}),
                               rnd.any(vector<int>{-diagonal, diagonal}));
        daisy = pointAtOffset(john, rnd.any(vector<int>{-axis, axis}) * rnd.next(0, 1),
                              rnd.any(vector<int>{-axis, axis}) * rnd.next(0, 1));
        if (same(daisy, john)) {
            daisy = pointAtOffset(john, axis, 0);
        }
    } else {
        john = randomInteriorJohn(10);
        bessie = randomPointDifferentFrom(john);
        daisy = rnd.next(0, 3) == 0 ? bessie : randomPointDifferentFrom(john);
    }

    println(bessie.r, bessie.c);
    println(daisy.r, daisy.c);
    println(john.r, john.c);

    return 0;
}
