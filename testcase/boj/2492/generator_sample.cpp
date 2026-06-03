#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

void addPoint(vector<Point>& points, set<Point>& used, int x, int y) {
    if (used.insert({x, y}).second) points.push_back({x, y});
}

int clampInt(long long value, int lo, int hi) {
    return int(max<long long>(lo, min<long long>(hi, value)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 80);
    int m = rnd.next(1, 80);

    if (mode == 3) {
        n = rnd.next(900000, 1000000);
        m = rnd.next(900000, 1000000);
    } else if (mode == 4) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 8);
    }

    int k = rnd.next(1, min(n, m));
    if (mode == 1) k = min(n, m);
    if (mode == 2) k = rnd.next(1, min(5, min(n, m)));
    if (mode == 3) k = rnd.next(max(1, min(n, m) - 20), min(n, m));

    int t = rnd.next(1, 30);
    if (mode == 4) t = min(100, (n + 1) * (m + 1));
    if (mode == 5) t = rnd.next(50, 100);

    vector<Point> points;
    set<Point> used;

    if (mode == 0) {
        int baseX = rnd.next(0, n);
        int baseY = rnd.next(0, m);
        int radius = rnd.next(0, max(1, k));
        for (int i = 0; i < t * 3 && int(points.size()) < t; ++i) {
            int x = clampInt(baseX + rnd.next(-radius, radius), 0, n);
            int y = clampInt(baseY + rnd.next(-radius, radius), 0, m);
            addPoint(points, used, x, y);
        }
    } else if (mode == 1) {
        vector<Point> corners = {{0, 0}, {0, m}, {n, 0}, {n, m}};
        shuffle(corners.begin(), corners.end());
        for (auto p : corners) addPoint(points, used, p.first, p.second);
    } else if (mode == 2) {
        int x = rnd.next(0, n);
        int y = rnd.next(0, m);
        for (int dx = -2; dx <= 2 && int(points.size()) < t; ++dx)
            for (int dy = -2; dy <= 2 && int(points.size()) < t; ++dy)
                addPoint(points, used, clampInt(x + dx, 0, n), clampInt(y + dy, 0, m));
    } else if (mode == 3) {
        addPoint(points, used, 0, 0);
        addPoint(points, used, n, m);
        addPoint(points, used, rnd.next(0, 20), rnd.next(m - 20, m));
        addPoint(points, used, rnd.next(n - 20, n), rnd.next(0, 20));
    } else if (mode == 4) {
        vector<Point> all;
        for (int x = 0; x <= n; ++x)
            for (int y = 0; y <= m; ++y)
                all.push_back({x, y});
        shuffle(all.begin(), all.end());
        for (int i = 0; i < t; ++i) addPoint(points, used, all[i].first, all[i].second);
    } else {
        int lines = rnd.next(2, 5);
        for (int i = 0; i < t * 3 && int(points.size()) < t; ++i) {
            int x = rnd.next() < 0.5 ? rnd.next(0, lines) : rnd.next(max(0, n - lines), n);
            int y = rnd.next(0, m);
            if (rnd.next() < 0.5) swap(x, y);
            addPoint(points, used, clampInt(x, 0, n), clampInt(y, 0, m));
        }
    }

    while (int(points.size()) < t) {
        addPoint(points, used, rnd.next(0, n), rnd.next(0, m));
    }

    shuffle(points.begin(), points.end());

    println(n, m, int(points.size()), k);
    for (auto [x, y] : points) println(x, y);

    return 0;
}
