#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

using Point = pair<int, int>;

Point makePoint(int x, int y) {
    return {max(-1000, min(1000, x)), max(-1000, min(1000, y))};
}

void addUnique(vector<Point>& points, set<Point>& seen, Point point) {
    if (seen.insert(point).second) {
        points.push_back(point);
    }
}

vector<Point> randomCloud(int n) {
    vector<Point> points;
    set<Point> seen;
    int lo = rnd.next(-20, 0);
    int hi = rnd.next(1, 20);
    while ((int)points.size() < n) {
        addUnique(points, seen, {rnd.next(lo, hi), rnd.next(lo, hi)});
    }
    return points;
}

vector<Point> collinear(int n) {
    vector<Point> points;
    set<Point> seen;
    bool horizontal = rnd.next(0, 1);
    int fixed = rnd.next(-30, 30);
    int start = rnd.next(-50, -10);
    int step = rnd.next(1, 8);
    for (int i = 0; (int)points.size() < n; ++i) {
        int value = start + i * step + rnd.next(0, 1);
        Point point = horizontal ? makePoint(value, fixed) : makePoint(fixed, value);
        addUnique(points, seen, point);
    }
    return points;
}

vector<Point> gridLike(int n) {
    vector<Point> candidates;
    int rows = rnd.next(2, 4);
    int cols = rnd.next(2, 5);
    int dx = rnd.next(1, 7);
    int dy = rnd.next(1, 7);
    int baseX = rnd.next(-30, 10);
    int baseY = rnd.next(-30, 10);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            candidates.push_back({baseX + c * dx, baseY + r * dy});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    n = min(n, (int)candidates.size());
    candidates.resize(n);
    return candidates;
}

vector<Point> clustered(int n) {
    vector<Point> points;
    set<Point> seen;
    int ax = rnd.next(-80, -20), ay = rnd.next(-80, -20);
    int bx = rnd.next(20, 80), by = rnd.next(20, 80);
    while ((int)points.size() < n) {
        bool first = rnd.next(0, 1);
        int cx = first ? ax : bx;
        int cy = first ? ay : by;
        addUnique(points, seen, makePoint(cx + rnd.next(-3, 3), cy + rnd.next(-3, 3)));
    }
    return points;
}

vector<Point> boundaryHeavy(int n) {
    vector<Point> rawCandidates = {
        {-1000, -1000}, {-1000, 1000}, {1000, -1000}, {1000, 1000},
        {-1000, 0}, {1000, 0}, {0, -1000}, {0, 1000},
        {-999, 1000}, {999, -1000}, {1000, rnd.next(-999, 999)},
        {rnd.next(-999, 999), -1000}
    };
    vector<Point> candidates;
    set<Point> seen;
    for (const Point& point : rawCandidates) {
        addUnique(candidates, seen, point);
    }
    while ((int)candidates.size() < n) {
        int side = rnd.next(0, 3);
        if (side == 0) {
            addUnique(candidates, seen, {-1000, rnd.next(-999, 999)});
        } else if (side == 1) {
            addUnique(candidates, seen, {1000, rnd.next(-999, 999)});
        } else if (side == 2) {
            addUnique(candidates, seen, {rnd.next(-999, 999), -1000});
        } else {
            addUnique(candidates, seen, {rnd.next(-999, 999), 1000});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    candidates.resize(n);
    return candidates;
}

vector<Point> makeCase() {
    int mode = rnd.next(0, 4);
    int n = (mode == 4) ? rnd.next(2, 8) : rnd.next(2, 12);
    if (mode == 2) {
        n = rnd.next(2, 8);
    }

    vector<Point> points;
    if (mode == 0) {
        points = randomCloud(n);
    } else if (mode == 1) {
        points = collinear(n);
    } else if (mode == 2) {
        points = gridLike(n);
    } else if (mode == 3) {
        points = clustered(n);
    } else {
        points = boundaryHeavy(n);
    }

    shuffle(points.begin(), points.end());
    return points;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(3, 6);
    for (int tc = 0; tc < caseCount; ++tc) {
        vector<Point> points = makeCase();
        println((int)points.size());
        for (const Point& point : points) {
            println(point.first, point.second);
        }
    }
    println(0);
    return 0;
}
