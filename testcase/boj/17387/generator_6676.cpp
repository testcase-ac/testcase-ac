#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

struct P { int x, y; };

int ccw(const P &a, const P &b, const P &c) {
    ll v = ll(b.x - a.x) * (c.y - a.y) - ll(b.y - a.y) * (c.x - a.x);
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}

bool onBox(int a1, int a2, int b1, int b2) {
    if (a1 > a2) swap(a1, a2);
    if (b1 > b2) swap(b1, b2);
    return max(a1, b1) <= min(a2, b2);
}

bool segIntersect(const P &a, const P &b, const P &c, const P &d) {
    int c1 = ccw(a, b, c);
    int c2 = ccw(a, b, d);
    int c3 = ccw(c, d, a);
    int c4 = ccw(c, d, b);
    if (ll(c1) * c2 <= 0 && ll(c3) * c4 <= 0) {
        return onBox(a.x, b.x, c.x, d.x) && onBox(a.y, b.y, c.y, d.y);
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose scenario
    int scen = rnd.next(0, 5);
    P p1, p2, p3, p4;

    if (scen == 0) {
        // Proper intersection at interior
        int xi = rnd.next(-100, 100), yi = rnd.next(-100, 100);
        // direction 1
        int dx1, dy1;
        do { dx1 = rnd.next(-10, 10); dy1 = rnd.next(-10, 10); }
        while (dx1 == 0 && dy1 == 0);
        // direction 2 non-parallel
        int dx2, dy2;
        do { dx2 = rnd.next(-10, 10); dy2 = rnd.next(-10, 10); }
        while (dx2 == 0 && dy2 == 0 || ll(dx1)*dy2 == ll(dx2)*dy1);
        int t1a = rnd.next(-20, -1), t1b = rnd.next(1, 20);
        int t2a = rnd.next(-20, -1), t2b = rnd.next(1, 20);
        p1 = { xi + dx1 * t1a, yi + dy1 * t1a };
        p2 = { xi + dx1 * t1b, yi + dy1 * t1b };
        p3 = { xi + dx2 * t2a, yi + dy2 * t2a };
        p4 = { xi + dx2 * t2b, yi + dy2 * t2b };
    }
    else if (scen == 1) {
        // Non-intersecting, non-collinear: rejection sampling
        int tries = 0;
        do {
            p1 = { rnd.next(-100,100), rnd.next(-100,100) };
            do {
                p2 = { rnd.next(-100,100), rnd.next(-100,100) };
            } while (p2.x == p1.x && p2.y == p1.y);
            p3 = { rnd.next(-100,100), rnd.next(-100,100) };
            do {
                p4 = { rnd.next(-100,100), rnd.next(-100,100) };
            } while ((p4.x == p3.x && p4.y == p3.y));
            tries++;
            if (tries > 10000) break;
        } while (segIntersect(p1,p2,p3,p4));
    }
    else if (scen == 2) {
        // Touching at an endpoint
        p1 = { rnd.next(-100,100), rnd.next(-100,100) };
        do {
            p2 = { rnd.next(-100,100), rnd.next(-100,100) };
        } while (p2.x == p1.x && p2.y == p1.y);
        // choose one endpoint of seg1
        P endp = rnd.next(0,1) ? p1 : p2;
        // other endpoint random but distinct
        do {
            p4 = { rnd.next(-100,100), rnd.next(-100,100) };
        } while (p4.x == endp.x && p4.y == endp.y);
        p3 = endp;
    }
    else if (scen == 3) {
        // Collinear overlapping
        int dx, dy;
        do { dx = rnd.next(-5,5); dy = rnd.next(-5,5); } while (dx==0 && dy==0);
        int k = rnd.next(3, 10);
        int x0 = rnd.next(-50,50), y0 = rnd.next(-50,50);
        p1 = { x0, y0 };
        p2 = { x0 + dx*k, y0 + dy*k };
        int t3 = rnd.next(1, k-2);
        int t4 = rnd.next(t3+1, k-1);
        p3 = { x0 + dx*t3, y0 + dy*t3 };
        p4 = { x0 + dx*t4, y0 + dy*t4 };
    }
    else if (scen == 4) {
        // Collinear touching at one endpoint
        int dx, dy;
        do { dx = rnd.next(-5,5); dy = rnd.next(-5,5); } while (dx==0 && dy==0);
        int k = rnd.next(2, 10);
        int x0 = rnd.next(-50,50), y0 = rnd.next(-50,50);
        p1 = { x0, y0 };
        p2 = { x0 + dx*k, y0 + dy*k };
        bool useLeft = rnd.next(0,1);
        if (useLeft) {
            // seg2 touches at p1
            p3 = p1;
            int t = rnd.next(1, k-1);
            p4 = { x0 + dx*t, y0 + dy*t };
        } else {
            // seg2 touches at p2
            p4 = p2;
            int t = rnd.next(1, k-1);
            p3 = { x0 + dx*t, y0 + dy*t };
        }
    }
    else { // scen == 5
        // Collinear non-overlapping
        int dx, dy;
        do { dx = rnd.next(-5,5); dy = rnd.next(-5,5); } while (dx==0 && dy==0);
        int k = rnd.next(3, 10);
        int x0 = rnd.next(-50,50), y0 = rnd.next(-50,50);
        p1 = { x0, y0 };
        p2 = { x0 + dx*k, y0 + dy*k };
        // place seg2 entirely before p1
        int t3 = rnd.next(-k-10, -k-1);
        int t4 = rnd.next(-k-1, -1);
        p3 = { x0 + dx*t3, y0 + dy*t3 };
        p4 = { x0 + dx*t4, y0 + dy*t4 };
    }

    // Output
    println(p1.x, p1.y, p2.x, p2.y);
    println(p3.x, p3.y, p4.x, p4.y);
    return 0;
}
