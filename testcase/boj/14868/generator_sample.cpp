#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

static void addPoint(vector<Point>& points, set<Point>& used, int x, int y) {
    if (used.insert({x, y}).second) {
        points.push_back({x, y});
    }
}

static void addCluster(vector<Point>& points, set<Point>& used, int n, int cx, int cy, int radius, int target) {
    vector<Point> candidates;
    for (int dx = -radius; dx <= radius; ++dx) {
        for (int dy = -radius; dy <= radius; ++dy) {
            if (abs(dx) + abs(dy) > radius) continue;
            int x = cx + dx;
            int y = cy + dy;
            if (1 <= x && x <= n && 1 <= y && y <= n) {
                candidates.push_back({x, y});
            }
        }
    }

    shuffle(candidates.begin(), candidates.end());
    for (Point p : candidates) {
        if ((int)points.size() >= target) break;
        addPoint(points, used, p.first, p.second);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 30);
    vector<Point> points;
    set<Point> used;

    if (mode == 0) {
        n = rnd.next(2, 8);
        int k = rnd.next(2, min(n * n, 12));
        int x = rnd.next(1, n);
        int y = rnd.next(1, n);
        while ((int)points.size() < k) {
            addPoint(points, used, x, y);
            int dir = rnd.next(0, 3);
            if (dir == 0 && x > 1) --x;
            else if (dir == 1 && x < n) ++x;
            else if (dir == 2 && y > 1) --y;
            else if (dir == 3 && y < n) ++y;
            else {
                x = rnd.next(1, n);
                y = rnd.next(1, n);
            }
        }
    } else if (mode == 1) {
        n = rnd.next(5, 30);
        addPoint(points, used, 1, 1);
        addPoint(points, used, 1, n);
        addPoint(points, used, n, 1);
        addPoint(points, used, n, n);
        if (rnd.next(0, 1)) addPoint(points, used, (n + 1) / 2, (n + 1) / 2);
    } else if (mode == 2) {
        n = rnd.next(4, 25);
        int k = rnd.next(2, min(n, 15));
        int fixed = rnd.next(1, n);
        bool vertical = rnd.next(0, 1);
        vector<int> coords;
        for (int i = 1; i <= n; ++i) coords.push_back(i);
        shuffle(coords.begin(), coords.end());
        coords.resize(k);
        sort(coords.begin(), coords.end());
        for (int v : coords) {
            if (vertical) addPoint(points, used, fixed, v);
            else addPoint(points, used, v, fixed);
        }
    } else if (mode == 3) {
        n = rnd.next(3, 10);
        int parity = rnd.next(0, 1);
        for (int x = 1; x <= n; ++x) {
            for (int y = 1; y <= n; ++y) {
                if (((x + y) & 1) == parity && (int)points.size() < 20) {
                    addPoint(points, used, x, y);
                }
            }
        }
    } else if (mode == 4) {
        n = rnd.next(6, 30);
        int clusters = rnd.next(2, 5);
        int target = rnd.next(clusters, 20);
        for (int i = 0; i < clusters; ++i) {
            int cx = rnd.next(1, n);
            int cy = rnd.next(1, n);
            int radius = rnd.next(1, 3);
            addCluster(points, used, n, cx, cy, radius, target);
        }
        while ((int)points.size() < target) {
            addPoint(points, used, rnd.next(1, n), rnd.next(1, n));
        }
    } else {
        n = rnd.next(2, 12);
        int k = rnd.next(2, min(n * n, 25));
        while ((int)points.size() < k) {
            addPoint(points, used, rnd.next(1, n), rnd.next(1, n));
        }
    }

    shuffle(points.begin(), points.end());
    println(n, (int)points.size());
    for (Point p : points) {
        println(p.first, p.second);
    }

    return 0;
}
