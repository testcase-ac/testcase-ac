#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

Point randomPoint(int n, int m) {
    return {rnd.next(0, n), rnd.next(0, m)};
}

Point boundaryPoint(int n, int m) {
    int side = rnd.next(0, 3);
    if (side == 0) return {0, rnd.next(0, m)};
    if (side == 1) return {n, rnd.next(0, m)};
    if (side == 2) return {rnd.next(0, n), 0};
    return {rnd.next(0, n), m};
}

void addUnique(vector<Point>& points, Point p, int n, int m) {
    while (find(points.begin(), points.end(), p) != points.end()) {
        p = randomPoint(n, m);
    }
    points.push_back(p);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m;
    vector<Point> points;

    if (mode == 0) {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
        while ((int)points.size() < 4) addUnique(points, randomPoint(n, m), n, m);
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        m = rnd.next(2, 20);
        while ((int)points.size() < 4) addUnique(points, boundaryPoint(n, m), n, m);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
        points = {{0, 0}, {n, m}, {0, m}, {n, 0}};
    } else if (mode == 3) {
        bool horizontal = rnd.next(0, 1);
        n = horizontal ? rnd.next(8, 35) : rnd.next(2, 4);
        m = horizontal ? rnd.next(2, 4) : rnd.next(8, 35);
        while ((int)points.size() < 4) addUnique(points, randomPoint(n, m), n, m);
    } else if (mode == 4) {
        n = rnd.next(4, 18);
        m = rnd.next(4, 18);
        int x = rnd.next(1, n - 1);
        int y = rnd.next(1, m - 1);
        points = {{x, 0}, {x, m}, {0, y}, {n, y}};
    } else {
        n = rnd.next(20, 100);
        m = rnd.next(20, 100);
        while ((int)points.size() < 4) addUnique(points, randomPoint(n, m), n, m);
    }

    if (rnd.next(0, 1)) swap(points[0], points[1]);
    if (rnd.next(0, 1)) swap(points[2], points[3]);
    if (rnd.next(0, 2) == 0) {
        swap(points[0], points[2]);
        swap(points[1], points[3]);
    }

    println(n, m);
    for (Point p : points) println(p.first, p.second);

    return 0;
}
