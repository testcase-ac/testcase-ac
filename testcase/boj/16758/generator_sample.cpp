#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Circle {
    int x;
    int y;
    int r;
};

int radiusLimit(int n, int m, int x, int y) {
    return min({x - 1, y - 1, n - x, m - y});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    if (mode == 0) {
        n = rnd.next(3, 7);
        m = rnd.next(3, 7);
    } else if (mode == 1) {
        n = rnd.next(8, 25);
        m = rnd.next(8, 25);
    } else if (mode == 2) {
        n = rnd.next(3, 8);
        m = rnd.next(20, 80);
    } else if (mode == 3) {
        n = rnd.next(20, 80);
        m = rnd.next(3, 8);
    } else if (mode == 4) {
        n = rnd.next(50, 200);
        m = rnd.next(50, 200);
    } else {
        n = rnd.next(1000, 100000);
        m = rnd.next(1000, 100000);
    }

    int k = mode == 5 ? rnd.next(1, 12) : rnd.next(1, min(20, max(1, n * m / 8)));
    vector<Circle> circles;
    circles.reserve(k);

    int clusterX = rnd.next(2, n - 1);
    int clusterY = rnd.next(2, m - 1);
    for (int i = 0; i < k; ++i) {
        int x;
        int y;
        if (mode == 1 && rnd.next(0, 99) < 65) {
            x = min(n - 1, max(2, clusterX + rnd.next(-3, 3)));
            y = min(m - 1, max(2, clusterY + rnd.next(-3, 3)));
        } else {
            x = rnd.next(2, n - 1);
            y = rnd.next(2, m - 1);
        }

        int limit = radiusLimit(n, m, x, y);
        int r;
        int radiusMode = rnd.next(0, 3);
        if (radiusMode == 0) {
            r = 1;
        } else if (radiusMode == 1) {
            r = rnd.next(1, limit);
        } else if (radiusMode == 2) {
            r = max(1, limit - rnd.next(0, min(2, limit - 1)));
        } else {
            r = rnd.wnext(limit, 2) + 1;
        }
        circles.push_back({x, y, r});
    }

    println(n, m);
    println(k);
    for (const Circle& circle : circles) {
        println(circle.x, circle.y, circle.r);
    }

    return 0;
}
