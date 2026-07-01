#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

const long long MIN_COORD = -1000000000LL;
const long long MAX_COORD = 1000000000LL;

bool inBounds(const Point& p) {
    return MIN_COORD <= p.first && p.first <= MAX_COORD &&
           MIN_COORD <= p.second && p.second <= MAX_COORD;
}

void addPoint(vector<Point>& points, set<Point>& used, Point p) {
    if (inBounds(p) && used.insert(p).second) {
        points.push_back(p);
    }
}

Point randomSmallPoint(int radius) {
    return {rnd.next(-radius, radius), rnd.next(-radius, radius)};
}

void fillRandom(vector<Point>& points, set<Point>& used, int target, int radius) {
    while ((int)points.size() < target) {
        addPoint(points, used, randomSmallPoint(radius));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> points;
    set<Point> used;

    int mode = rnd.next(0, 5);
    int radius = rnd.next(3, 40);

    if (mode == 0) {
        fillRandom(points, used, rnd.next(1, 25), radius);
    } else if (mode == 1) {
        Point center = randomSmallPoint(20);
        int pairs = rnd.next(1, 18);
        if (rnd.next(0, 1)) {
            addPoint(points, used, center);
        }
        while ((int)points.size() < 2 * pairs) {
            Point delta = randomSmallPoint(radius);
            if (delta == Point{0, 0}) {
                continue;
            }
            addPoint(points, used, {center.first + delta.first, center.second + delta.second});
            addPoint(points, used, {center.first - delta.first, center.second - delta.second});
        }
        fillRandom(points, used, rnd.next((int)points.size(), (int)points.size() + 8), radius + 50);
    } else if (mode == 2) {
        Point center = randomSmallPoint(50);
        int orbits = rnd.next(1, 8);
        for (int i = 0; i < orbits; ++i) {
            Point delta = randomSmallPoint(radius);
            if (delta == Point{0, 0}) {
                --i;
                continue;
            }
            addPoint(points, used, {center.first + delta.first, center.second + delta.second});
            addPoint(points, used, {center.first - delta.second, center.second + delta.first});
            addPoint(points, used, {center.first - delta.first, center.second - delta.second});
            addPoint(points, used, {center.first + delta.second, center.second - delta.first});
        }
        if (rnd.next(0, 1)) {
            addPoint(points, used, center);
        }
    } else if (mode == 3) {
        int width = rnd.next(2, 8);
        int height = rnd.next(2, 8);
        int step = rnd.next(1, 5);
        Point base = randomSmallPoint(100);
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                if (rnd.next(0, 99) < 70) {
                    addPoint(points, used, {base.first + x * step, base.second + y * step});
                }
            }
        }
        fillRandom(points, used, max(1, (int)points.size()), radius + 100);
    } else if (mode == 4) {
        int n = rnd.next(2, 50);
        long long fixedX = rnd.next(-100, 100);
        while ((int)points.size() < n) {
            addPoint(points, used, {fixedX, rnd.next(-500, 500)});
        }
    } else {
        vector<Point> corners = {
            {MIN_COORD, MIN_COORD},
            {MIN_COORD, MAX_COORD},
            {MAX_COORD, MIN_COORD},
            {MAX_COORD, MAX_COORD},
            {0, 0},
        };
        shuffle(corners.begin(), corners.end());
        int take = rnd.next(1, (int)corners.size());
        for (int i = 0; i < take; ++i) {
            addPoint(points, used, corners[i]);
        }
        fillRandom(points, used, rnd.next(take, take + 12), 1000);
    }

    shuffle(points.begin(), points.end());

    println((int)points.size());
    for (const Point& p : points) {
        println(p.first, p.second);
    }

    return 0;
}
