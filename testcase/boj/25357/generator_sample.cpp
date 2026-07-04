#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

constexpr long long kMinCoord = -1000000000LL;
constexpr long long kMaxCoord = 1000000000LL;

long long randomCoord(long long lo = kMinCoord, long long hi = kMaxCoord) {
    return rnd.next(lo, hi);
}

Point randomPoint(long long lo = kMinCoord, long long hi = kMaxCoord) {
    return {randomCoord(lo, hi), randomCoord(lo, hi)};
}

bool hasPoint(const vector<Point>& points, Point candidate) {
    return find(points.begin(), points.end(), candidate) != points.end();
}

void addRandomDistinct(vector<Point>& points, long long lo = kMinCoord, long long hi = kMaxCoord) {
    Point candidate = randomPoint(lo, hi);
    while (hasPoint(points, candidate)) {
        candidate = randomPoint(lo, hi);
    }
    points.push_back(candidate);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> points;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        for (int i = 0; i < 3; ++i) {
            addRandomDistinct(points);
        }
    } else if (mode == 1) {
        long long x = randomCoord();
        for (int i = 0; i < 3; ++i) {
            Point candidate = {x, randomCoord()};
            while (hasPoint(points, candidate)) {
                candidate = {x, randomCoord()};
            }
            points.push_back(candidate);
        }
    } else if (mode == 2) {
        long long y = randomCoord();
        for (int i = 0; i < 3; ++i) {
            Point candidate = {randomCoord(), y};
            while (hasPoint(points, candidate)) {
                candidate = {randomCoord(), y};
            }
            points.push_back(candidate);
        }
    } else if (mode == 3) {
        long long x = randomCoord(-1000, 1000);
        long long y = randomCoord(-1000, 1000);
        points.push_back({x, y});
        Point vertical = {x, randomCoord(-1000, 1000)};
        while (hasPoint(points, vertical)) {
            vertical = {x, randomCoord(-1000, 1000)};
        }
        points.push_back(vertical);
        Point horizontal = {randomCoord(-1000, 1000), y};
        while (hasPoint(points, horizontal)) {
            horizontal = {randomCoord(-1000, 1000), y};
        }
        points.push_back(horizontal);
    } else if (mode == 4) {
        long long lo = rnd.next(-20, 0);
        long long hi = rnd.next(0, 20);
        for (int i = 0; i < 3; ++i) {
            addRandomDistinct(points, lo, hi);
        }
    } else {
        vector<long long> coords = {kMinCoord, kMinCoord + 1, -1, 0, 1,
                                   kMaxCoord - 1, kMaxCoord};
        for (int i = 0; i < 3; ++i) {
            Point candidate = {rnd.any(coords), rnd.any(coords)};
            while (hasPoint(points, candidate)) {
                candidate = {rnd.any(coords), rnd.any(coords)};
            }
            points.push_back(candidate);
        }
    }

    shuffle(points.begin(), points.end());
    for (Point point : points) {
        println(point.first, point.second);
    }

    return 0;
}
