#include "testlib.h"
using namespace std;

struct Point {
    double x, y;
};

double randomNonZeroAbs() {
    // Generate a positive non-zero value with small/medium magnitude and possible decimals
    int type = rnd.next(0, 2);
    if (type == 0) {
        // Small integer [1..9]
        return rnd.next(1, 9);
    } else if (type == 1) {
        // Integer with one decimal, like 3.7
        int ip = rnd.next(0, 9);
        int fp = rnd.next(1, 9);
        double v = ip + fp / 10.0;
        if (v == 0.0) v = 0.5;
        return v;
    } else {
        // Larger integer [10..30]
        return rnd.next(10, 30);
    }
}

double randomSignedNonZero(int sign) {
    double v = randomNonZeroAbs();
    return (sign >= 0 ? v : -v);
}

double randomNearZeroSigned() {
    // Very small but non-zero: k * 1e-6, k in [1..9]
    int k = rnd.next(1, 9);
    double v = k * 1e-6;
    if (rnd.next(0, 1) == 0) v = -v;
    return v;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> pts;

    // Ensure all quadrants and both axes are covered at least once
    // Q1: x > 0, y > 0
    pts.push_back({ randomSignedNonZero(+1), randomSignedNonZero(+1) });
    // Q2: x < 0, y > 0
    pts.push_back({ randomSignedNonZero(-1), randomSignedNonZero(+1) });
    // Q3: x < 0, y < 0
    pts.push_back({ randomSignedNonZero(-1), randomSignedNonZero(-1) });
    // Q4: x > 0, y < 0
    pts.push_back({ randomSignedNonZero(+1), randomSignedNonZero(-1) });
    // On X-axis: y = 0, x != 0
    pts.push_back({ randomSignedNonZero(rnd.next(0, 1) ? +1 : -1), 0.0 });
    // On Y-axis: x = 0, y != 0
    pts.push_back({ 0.0, randomSignedNonZero(rnd.next(0, 1) ? +1 : -1) });

    // Add some extra random points for variability
    int extra = rnd.next(0, 6); // total between 6 and 12
    for (int i = 0; i < extra; ++i) {
        int kind = rnd.next(0, 5);
        Point p;
        if (kind == 0) {
            // Random quadrant point
            int sx = rnd.next(0, 1) ? +1 : -1;
            int sy = rnd.next(0, 1) ? +1 : -1;
            p.x = randomSignedNonZero(sx);
            p.y = randomSignedNonZero(sy);
        } else if (kind == 1) {
            // Another X-axis point
            p.x = randomSignedNonZero(rnd.next(0, 1) ? +1 : -1);
            p.y = 0.0;
        } else if (kind == 2) {
            // Another Y-axis point
            p.x = 0.0;
            p.y = randomSignedNonZero(rnd.next(0, 1) ? +1 : -1);
        } else if (kind == 3) {
            // Very close to X-axis but not on it
            p.x = randomSignedNonZero(rnd.next(0, 1) ? +1 : -1);
            p.y = randomNearZeroSigned(); // tiny non-zero
        } else if (kind == 4) {
            // Very close to Y-axis but not on it
            p.x = randomNearZeroSigned(); // tiny non-zero
            p.y = randomSignedNonZero(rnd.next(0, 1) ? +1 : -1);
        } else {
            // Larger magnitude random quadrant
            int sx = rnd.next(0, 1) ? +1 : -1;
            int sy = rnd.next(0, 1) ? +1 : -1;
            p.x = (sx > 0 ? 1.0 : -1.0) * rnd.next(50, 200);
            p.y = (sy > 0 ? 1.0 : -1.0) * rnd.next(50, 200);
        }
        // Ensure we don't accidentally create (0,0)
        if (p.x == 0.0 && p.y == 0.0) {
            p.x = randomSignedNonZero(+1);
            p.y = randomSignedNonZero(-1);
        }
        pts.push_back(p);
    }

    shuffle(pts.begin(), pts.end());

    // Output all points
    for (const auto &p : pts) {
        println(p.x, p.y);
    }

    // Terminating line
    println(0, 0);

    return 0;
}
