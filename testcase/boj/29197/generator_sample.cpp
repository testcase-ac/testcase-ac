#include "testlib.h"
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

const int COORD_LIMIT = 10000;

int maxScale(int x, int y) {
    int limit = COORD_LIMIT;
    if (x != 0) limit = min(limit, COORD_LIMIT / abs(x));
    if (y != 0) limit = min(limit, COORD_LIMIT / abs(y));
    return limit;
}

bool primitive(int x, int y) {
    return (x != 0 || y != 0) && gcd(abs(x), abs(y)) == 1;
}

void addPoint(vector<pair<int, int>>& points, set<pair<int, int>>& used, int x, int y) {
    if (x == 0 && y == 0) return;
    if (x < -COORD_LIMIT || x > COORD_LIMIT) return;
    if (y < -COORD_LIMIT || y > COORD_LIMIT) return;
    if (used.insert({x, y}).second) points.push_back({x, y});
}

pair<int, int> randomDirection(int span) {
    while (true) {
        int x = rnd.next(-span, span);
        int y = rnd.next(-span, span);
        if (primitive(x, y)) return {x, y};
    }
}

void addRay(vector<pair<int, int>>& points, set<pair<int, int>>& used, int dx, int dy, int count) {
    int hi = maxScale(dx, dy);
    vector<int> scales;
    for (int s = 1; s <= hi; ++s) scales.push_back(s);
    shuffle(scales.begin(), scales.end());
    count = min(count, static_cast<int>(scales.size()));
    for (int i = 0; i < count; ++i) addPoint(points, used, dx * scales[i], dy * scales[i]);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> points;
    set<pair<int, int>> used;

    int mode = rnd.next(5);
    if (mode == 0) {
        int rays = rnd.next(3, 9);
        for (int i = 0; i < rays; ++i) {
            auto [dx, dy] = randomDirection(rnd.next(2, 9));
            addRay(points, used, dx, dy, rnd.next(1, 5));
        }
    } else if (mode == 1) {
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, -1}};
        shuffle(dirs.begin(), dirs.end());
        for (auto [dx, dy] : dirs) addRay(points, used, dx, dy, rnd.next(1, 6));
    } else if (mode == 2) {
        int n = rnd.next(8, 35);
        while (static_cast<int>(points.size()) < n) {
            auto [dx, dy] = randomDirection(30);
            addRay(points, used, dx, dy, 1);
        }
    } else if (mode == 3) {
        vector<pair<int, int>> candidates = {
            {-10000, -10000}, {-10000, 10000}, {10000, -10000}, {10000, 10000},
            {-10000, 0}, {10000, 0}, {0, -10000}, {0, 10000},
            {-9999, 10000}, {9999, -10000}, {-10000, 9999}, {10000, -9999}
        };
        shuffle(candidates.begin(), candidates.end());
        int n = rnd.next(4, static_cast<int>(candidates.size()));
        for (int i = 0; i < n; ++i) addPoint(points, used, candidates[i].first, candidates[i].second);
    } else {
        int rays = rnd.next(4, 10);
        for (int i = 0; i < rays; ++i) {
            auto [dx, dy] = randomDirection(12);
            int count = rnd.next(1, 4);
            addRay(points, used, dx, dy, count);
            if (rnd.next(2) == 0) addRay(points, used, -dx, -dy, rnd.next(1, count));
        }
    }

    if (points.empty()) addPoint(points, used, 1, 0);
    shuffle(points.begin(), points.end());

    println(static_cast<int>(points.size()));
    for (auto [x, y] : points) println(x, y);

    return 0;
}
