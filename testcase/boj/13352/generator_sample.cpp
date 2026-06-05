#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

const long long LIM = 1000000000LL;

void addPoint(vector<Point>& points, set<Point>& used, long long x, long long y) {
    if (x < -LIM || x > LIM || y < -LIM || y > LIM) return;
    if (used.insert({x, y}).second) points.push_back({x, y});
}

Point pointOnLine(long long bx, long long by, long long dx, long long dy, int t) {
    return {bx + dx * t, by + dy * t};
}

void addLinePoints(vector<Point>& points, set<Point>& used, int count) {
    long long bx = rnd.next(-20, 20);
    long long by = rnd.next(-20, 20);
    long long dx = rnd.next(-5, 5);
    long long dy = rnd.next(-5, 5);
    while (dx == 0 && dy == 0) {
        dx = rnd.next(-5, 5);
        dy = rnd.next(-5, 5);
    }

    vector<int> ts;
    for (int t = -30; t <= 30; ++t) ts.push_back(t);
    shuffle(ts.begin(), ts.end());

    for (int t : ts) {
        Point p = pointOnLine(bx, by, dx, dy, t);
        addPoint(points, used, p.first, p.second);
        if ((int)points.size() >= count) return;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> points;
    set<Point> used;

    int mode = rnd.next(5);
    int n = rnd.next(1, 24);

    if (mode == 0) {
        addLinePoints(points, used, n);
    } else if (mode == 1) {
        int first = rnd.next(1, n);
        addLinePoints(points, used, first);
        addLinePoints(points, used, n);
    } else if (mode == 2) {
        int first = max(2, n / 2);
        addLinePoints(points, used, first);
        addLinePoints(points, used, max(first + 1, n - 1));
        while ((int)points.size() < n) {
            addPoint(points, used, rnd.next(-15, 15), rnd.next(-15, 15));
        }
    } else if (mode == 3) {
        int width = rnd.next(2, 6);
        int height = rnd.next(2, 6);
        long long ox = rnd.next(-10, 10);
        long long oy = rnd.next(-10, 10);
        vector<Point> candidates;
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                candidates.push_back({ox + x, oy + y});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        n = min(n, (int)candidates.size());
        for (Point p : candidates) addPoint(points, used, p.first, p.second);
        points.resize(n);
    } else {
        while ((int)points.size() < n) {
            addPoint(points, used, rnd.next(-30, 30), rnd.next(-30, 30));
        }
        if (rnd.next(4) == 0 && !points.empty()) {
            Point old = points.back();
            used.erase(old);
            points.back() = {rnd.any(vector<long long>{-LIM, LIM}), rnd.next(-5, 5)};
            used.insert(points.back());
        }
    }

    while ((int)points.size() < n) {
        addPoint(points, used, rnd.next(-50, 50), rnd.next(-50, 50));
    }

    shuffle(points.begin(), points.end());
    println((int)points.size());
    for (Point p : points) println(p.first, p.second);

    return 0;
}
