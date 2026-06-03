#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

void addPoint(vector<Point>& points, set<Point>& used, long long x, long long y) {
    if (used.insert({x, y}).second) {
        points.push_back({x, y});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> points;
    set<Point> used;

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        int width = rnd.next(2, 6);
        int height = rnd.next(2, 6);
        int dx = rnd.next(-5, 5);
        int dy = rnd.next(-5, 5);
        vector<Point> candidates;
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                candidates.push_back({dx + x, dy + y});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int n = rnd.next(3, (int)candidates.size());
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, candidates[i].first, candidates[i].second);
        }
    } else if (mode == 1) {
        int n = rnd.next(5, 25);
        addPoint(points, used, 0, 0);
        while ((int)points.size() < n) {
            if (rnd.next(0, 1) == 0) {
                addPoint(points, used, rnd.next(-12, 12), 0);
            } else {
                addPoint(points, used, 0, rnd.next(-12, 12));
            }
        }
    } else if (mode == 2) {
        int pivots = rnd.next(1, 6);
        for (int i = 0; i < pivots; ++i) {
            long long px = rnd.next(-20, 20);
            long long py = rnd.next(-20, 20);
            long long ax = rnd.next(-5, 5);
            long long ay = rnd.next(-5, 5);
            if (ax == 0 && ay == 0) {
                ax = 1;
            }
            addPoint(points, used, px, py);
            addPoint(points, used, px + ax, py + ay);
            addPoint(points, used, px - ay, py + ax);
        }
        while ((int)points.size() < 3) {
            addPoint(points, used, rnd.next(-10, 10), rnd.next(-10, 10));
        }
    } else if (mode == 3) {
        int n = rnd.next(3, 35);
        while ((int)points.size() < n) {
            addPoint(points, used, rnd.next(-30, 30), rnd.next(-30, 30));
        }
    } else {
        int n = rnd.next(3, 20);
        long long base = rnd.next(999999950LL, 1000000000LL);
        addPoint(points, used, -1000000000LL, -1000000000LL);
        addPoint(points, used, 1000000000LL, 1000000000LL);
        addPoint(points, used, -1000000000LL, 1000000000LL);
        while ((int)points.size() < n) {
            addPoint(points, used, rnd.next(-base, base), rnd.next(-base, base));
        }
    }

    shuffle(points.begin(), points.end());
    println((int)points.size());
    for (const Point& p : points) {
        println(p.first, p.second);
    }

    return 0;
}
