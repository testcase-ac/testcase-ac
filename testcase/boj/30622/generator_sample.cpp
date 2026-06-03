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

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> points;
    set<Point> used;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 25);
        long long bx = rnd.next(-12, 12);
        long long by = rnd.next(-12, 12);
        addPoint(points, used, bx, by);
        while ((int)points.size() < n) {
            Point base = rnd.any(points);
            long long nx = base.first + rnd.next(-1, 1);
            long long ny = base.second + rnd.next(-1, 1);
            addPoint(points, used, nx, ny);
        }
    } else if (mode == 1) {
        int components = rnd.next(2, 6);
        for (int c = 0; c < components; ++c) {
            long long bx = c * 10LL + rnd.next(-2, 2);
            long long by = rnd.next(-15, 15);
            int len = rnd.next(1, 6);
            for (int i = 0; i < len; ++i) {
                int dx = rnd.next(0, 1) ? i : -i;
                int dy = rnd.next(0, 1) ? i : -i;
                addPoint(points, used, bx + dx, by + dy);
            }
        }
    } else if (mode == 2) {
        int rows = rnd.next(2, 5);
        int cols = rnd.next(2, 6);
        long long bx = rnd.next(-8, 8);
        long long by = rnd.next(-8, 8);
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (rnd.next(0, 99) < 70) addPoint(points, used, bx + r, by + c);
            }
        }
    } else if (mode == 3) {
        int n = rnd.next(3, 20);
        int spacing = rnd.next(3, 9);
        for (int i = 0; i < n; ++i) {
            long long x = (long long)(i - n / 2) * spacing + rnd.next(-1, 1);
            long long y = rnd.next(-20, 20);
            addPoint(points, used, x, y);
        }
    } else if (mode == 4) {
        int radius = rnd.next(1, 4);
        addPoint(points, used, 0, 0);
        for (int x = -radius; x <= radius; ++x) {
            for (int y = -radius; y <= radius; ++y) {
                if (abs(x) + abs(y) <= radius + rnd.next(0, 1)) {
                    addPoint(points, used, x, y);
                }
            }
        }
    } else {
        vector<Point> corners = {
            {-1000000000LL, -1000000000LL},
            {-1000000000LL, 1000000000LL},
            {1000000000LL, -1000000000LL},
            {1000000000LL, 1000000000LL},
        };
        shuffle(corners.begin(), corners.end());
        int take = rnd.next(1, 4);
        for (int i = 0; i < take; ++i) addPoint(points, used, corners[i].first, corners[i].second);

        int extra = rnd.next(0, 8);
        for (int i = 0; i < extra; ++i) {
            long long x = rnd.next(-30, 30);
            long long y = rnd.next(-30, 30);
            addPoint(points, used, x, y);
        }
    }

    if (points.empty()) addPoint(points, used, 0, 0);
    shuffle(points.begin(), points.end());

    println((int)points.size());
    for (const auto& point : points) println(point.first, point.second);

    return 0;
}
