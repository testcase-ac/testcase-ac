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

static vector<Point> allCells(int n, int m) {
    vector<Point> cells;
    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= m; ++y) {
            cells.push_back({x, y});
        }
    }
    return cells;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 1;
    vector<Point> points;
    set<Point> used;
    Point start = {1, 1};

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 18);
        int k = rnd.next(1, m);
        vector<int> ys;
        for (int y = 1; y <= m; ++y) ys.push_back(y);
        shuffle(ys.begin(), ys.end());
        ys.resize(k);
        sort(ys.begin(), ys.end());
        for (int y : ys) addPoint(points, used, 1, y);
        start = rnd.any(points);
    } else if (mode == 1) {
        n = rnd.next(2, 4);
        m = rnd.next(2, 6);
        vector<Point> cells = allCells(n, m);
        shuffle(cells.begin(), cells.end());
        int k = rnd.next(max(2, n * m / 2), n * m);
        for (int i = 0; i < k; ++i) addPoint(points, used, cells[i].first, cells[i].second);
        start = rnd.any(points);
    } else if (mode == 2) {
        n = rnd.next(3, 8);
        m = rnd.next(3, 8);
        int target = rnd.next(4, min(18, n * m));
        int x = rnd.next(1, n);
        int y = rnd.next(1, m);
        addPoint(points, used, x, y);
        while ((int)points.size() < target) {
            Point base = rnd.any(points);
            int nx = base.first + rnd.next(-1, 1);
            int ny = base.second + rnd.next(-1, 1);
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            addPoint(points, used, nx, ny);
        }
        start = rnd.any(points);
    } else if (mode == 3) {
        n = rnd.next(4, 10);
        m = rnd.next(4, 10);
        addPoint(points, used, 1, 1);
        addPoint(points, used, 1, min(m, 2));
        addPoint(points, used, n, m);
        addPoint(points, used, max(1, n - 1), m);
        if (rnd.next(0, 1)) addPoint(points, used, n, max(1, m - 1));
        start = points[rnd.next(0, 1)];
    } else if (mode == 4) {
        n = rnd.next(3, 7);
        m = rnd.next(3, 7);
        int cx = rnd.next(2, n - 1);
        int cy = rnd.next(2, m - 1);
        addPoint(points, used, cx, cy);
        addPoint(points, used, cx - 1, cy - 1);
        addPoint(points, used, cx - 1, cy + 1);
        addPoint(points, used, cx + 1, cy - 1);
        addPoint(points, used, cx + 1, cy + 1);
        if (rnd.next(0, 1)) addPoint(points, used, cx - 1, cy);
        if (rnd.next(0, 1)) addPoint(points, used, cx + 1, cy);
        start = rnd.any(points);
    } else {
        n = rnd.next(5, 12);
        m = rnd.next(5, 12);
        int k = rnd.next(3, 16);
        vector<Point> cells = allCells(n, m);
        shuffle(cells.begin(), cells.end());
        for (int i = 0; i < k; ++i) addPoint(points, used, cells[i].first, cells[i].second);
        start = rnd.any(points);
    }

    shuffle(points.begin(), points.end());
    int s = 1;
    for (int i = 0; i < (int)points.size(); ++i) {
        if (points[i] == start) {
            s = i + 1;
            break;
        }
    }

    println(n, m, (int)points.size());
    for (Point p : points) {
        println(p.first, p.second);
    }
    println(s);

    return 0;
}
