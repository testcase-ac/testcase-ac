#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

vector<int> oddValuesUpTo(int b) {
    vector<int> values;
    for (int x = 1; x <= b; x += 2) values.push_back(x);
    return values;
}

void addPoint(vector<pair<int, int>>& points, set<pair<int, int>>& seen, int x, int y) {
    if (seen.insert({x, y}).second) points.push_back({x, y});
}

int chooseB(int mode) {
    if (mode == 0) return rnd.next(1, 15);
    if (mode == 1) return rnd.next(2, 100);
    if (mode == 2) return rnd.next(25, 250);
    if (mode == 3) return rnd.next(999900, 1000000);
    return rnd.next(3, 1000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int b = chooseB(mode);
    vector<int> odds = oddValuesUpTo(b);

    int capacity = (int)min<long long>(100, 1LL * odds.size() * odds.size());
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, min(capacity, 6));
    } else if (mode == 1) {
        n = rnd.next(4, min(capacity, 25));
    } else if (mode == 2) {
        n = rnd.next(10, min(capacity, 60));
    } else {
        n = rnd.next(20, capacity);
    }

    vector<pair<int, int>> points;
    set<pair<int, int>> seen;

    if (mode == 0) {
        addPoint(points, seen, rnd.any(odds), rnd.any(odds));
    } else if (mode == 1) {
        vector<int> xs = odds;
        vector<int> ys = odds;
        shuffle(xs.begin(), xs.end());
        shuffle(ys.begin(), ys.end());
        int maxX = min<int>(xs.size(), 8);
        int maxY = min<int>(ys.size(), 8);
        int xCount = rnd.next((n + maxY - 1) / maxY, maxX);
        int yCount = rnd.next((n + xCount - 1) / xCount, maxY);
        int attempts = 0;
        while ((int)points.size() < n && attempts++ < n * 20) {
            addPoint(points, seen, xs[rnd.next(xCount)], ys[rnd.next(yCount)]);
        }
    } else if (mode == 2) {
        int centerX = rnd.any(odds);
        int centerY = rnd.any(odds);
        int radius = rnd.next(0, min(20, (int)odds.size() - 1));
        int attempts = 0;
        while ((int)points.size() < n && attempts++ < n * 20) {
            int dx = rnd.next(-radius, radius) * 2;
            int dy = rnd.next(-radius, radius) * 2;
            int x = min(b | 1, max(1, centerX + dx));
            int y = min(b | 1, max(1, centerY + dy));
            if (x > b) x -= 2;
            if (y > b) y -= 2;
            addPoint(points, seen, x, y);
        }
    } else if (mode == 3) {
        addPoint(points, seen, 1, 1);
        addPoint(points, seen, 1, odds.back());
        addPoint(points, seen, odds.back(), 1);
        addPoint(points, seen, odds.back(), odds.back());
    } else {
        int step = rnd.next(1, max(1, (int)odds.size() / max(1, n)));
        for (int i = 0; i < (int)odds.size() && (int)points.size() < n; i += step) {
            int x = odds[i];
            int y = (rnd.next(2) == 0 ? x : odds[(odds.size() - 1 - i) % odds.size()]);
            addPoint(points, seen, x, y);
        }
    }

    while ((int)points.size() < n) {
        addPoint(points, seen, rnd.any(odds), rnd.any(odds));
    }

    shuffle(points.begin(), points.end());

    println(n, b);
    for (auto [x, y] : points) println(x, y);

    return 0;
}
