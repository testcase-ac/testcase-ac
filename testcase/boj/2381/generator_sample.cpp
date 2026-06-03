#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

const int LIM = 1000000;

int coordNear(int center, int radius) {
    int lo = max(-LIM, center - radius);
    int hi = min(LIM, center + radius);
    return rnd.next(lo, hi);
}

void addRandomPoints(vector<Point>& points, int target, int radius = LIM) {
    while ((int)points.size() < target) {
        if (radius >= LIM) {
            points.emplace_back(rnd.next(-LIM, LIM), rnd.next(-LIM, LIM));
        } else {
            int cx = rnd.next(-LIM, LIM);
            int cy = rnd.next(-LIM, LIM);
            points.emplace_back(coordNear(cx, radius), coordNear(cy, radius));
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    vector<Point> points;

    if (mode == 0) {
        points.emplace_back(rnd.next(-LIM, LIM), rnd.next(-LIM, LIM));
    } else if (mode == 1) {
        int n = rnd.next(2, 24);
        int y = rnd.next(-LIM, LIM);
        for (int i = 0; i < n; ++i) {
            points.emplace_back(rnd.next(-LIM, LIM), y);
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 24);
        int x = rnd.next(-LIM, LIM);
        for (int i = 0; i < n; ++i) {
            points.emplace_back(x, rnd.next(-LIM, LIM));
        }
    } else if (mode == 3) {
        int n = rnd.next(2, 26);
        int base = rnd.next(-LIM / 2, LIM / 2);
        for (int i = 0; i < n; ++i) {
            int x = coordNear(base, 200000);
            int y = coordNear(x, 50);
            points.emplace_back(x, y);
        }
    } else if (mode == 4) {
        int n = rnd.next(2, 26);
        int sum = rnd.next(-LIM, LIM);
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(max(-LIM, sum - LIM), min(LIM, sum + LIM));
            int y = sum - x;
            points.emplace_back(x, y);
        }
    } else if (mode == 5) {
        points = {
            {-LIM, -LIM},
            {-LIM, LIM},
            {LIM, -LIM},
            {LIM, LIM},
        };
        addRandomPoints(points, rnd.next(4, 18), 1000);
    } else if (mode == 6) {
        int n = rnd.next(2, 30);
        int cx = rnd.next(-LIM, LIM);
        int cy = rnd.next(-LIM, LIM);
        int radius = rnd.next(0, 25);
        for (int i = 0; i < n; ++i) {
            points.emplace_back(coordNear(cx, radius), coordNear(cy, radius));
        }
    } else {
        int n = rnd.next(2, 30);
        int span = rnd.any(vector<int>{1, 10, 1000, 1000000});
        for (int i = 0; i < n; ++i) {
            int sx = rnd.any(vector<int>{-1, 1});
            int sy = rnd.any(vector<int>{-1, 1});
            points.emplace_back(sx * rnd.next(0, span), sy * rnd.next(0, span));
        }
    }

    shuffle(points.begin(), points.end());

    println((int)points.size());
    for (const auto& p : points) {
        println(p.first, p.second);
    }

    return 0;
}
