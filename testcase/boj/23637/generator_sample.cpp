#include "testlib.h"

#include <cmath>
#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace {

const int kMaxCoord = 1000;
const double kPi = acos(-1.0);
const double kEps = 1e-9;

pair<int, int> randomPoint() {
    while (true) {
        int y = rnd.next(-kMaxCoord, kMaxCoord);
        int x = rnd.next(-kMaxCoord, kMaxCoord);
        if (y != 0 || x != 0) return {y, x};
    }
}

pair<int, int> boundaryPoint() {
    static const vector<pair<int, int>> points = {
        {0, 1},   {1, 0},    {0, -1},   {-1, 0},
        {1, 1},   {1, -1},   {-1, -1},  {-1, 1},
        {2, 1},   {1, 2},    {-2, 1},   {1, -2},
        {1000, 0}, {0, 1000}, {-1000, 0}, {0, -1000},
        {1000, 1000}, {-1000, 1000}, {1000, -1000}, {-1000, -1000},
    };
    return rnd.any(points);
}

pair<int, int> makePoint() {
    if (rnd.next(100) < 55) return boundaryPoint();
    return randomPoint();
}

double normAngle(double angle) {
    while (angle < 0.0) angle += 360.0;
    while (angle >= 360.0) angle -= 360.0;
    return angle;
}

bool betweenCounterClockwise(double angle, int start, int width) {
    if (width == 360) return true;

    double delta = normAngle(angle - start);
    return delta + kEps >= 0.0 && delta <= width + kEps;
}

int actualCount(const vector<pair<int, int>>& points, const string& dir, int a, int b, int r) {
    int result = 0;
    for (auto [y, x] : points) {
        if (1LL * y * y + 1LL * x * x > 1LL * r * r) continue;

        double angle = normAngle(atan2(static_cast<double>(y), static_cast<double>(x)) * 180.0 / kPi);
        bool visible = false;
        if (dir == "L") {
            visible = betweenCounterClockwise(angle, a, b);
        } else {
            visible = betweenCounterClockwise(angle, normAngle(a - b), b);
        }

        if (visible) ++result;
    }
    return result;
}

int chooseAngle() {
    static const vector<int> edgeAngles = {0, 1, 30, 45, 89, 90, 135, 179, 180, 225, 270, 315, 330, 359, 360};
    if (rnd.next(100) < 70) return rnd.any(edgeAngles);
    return rnd.next(0, 360);
}

int chooseWidth() {
    static const vector<int> edgeWidths = {0, 1, 30, 45, 90, 120, 180, 270, 300, 359, 360};
    if (rnd.next(100) < 75) return rnd.any(edgeWidths);
    return rnd.next(0, 360);
}

int chooseRadius() {
    static const vector<int> edgeRadii = {1, 2, 3, 5, 8, 30, 999, 1000};
    if (rnd.next(100) < 65) return rnd.any(edgeRadii);
    return rnd.next(1, 1000);
}

int claimedCount(int actual) {
    if (rnd.next(100) < 45) return actual;

    int delta = rnd.next(1, 4);
    if (rnd.next(2) == 0 && actual >= delta) return actual - delta;
    return actual + delta;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    int q = rnd.next(8, 35);

    vector<pair<int, int>> points;
    for (int i = 0; i < n; ++i) {
        points.push_back(makePoint());
    }

    println(n, q);
    for (auto [y, x] : points) {
        println(y, x);
    }

    for (int i = 0; i < q; ++i) {
        bool forceQuery = (i == q - 1);
        bool addPoint = !forceQuery && rnd.next(100) < 35;

        if (addPoint) {
            auto point = makePoint();
            points.push_back(point);
            println(1, point.first, point.second);
            continue;
        }

        string dir = rnd.next(2) == 0 ? "L" : "R";
        int a = chooseAngle();
        int b = chooseWidth();
        int r = chooseRadius();
        int actual = actualCount(points, dir, a, b, r);
        int c = claimedCount(actual);

        println(2, dir, a, b, r, c);
    }

    return 0;
}
