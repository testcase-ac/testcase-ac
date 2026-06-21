#include "testlib.h"
#include <set>
#include <utility>
#include <vector>
using namespace std;

using Point = pair<int, int>;

void addPoint(vector<Point>& points, set<Point>& used, int x, int y) {
    if (used.insert({x, y}).second) {
        points.push_back({x, y});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);
    vector<Point> points;
    set<Point> used;

    if (mode == 0) {
        int x0 = rnd.next(1, 20);
        int y0 = rnd.next(1, 20);
        int dx = rnd.next(0, 4);
        int dy = rnd.next(0, 4);
        if (dx == 0 && dy == 0) {
            dy = 1;
        }
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, x0 + i * dx, y0 + i * dy);
        }
    } else if (mode == 1) {
        int rows = rnd.next(2, 5);
        int cols = rnd.next(2, 5);
        int x0 = rnd.next(1, 10);
        int y0 = rnd.next(1, 10);
        int stepX = rnd.next(1, 4);
        int stepY = rnd.next(1, 4);
        vector<Point> candidates;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                candidates.push_back({x0 + c * stepX, y0 + r * stepY});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        n = rnd.next(2, (int)candidates.size());
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, candidates[i].first, candidates[i].second);
        }
    } else if (mode == 2) {
        int x0 = rnd.next(30, 60);
        int y0 = rnd.next(30, 60);
        addPoint(points, used, x0, y0);
        vector<Point> directions = {{1, 0}, {0, 1}, {1, 1}, {1, 2}, {2, 1},
                                    {2, 3}, {3, 2}, {-1, 1}, {-2, 1}};
        shuffle(directions.begin(), directions.end());
        while ((int)points.size() < n) {
            Point dir = rnd.any(directions);
            int d = rnd.next(1, 8);
            addPoint(points, used, x0 + dir.first * d, y0 + dir.second * d);
        }
    } else if (mode == 3) {
        int x = rnd.next(1, 1000000000);
        int y = rnd.next(1, 1000000000);
        int dx = rnd.next(0, 1) ? 1 : -1;
        int dy = rnd.next(0, 1) ? 1 : -1;
        if (x <= 20) dx = 1;
        if (x >= 1000000000 - 20) dx = -1;
        if (y <= 20) dy = 1;
        if (y >= 1000000000 - 20) dy = -1;
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, x + dx * i, y + dy * rnd.next(0, 3));
        }
    } else if (mode == 4) {
        int x = rnd.next(1, 1000000000);
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, x, 1 + i * rnd.next(1, 4));
        }
    } else {
        int limit = rnd.next(5, 60);
        while ((int)points.size() < n) {
            addPoint(points, used, rnd.next(1, limit), rnd.next(1, limit));
        }
    }

    while ((int)points.size() < n) {
        addPoint(points, used, rnd.next(1, 100), rnd.next(1, 100));
    }
    shuffle(points.begin(), points.end());

    println((int)points.size());
    for (const Point& p : points) {
        println(p.first, p.second);
    }

    return 0;
}
