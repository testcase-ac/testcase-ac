#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

namespace {

const int kCoordLimit = 5000;

bool addPoint(set<pair<int, int>>& used, vector<pair<int, int>>& points, int x, int y) {
    if (x < 0 || x > kCoordLimit || y < 0 || y > kCoordLimit) return false;
    if (!used.insert({x, y}).second) return false;
    points.push_back({x, y});
    return true;
}

bool addSquare(set<pair<int, int>>& used, vector<pair<int, int>>& points, int x, int y, int dx, int dy) {
    vector<pair<int, int>> square = {
        {x, y},
        {x + dx, y + dy},
        {x + dx - dy, y + dy + dx},
        {x - dy, y + dx},
    };

    for (const auto& p : square) {
        if (p.first < 0 || p.first > kCoordLimit || p.second < 0 || p.second > kCoordLimit) return false;
        if (used.count(p)) return false;
    }

    for (const auto& p : square) addPoint(used, points, p.first, p.second);
    return true;
}

void addRandomNoise(set<pair<int, int>>& used, vector<pair<int, int>>& points, int target) {
    int attempts = 0;
    while ((int)points.size() < target && attempts < 10000) {
        ++attempts;
        int style = rnd.next(0, 3);
        int x = rnd.next(0, kCoordLimit);
        int y = rnd.next(0, kCoordLimit);

        if (style == 1) x = rnd.any(vector<int>{0, 1, 2, 4998, 4999, 5000});
        if (style == 2) y = rnd.any(vector<int>{0, 1, 2, 4998, 4999, 5000});
        if (style == 3) {
            x = rnd.next(0, 30);
            y = rnd.next(0, 30);
        }

        addPoint(used, points, x, y);
    }
}

bool addRandomSquare(set<pair<int, int>>& used, vector<pair<int, int>>& points, bool axisAligned) {
    for (int attempt = 0; attempt < 2000; ++attempt) {
        int dx, dy;
        if (axisAligned) {
            dx = rnd.next(1, 70);
            dy = 0;
        } else {
            dx = rnd.next(-40, 40);
            dy = rnd.next(-40, 40);
            if (dx == 0 && dy == 0) continue;
        }

        int x = rnd.next(0, kCoordLimit);
        int y = rnd.next(0, kCoordLimit);
        if (addSquare(used, points, x, y, dx, dy)) return true;
    }
    return false;
}

} // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    set<pair<int, int>> used;
    vector<pair<int, int>> points;

    int mode = rnd.next(0, 4);
    int target = rnd.next(1, 45);

    if (mode == 0) {
        target = rnd.next(1, 20);
    } else if (mode == 1) {
        addRandomSquare(used, points, true);
        target = rnd.next((int)points.size(), 35);
    } else if (mode == 2) {
        addRandomSquare(used, points, false);
        target = rnd.next((int)points.size(), 35);
    } else if (mode == 3) {
        int squareCount = rnd.next(2, 5);
        for (int i = 0; i < squareCount; ++i) {
            addRandomSquare(used, points, rnd.next(0, 1) == 0);
        }
        target = rnd.next((int)points.size(), 50);
    } else {
        addPoint(used, points, 0, 0);
        addPoint(used, points, 5000, 0);
        addPoint(used, points, 5000, 5000);
        addPoint(used, points, 0, 5000);
        target = rnd.next(4, 25);
    }

    addRandomNoise(used, points, target);
    shuffle(points.begin(), points.end());

    println((int)points.size());
    for (const auto& p : points) println(p.first, p.second);

    return 0;
}
