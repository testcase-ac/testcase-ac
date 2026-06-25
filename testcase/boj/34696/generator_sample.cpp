#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

const int LIMIT = 999999999;

void addPoint(vector<Point>& points, set<Point>& used, int x, int y) {
    if (used.emplace(x, y).second) {
        points.emplace_back(x, y);
    }
}

void addRandomPoint(vector<Point>& points, set<Point>& used, int lo, int hi) {
    while (true) {
        int x = rnd.next(lo, hi);
        int y = rnd.next(lo, hi);
        if (used.emplace(x, y).second) {
            points.emplace_back(x, y);
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> points;
    set<Point> used;

    int mode = rnd.next(0, 5);
    int targetM = rnd.next(1, 35);

    if (mode == 0) {
        int start = rnd.next(0, 20);
        int step = rnd.next(1, 9);
        int y = rnd.next(0, 20);
        targetM = rnd.next(2, 30);
        for (int i = 0; i < targetM; ++i) {
            addPoint(points, used, start + i * step, y);
        }
    } else if (mode == 1) {
        int rows = rnd.next(2, 6);
        int cols = rnd.next(2, 6);
        int dx = rnd.next(1, 7);
        int dy = rnd.next(1, 7);
        int ox = rnd.next(0, 20);
        int oy = rnd.next(0, 20);
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                addPoint(points, used, ox + c * dx, oy + r * dy);
            }
        }
    } else if (mode == 2) {
        addPoint(points, used, 0, 0);
        addPoint(points, used, 0, LIMIT);
        addPoint(points, used, LIMIT, 0);
        addPoint(points, used, LIMIT, LIMIT);
        targetM = rnd.next(4, 24);
        while ((int)points.size() < targetM) {
            int side = rnd.next(0, 3);
            int v = rnd.next(0, LIMIT);
            if (side == 0) addPoint(points, used, v, 0);
            if (side == 1) addPoint(points, used, v, LIMIT);
            if (side == 2) addPoint(points, used, 0, v);
            if (side == 3) addPoint(points, used, LIMIT, v);
        }
    } else if (mode == 3) {
        int clusters = rnd.next(2, 4);
        targetM = rnd.next(clusters, 35);
        vector<Point> centers;
        for (int i = 0; i < clusters; ++i) {
            centers.emplace_back(rnd.next(50, 950), rnd.next(50, 950));
        }
        while ((int)points.size() < targetM) {
            Point center = rnd.any(centers);
            int x = center.first + rnd.next(-25, 25);
            int y = center.second + rnd.next(-25, 25);
            addPoint(points, used, x, y);
        }
    } else {
        targetM = rnd.next(1, 35);
        while ((int)points.size() < targetM) {
            addRandomPoint(points, used, 0, 1000);
        }
    }

    shuffle(points.begin(), points.end());

    int m = points.size();
    int n;
    if (m == 1) {
        n = 1;
    } else {
        int nMode = rnd.next(0, 3);
        if (nMode == 0) {
            n = 1;
        } else if (nMode == 1) {
            n = rnd.next(2, m);
        } else {
            n = m;
        }
    }
    int s1 = rnd.next(1, m);

    println(n, m);
    for (const Point& p : points) {
        println(p.first, p.second);
    }
    println(s1);

    return 0;
}
