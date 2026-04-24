#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // t = 0 => collinear, 1 => ccw, 2 => cw
    int t = rnd.next(0, 2);
    int x1, y1, x2, y2, x3, y3;

    if (t == 0) {
        // Generate a collinear triple by picking A, B then C = A - (B-A) or B + (B-A)
        int baseRange = rnd.next(1000, 2000);
        // Pick A
        x1 = rnd.next(-baseRange, baseRange);
        y1 = rnd.next(-baseRange, baseRange);
        // Pick B distinct from A
        do {
            x2 = rnd.next(-baseRange, baseRange);
            y2 = rnd.next(-baseRange, baseRange);
        } while (x2 == x1 && y2 == y1);
        int dx = x2 - x1;
        int dy = y2 - y1;
        // Mirror or extend
        if (rnd.next(0, 1)) {
            x3 = x1 - dx;
            y3 = y1 - dy;
        } else {
            x3 = x2 + dx;
            y3 = y2 + dy;
        }
    } else {
        // Generate a non-collinear triple
        // Hyper-parameter: small vs large coords
        bool smallCoord = rnd.next() < 0.3;
        int coordRange = smallCoord ? rnd.next(1, 5) : rnd.next(1000, 10000);
        auto cross = [&](int ax, int ay, int bx, int by, int cx, int cy) {
            long long ux = bx - ax, uy = by - ay;
            long long vx = cx - ax, vy = cy - ay;
            return ux * vy - uy * vx;
        };
        long long cr = 0;
        // Keep sampling until non-zero cross
        do {
            x1 = rnd.next(-coordRange, coordRange);
            y1 = rnd.next(-coordRange, coordRange);
            do {
                x2 = rnd.next(-coordRange, coordRange);
                y2 = rnd.next(-coordRange, coordRange);
            } while (x2 == x1 && y2 == y1);
            do {
                x3 = rnd.next(-coordRange, coordRange);
                y3 = rnd.next(-coordRange, coordRange);
            } while ((x3 == x1 && y3 == y1) || (x3 == x2 && y3 == y2));
            cr = cross(x1, y1, x2, y2, x3, y3);
        } while (cr == 0);

        // If orientation doesn't match desired, swap P2 and P3
        if ((t == 1 && cr < 0) || (t == 2 && cr > 0)) {
            swap(x2, x3);
            swap(y2, y3);
        }
    }

    // Output
    println(x1, y1);
    println(x2, y2);
    println(x3, y3);

    return 0;
}
