#include "testlib.h"

#include <array>
#include <vector>

using namespace std;

using Point = array<int, 2>;

long long squaredDistance(const Point& a, const Point& b) {
    long long dx = a[0] - b[0];
    long long dy = a[1] - b[1];
    return dx * dx + dy * dy;
}

bool validPoints(const vector<Point>& p, int r) {
    long long touchDistanceSquared = 4LL * r * r;
    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            if (squaredDistance(p[i], p[j]) <= touchDistanceSquared) return false;
        }
    }
    return squaredDistance(p[1], p[2]) > 16LL * r * r;
}

Point randomPoint(int limit) {
    return {rnd.next(-limit, limit), rnd.next(-limit, limit)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int r = rnd.next(1, 20);
    int mode = rnd.next(5);
    vector<Point> p(3);
    int xv = 0;
    int yv = 0;

    for (int attempt = 0; attempt < 10000; ++attempt) {
        if (mode == 0) {
            p[0] = {0, 0};
            p[1] = {rnd.next(2 * r + 1, 8 * r + 30), rnd.next(-r + 1, r - 1)};
            p[2] = {p[1][0] + rnd.next(4 * r + 1, 9 * r + 40), rnd.next(-3 * r, 3 * r)};
            xv = rnd.next(20, 100);
            yv = rnd.next(-10, 10);
        } else if (mode == 1) {
            p[0] = {0, 0};
            p[2] = {rnd.next(2 * r + 1, 8 * r + 30), rnd.next(-r + 1, r - 1)};
            p[1] = {p[2][0] + rnd.next(4 * r + 1, 9 * r + 40), rnd.next(-3 * r, 3 * r)};
            xv = rnd.next(20, 100);
            yv = rnd.next(-10, 10);
        } else if (mode == 2) {
            p[0] = {rnd.next(-40, 40), rnd.next(-40, 40)};
            p[1] = {p[0][0] + rnd.next(2 * r + 1, 9 * r + 30), p[0][1] + rnd.next(3 * r + 1, 8 * r + 30)};
            p[2] = {p[0][0] + rnd.next(2 * r + 1, 9 * r + 30), p[0][1] - rnd.next(3 * r + 1, 8 * r + 30)};
            xv = rnd.next(-100, -20);
            yv = rnd.next(-30, 30);
        } else if (mode == 3) {
            p[0] = {0, 0};
            int dist = rnd.next(2 * r + 1, 10 * r + 40);
            p[1] = {dist, rnd.next(-r + 1, r - 1)};
            p[2] = {-rnd.next(4 * r + 1, 10 * r + 40), rnd.next(-4 * r, 4 * r)};
            xv = rnd.next(30, 120);
            yv = rnd.next(-15, 15);
        } else {
            p[0] = randomPoint(80);
            p[1] = randomPoint(80);
            p[2] = randomPoint(80);
            xv = rnd.next(-100, 100);
            yv = rnd.next(-100, 100);
        }

        if ((xv != 0 || yv != 0) && validPoints(p, r)) break;
    }

    println(p[0][0], p[0][1]);
    println(p[1][0], p[1][1]);
    println(p[2][0], p[2][1]);
    println(xv, yv, r);

    return 0;
}
