#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

const long long kLimit = 1000000000LL;

long long RandomNonZero(long long lo, long long hi) {
    while (true) {
        long long value = rnd.next(lo, hi);
        if (value != 0) return value;
    }
}

Point Scale(Point direction, long long scale) {
    return {direction.first * scale, direction.second * scale};
}

Point RandomPoint(int coord_limit) {
    while (true) {
        Point p = {rnd.next(-coord_limit, coord_limit),
                   rnd.next(-coord_limit, coord_limit)};
        if (p.first != 0 || p.second != 0) return p;
    }
}

Point RandomDirection() {
    while (true) {
        Point p = {rnd.next(-8, 8), rnd.next(-8, 8)};
        if (p.first == 0 && p.second == 0) continue;
        long long g = gcd(llabs(p.first), llabs(p.second));
        return {p.first / g, p.second / g};
    }
}

void AddUnique(vector<Point>& points, set<Point>& used, Point p) {
    if (p.first == 0 && p.second == 0) return;
    if (abs(p.first) > kLimit || abs(p.second) > kLimit) return;
    if (used.insert(p).second) points.push_back(p);
}

void FillRandom(vector<Point>& points, set<Point>& used, int target,
                int coord_limit) {
    while ((int)points.size() < target) {
        AddUnique(points, used, RandomPoint(coord_limit));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 35);
    int m = rnd.next(1, 35);
    vector<Point> fruits;
    vector<Point> endpoints;
    set<Point> used_fruits;
    set<Point> used_endpoints;

    if (mode == 0) {
        int directions = rnd.next(1, 5);
        for (int d = 0; d < directions; ++d) {
            Point dir = RandomDirection();
            int count = rnd.next(1, 8);
            for (int i = 0; i < count; ++i) {
                AddUnique(fruits, used_fruits, Scale(dir, rnd.next(1, 25)));
            }
            for (int i = 0; i < rnd.next(1, 6); ++i) {
                AddUnique(endpoints, used_endpoints,
                          Scale(dir, rnd.next(1, 30)));
            }
        }
    } else if (mode == 1) {
        vector<Point> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1},
                              {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
        shuffle(dirs.begin(), dirs.end());
        for (Point dir : dirs) {
            for (int i = 0; i < rnd.next(1, 4); ++i) {
                AddUnique(fruits, used_fruits, Scale(dir, rnd.next(1, 18)));
            }
            AddUnique(endpoints, used_endpoints, Scale(dir, rnd.next(1, 22)));
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            long long x = RandomNonZero(-25, 25);
            long long y = RandomNonZero(-25, 25);
            AddUnique(fruits, used_fruits, {x, y});
            if (rnd.next(0, 2) == 0) AddUnique(endpoints, used_endpoints, {x, y});
        }
    } else if (mode == 3) {
        vector<long long> values = {-kLimit, -kLimit + 1, -999999937LL,
                                    -123456789LL, -1, 1, 123456789LL,
                                    999999937LL, kLimit - 1, kLimit};
        for (long long x : values) {
            long long y = rnd.any(values);
            AddUnique(fruits, used_fruits, {x, y});
            AddUnique(endpoints, used_endpoints, {y, x});
        }
    } else {
        int coord_limit = rnd.next(6, 60);
        FillRandom(fruits, used_fruits, n, coord_limit);
        FillRandom(endpoints, used_endpoints, m, coord_limit);
    }

    FillRandom(fruits, used_fruits, n, 80);
    FillRandom(endpoints, used_endpoints, m, 80);
    shuffle(fruits.begin(), fruits.end());
    shuffle(endpoints.begin(), endpoints.end());

    println((int)fruits.size(), (int)endpoints.size());
    for (Point p : fruits) println(p.first, p.second);
    for (Point p : endpoints) println(p.first, p.second);

    return 0;
}
