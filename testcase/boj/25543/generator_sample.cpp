#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

void addPoint(vector<Point>& points, set<Point>& used, long long x, long long y) {
    if (used.emplace(x, y).second) points.emplace_back(x, y);
}

void addAxisLine(vector<Point>& points, set<Point>& used, int radius, bool horizontal) {
    for (int d = -radius; d <= radius; ++d) {
        if (horizontal) addPoint(points, used, d, 0);
        else addPoint(points, used, 0, d);
    }
}

void addIncreasingChain(vector<Point>& points, set<Point>& used, int quadrant, int len) {
    for (int i = 1; i <= len; ++i) {
        int x = i;
        int y = i + rnd.next(0, 2);
        if (quadrant == 1) addPoint(points, used, x, y);
        if (quadrant == 2) addPoint(points, used, -x, y);
        if (quadrant == 3) addPoint(points, used, -x, -y);
        if (quadrant == 4) addPoint(points, used, x, -y);
    }
}

void addRandomScatter(vector<Point>& points, set<Point>& used, int target, int limit) {
    while ((int)points.size() < target) {
        addPoint(points, used, rnd.next(-limit, limit), rnd.next(-limit, limit));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> points;
    set<Point> used;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int radius = rnd.next(1, 5);
        for (int d = 1; d <= radius; ++d) {
            addPoint(points, used, d, d + rnd.next(0, 1));
            addPoint(points, used, -d, -d - rnd.next(0, 1));
            addPoint(points, used, -d, d + rnd.next(0, 1));
            addPoint(points, used, d, -d - rnd.next(0, 1));
        }
        addPoint(points, used, 0, 0);
        addRandomScatter(points, used, rnd.next((int)points.size(), min(50, (int)points.size() + 20)), 12);
    } else if (mode == 1) {
        int radius = rnd.next(1, 8);
        addAxisLine(points, used, radius, true);
        if (rnd.next(0, 1)) addAxisLine(points, used, radius, false);
        addRandomScatter(points, used, rnd.next((int)points.size(), min(45, (int)points.size() + 15)), 15);
    } else if (mode == 2) {
        addPoint(points, used, 0, 0);
        for (int q = 1; q <= 4; ++q) addIncreasingChain(points, used, q, rnd.next(1, 8));
        addRandomScatter(points, used, rnd.next((int)points.size(), min(55, (int)points.size() + 15)), 18);
    } else if (mode == 3) {
        int n = rnd.next(1, 4);
        long long base = rnd.any(vector<long long>{-1000000000LL, -999999999LL, 999999999LL, 1000000000LL});
        for (int i = 0; i < n; ++i) {
            long long x = base + (base < 0 ? i : -i);
            long long y = rnd.next(-3, 3);
            addPoint(points, used, x, y);
        }
        addRandomScatter(points, used, rnd.next(n, 20), 6);
    } else {
        int n = rnd.next(5, 80);
        int limit = rnd.next(3, 25);
        addRandomScatter(points, used, n, limit);
    }

    shuffle(points.begin(), points.end());
    println((int)points.size());
    for (const Point& p : points) println(p.first, p.second);

    return 0;
}
