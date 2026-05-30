#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x;
    long long y;
};

long long dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

long long cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

Point operator-(Point a, Point b) {
    return {a.x - b.x, a.y - b.y};
}

long long squaredLength(Point a) {
    return dot(a, a);
}

long long signedDoubleArea(const vector<Point>& p) {
    long long area = 0;
    for (int i = 0; i < 4; ++i) {
        area += cross(p[i], p[(i + 1) % 4]);
    }
    return area;
}

bool isClockwiseRectangle(const vector<Point>& p) {
    for (int i = 0; i < 4; ++i) {
        Point side = p[(i + 1) % 4] - p[i];
        if (squaredLength(side) == 0) {
            return false;
        }
    }

    for (int i = 0; i < 4; ++i) {
        Point a = p[(i + 1) % 4] - p[i];
        Point b = p[(i + 2) % 4] - p[(i + 1) % 4];
        if (dot(a, b) != 0) {
            return false;
        }
    }

    if (squaredLength(p[1] - p[0]) != squaredLength(p[3] - p[2])) {
        return false;
    }
    if (squaredLength(p[2] - p[1]) != squaredLength(p[0] - p[3])) {
        return false;
    }

    return signedDoubleArea(p) < 0;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readInt(1, 1000, "R");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        vector<Point> p(4);
        for (int j = 0; j < 4; ++j) {
            p[j].x = inf.readInt(-1000, 1000, format("x_%d_%d", i + 1, j + 1));
            inf.readSpace();
            p[j].y = inf.readInt(-1000, 1000, format("y_%d_%d", i + 1, j + 1));
            if (j < 3) {
                inf.readSpace();
            }
        }
        inf.readEoln();

        ensuref(isClockwiseRectangle(p),
                "device %d must be a non-degenerate rectangle with vertices in clockwise order",
                i + 1);
    }

    inf.readEof();
}
