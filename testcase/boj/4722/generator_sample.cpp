#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

Point randomPoint(int lo = -1000, int hi = 1000) {
    return {rnd.next(lo, hi), rnd.next(lo, hi)};
}

vector<Point> randomCloud(int n) {
    vector<Point> points;
    for (int i = 0; i < n; ++i) {
        points.push_back(randomPoint());
    }
    return points;
}

vector<Point> duplicatedCluster(int n) {
    vector<Point> base;
    int baseCount = rnd.next(1, min(n, 4));
    for (int i = 0; i < baseCount; ++i) {
        base.push_back(randomPoint(-20, 20));
    }

    vector<Point> points;
    for (int i = 0; i < n; ++i) {
        points.push_back(rnd.any(base));
    }
    return points;
}

vector<Point> collinearCase(int n) {
    vector<Point> points;
    int axis = rnd.next(0, 2);
    int fixed = rnd.next(-1000, 1000);
    int step = rnd.next(1, max(1, 2000 / max(1, n - 1)));
    int start = rnd.next(-1000, 1000 - step * (n - 1));

    for (int i = 0; i < n; ++i) {
        int moving = start + step * i;
        if (axis == 0) {
            points.push_back({moving, fixed});
        } else {
            points.push_back({fixed, moving});
        }
    }
    return points;
}

vector<Point> gridCase(int n) {
    vector<Point> candidates;
    int width = rnd.next(2, 5);
    int height = rnd.next(2, 5);
    int x0 = rnd.next(-30, 20);
    int y0 = rnd.next(-30, 20);
    int dx = rnd.next(1, 12);
    int dy = rnd.next(1, 12);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            candidates.push_back({x0 + x * dx, y0 + y * dy});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    candidates.resize(n);
    return candidates;
}

vector<Point> rectangleCase() {
    int x1 = rnd.next(-1000, 990);
    int y1 = rnd.next(-1000, 990);
    int x2 = rnd.next(x1 + 1, 1000);
    int y2 = rnd.next(y1 + 1, 1000);

    vector<Point> points = {{x1, y1}, {x1, y2}, {x2, y1}, {x2, y2}};
    if (rnd.next(0, 1)) {
        points.push_back({(x1 + x2) / 2, (y1 + y2) / 2});
    }
    return points;
}

vector<Point> extremeCase(int n) {
    vector<Point> corners = {
        {-1000, -1000}, {-1000, 1000}, {1000, -1000}, {1000, 1000},
        {-1000, 0}, {1000, 0}, {0, -1000}, {0, 1000}
    };

    shuffle(corners.begin(), corners.end());
    corners.resize(min(n, (int)corners.size()));
    while ((int)corners.size() < n) {
        corners.push_back(randomPoint(-1000, 1000));
    }
    return corners;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(3, 7);
    for (int tc = 0; tc < cases; ++tc) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(2, 14);
        vector<Point> points;

        if (mode == 0) {
            points = randomCloud(n);
        } else if (mode == 1) {
            points = duplicatedCluster(n);
        } else if (mode == 2) {
            points = collinearCase(n);
        } else if (mode == 3) {
            n = rnd.next(4, 12);
            points = gridCase(n);
        } else if (mode == 4) {
            points = rectangleCase();
        } else {
            points = extremeCase(n);
        }

        shuffle(points.begin(), points.end());
        println((int)points.size());
        for (const Point& p : points) {
            println(p.first, p.second);
        }
    }

    println(0);
    return 0;
}
