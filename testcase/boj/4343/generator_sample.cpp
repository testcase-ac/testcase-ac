#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

Point clampPoint(int x, int y) {
    return {max(0, min(10000, x)), max(0, min(10000, y))};
}

void addUnique(vector<Point>& points, set<Point>& used, Point point) {
    if (used.insert(point).second) {
        points.push_back(point);
    }
}

vector<Point> makeLineCase(int p) {
    vector<Point> points;
    int startX = rnd.next(0, 1500);
    int startY = rnd.next(0, 1500);
    int dx = rnd.next(0, 3) == 0 ? 0 : rnd.next(1, 900);
    int dy = dx == 0 ? rnd.next(1, 900) : rnd.next(0, 900);
    int jitter = rnd.next(0, 25);

    for (int i = 0; i < p; ++i) {
        int x = startX + i * dx + rnd.next(-jitter, jitter);
        int y = startY + i * dy + rnd.next(-jitter, jitter);
        points.push_back(clampPoint(x, y));
    }
    return points;
}

vector<Point> makeClusterCase(int p) {
    vector<Point> points;
    int clusters = rnd.next(2, min(5, p));
    vector<Point> centers;
    for (int i = 0; i < clusters; ++i) {
        centers.push_back({rnd.next(0, 10000), rnd.next(0, 10000)});
    }

    bool allowDuplicates = rnd.next(0, 4) == 0;
    set<Point> used;
    while ((int)points.size() < p) {
        Point c = rnd.any(centers);
        int radius = rnd.next(0, 800);
        Point point = clampPoint(c.first + rnd.next(-radius, radius),
                                 c.second + rnd.next(-radius, radius));
        if (allowDuplicates) {
            points.push_back(point);
        } else {
            addUnique(points, used, point);
        }
    }
    return points;
}

vector<Point> makeGridCase(int p) {
    vector<Point> points;
    set<Point> used;
    int step = rnd.next(1, 1200);
    int width = rnd.next(2, min(8, p));
    int baseX = rnd.next(0, 10000);
    int baseY = rnd.next(0, 10000);

    for (int i = 0; (int)points.size() < p; ++i) {
        int row = i / width;
        int col = i % width;
        int x = baseX + col * step + rnd.next(-3, 3);
        int y = baseY + row * step + rnd.next(-3, 3);
        addUnique(points, used, clampPoint(x, y));
    }
    return points;
}

vector<Point> makeExtremeCase(int p) {
    vector<Point> points;
    set<Point> used;
    vector<Point> base = {{0, 0}, {0, 10000}, {10000, 0}, {10000, 10000},
                          {5000, 5000}};
    shuffle(base.begin(), base.end());
    for (Point point : base) {
        if ((int)points.size() < p) {
            addUnique(points, used, point);
        }
    }
    while ((int)points.size() < p) {
        int edge = rnd.next(0, 3);
        int v = rnd.next(0, 10000);
        Point point;
        if (edge == 0) point = {0, v};
        if (edge == 1) point = {10000, v};
        if (edge == 2) point = {v, 0};
        if (edge == 3) point = {v, 10000};
        addUnique(points, used, point);
    }
    return points;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tests = rnd.next(1, 8);
    println(tests);
    for (int tc = 0; tc < tests; ++tc) {
        int p = rnd.next(2, 35);
        int s;
        if (rnd.next(0, 5) == 0) {
            s = p - 1;
        } else if (rnd.next(0, 4) == 0) {
            s = 1;
        } else {
            s = rnd.next(1, p - 1);
        }

        vector<Point> points;
        int mode = rnd.next(0, 3);
        if (mode == 0) points = makeLineCase(p);
        if (mode == 1) points = makeClusterCase(p);
        if (mode == 2) points = makeGridCase(p);
        if (mode == 3) points = makeExtremeCase(p);

        shuffle(points.begin(), points.end());
        println(s, p);
        for (Point point : points) {
            println(point.first, point.second);
        }
    }

    return 0;
}
