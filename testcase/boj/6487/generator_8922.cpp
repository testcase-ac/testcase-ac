#include "testlib.h"
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;

struct Pt {
    int x, y;
};

struct LineCase {
    int x1, y1, x2, y2;
    int x3, y3, x4, y4;
};

long long cross(const Pt& a, const Pt& b) {
    return 1LL * a.x * b.y - 1LL * a.y * b.x;
}

bool isParallel(const Pt& a1, const Pt& a2, const Pt& b1, const Pt& b2) {
    Pt v1{a2.x - a1.x, a2.y - a1.y};
    Pt v2{b2.x - b1.x, b2.y - b1.y};
    return cross(v1, v2) == 0;
}

bool computeIntersection(const Pt& a1, const Pt& a2,
                         const Pt& b1, const Pt& b2,
                         double& x, double& y) {
    double A1 = (double)a2.y - a1.y;
    double B1 = (double)a1.x - a2.x;
    double C1 = A1 * a1.x + B1 * a1.y;

    double A2 = (double)b2.y - b1.y;
    double B2 = (double)b1.x - b2.x;
    double C2 = A2 * b1.x + B2 * b1.y;

    double det = A1 * B2 - A2 * B1;
    if (fabs(det) < 1e-12) return false;

    x = (B2 * C1 - B1 * C2) / det;
    y = (A1 * C2 - A2 * C1) / det;
    return true;
}

bool isInteger(double z) {
    long long r = (z >= 0.0 ? (long long)(z + 0.5) : (long long)(z - 0.5));
    return fabs(z - (double)r) < 1e-6;
}

// Integer intersection, general position (not necessarily axis-aligned)
void genIntPointCase(LineCase &cs, bool big = false) {
    vector<Pt> dirs = { {1,0},{0,1},{1,1},{1,2},{2,1},{-1,1},{1,-1},{2,-1},{-2,1} };

    int lo = big ? -900 : -5;
    int hi = big ?  900 :  5;

    while (true) {
        Pt P{ rnd.next(lo, hi), rnd.next(lo, hi) };
        Pt d1 = rnd.any(dirs);
        Pt d2 = rnd.any(dirs);
        while (cross(d1, d2) == 0) d2 = rnd.any(dirs);

        Pt p1 = P;
        Pt p2{ P.x + d1.x, P.y + d1.y };
        Pt p3{ P.x + d2.x, P.y + d2.y };
        Pt p4{ P.x + 2 * d2.x, P.y + 2 * d2.y };

        if (p2.x < -1000 || p2.x > 1000 || p2.y < -1000 || p2.y > 1000) continue;
        if (p3.x < -1000 || p3.x > 1000 || p3.y < -1000 || p3.y > 1000) continue;
        if (p4.x < -1000 || p4.x > 1000 || p4.y < -1000 || p4.y > 1000) continue;

        cs.x1 = p1.x; cs.y1 = p1.y;
        cs.x2 = p2.x; cs.y2 = p2.y;
        cs.x3 = p3.x; cs.y3 = p3.y;
        cs.x4 = p4.x; cs.y4 = p4.y;
        return;
    }
}

// Intersection with non-integer coordinates
void genNonIntPointCase(LineCase &cs) {
    for (int iter = 0; iter < 1000; ++iter) {
        Pt a1{ rnd.next(-7, 7), rnd.next(-7, 7) };
        Pt a2{ rnd.next(-7, 7), rnd.next(-7, 7) };
        if (a1.x == a2.x && a1.y == a2.y) continue;

        Pt b1{ rnd.next(-7, 7), rnd.next(-7, 7) };
        Pt b2{ rnd.next(-7, 7), rnd.next(-7, 7) };
        if (b1.x == b2.x && b1.y == b2.y) continue;

        if (isParallel(a1, a2, b1, b2)) continue;

        double x, y;
        if (!computeIntersection(a1, a2, b1, b2, x, y)) continue;

        if (isInteger(x) && isInteger(y)) continue;

        cs.x1 = a1.x; cs.y1 = a1.y;
        cs.x2 = a2.x; cs.y2 = a2.y;
        cs.x3 = b1.x; cs.y3 = b1.y;
        cs.x4 = b2.x; cs.y4 = b2.y;
        return;
    }
    // Fallback: just use an integer intersection case
    genIntPointCase(cs, false);
}

// Parallel, non-coincident lines
void genParallelCase(LineCase &cs, bool big = false) {
    vector<Pt> dirs = { {1,0},{0,1},{1,1},{1,2},{2,1},{-1,1},{1,-1},{2,-1},{-2,1} };
    int lo = big ? -900 : -5;
    int hi = big ?  900 :  5;

    while (true) {
        Pt P1{ rnd.next(lo, hi), rnd.next(lo, hi) };
        Pt v = rnd.any(dirs);
        Pt P2{ P1.x + v.x, P1.y + v.y };

        Pt perp{ -v.y, v.x };
        int t = rnd.next(1, 3);
        Pt n{ perp.x * t, perp.y * t };

        Pt P3{ P1.x + n.x, P1.y + n.y };
        Pt P4{ P2.x + n.x, P2.y + n.y };

        if (P2.x < -1000 || P2.x > 1000 || P2.y < -1000 || P2.y > 1000) continue;
        if (P3.x < -1000 || P3.x > 1000 || P3.y < -1000 || P3.y > 1000) continue;
        if (P4.x < -1000 || P4.x > 1000 || P4.y < -1000 || P4.y > 1000) continue;

        cs.x1 = P1.x; cs.y1 = P1.y;
        cs.x2 = P2.x; cs.y2 = P2.y;
        cs.x3 = P3.x; cs.y3 = P3.y;
        cs.x4 = P4.x; cs.y4 = P4.y;
        return;
    }
}

// Coincident lines (LINE)
void genCoincidentCase(LineCase &cs, bool big = false) {
    vector<Pt> dirs = { {1,0},{0,1},{1,1},{1,2},{2,1},{-1,1},{1,-1},{2,-1},{-2,1} };
    int lo = big ? -900 : -5;
    int hi = big ?  900 :  5;

    while (true) {
        Pt P1{ rnd.next(lo, hi), rnd.next(lo, hi) };
        Pt v = rnd.any(dirs);
        Pt P2{ P1.x + v.x, P1.y + v.y };

        int t3 = rnd.next(-2, 3);
        int t4 = rnd.next(-2, 3);
        if (t3 == t4) continue;

        Pt P3{ P1.x + t3 * v.x, P1.y + t3 * v.y };
        Pt P4{ P1.x + t4 * v.x, P1.y + t4 * v.y };

        if (P3.x < -1000 || P3.x > 1000 || P3.y < -1000 || P3.y > 1000) continue;
        if (P4.x < -1000 || P4.x > 1000 || P4.y < -1000 || P4.y > 1000) continue;

        cs.x1 = P1.x; cs.y1 = P1.y;
        cs.x2 = P2.x; cs.y2 = P2.y;
        cs.x3 = P3.x; cs.y3 = P3.y;
        cs.x4 = P4.x; cs.y4 = P4.y;
        return;
    }
}

// Vertical & horizontal intersection (axis-aligned), optionally with big coordinates
void genVertHorizCase(LineCase &cs, bool big = false) {
    int lo = big ? -900 : -5;
    int hi = big ?  900 :  5;

    int x = rnd.next(lo, hi);
    int y = rnd.next(lo, hi);

    if (y == 1000) y = 999;
    if (x == 1000) x = 999;
    if (y == -1000) y = -999;
    if (x == -1000) x = -999;

    // Line 1: vertical through (x, y)
    cs.x1 = x; cs.y1 = y;
    cs.x2 = x; cs.y2 = y + 1;

    // Line 2: horizontal through (x, y)
    cs.x3 = x;     cs.y3 = y;
    cs.x4 = x + 1; cs.y4 = y;
}

void genRandomCase(LineCase &cs) {
    int type = rnd.next(0, 3); // 0:int, 1:nonint, 2:parallel, 3:coincident
    bool big = (rnd.next(0, 4) == 0); // 1/5 chance of bigger coordinates

    if (type == 0) {
        genIntPointCase(cs, big);
    } else if (type == 1) {
        genNonIntPointCase(cs);
    } else if (type == 2) {
        genParallelCase(cs, big);
    } else {
        genCoincidentCase(cs, big);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(5, 10);
    vector<LineCase> cases;
    cases.reserve(T);

    LineCase cs;

    // 1) Integer intersection, general position
    genIntPointCase(cs, false);
    cases.push_back(cs);

    if ((int)cases.size() < T) {
        // 2) Non-integer intersection
        genNonIntPointCase(cs);
        cases.push_back(cs);
    }
    if ((int)cases.size() < T) {
        // 3) Parallel, no intersection
        genParallelCase(cs, false);
        cases.push_back(cs);
    }
    if ((int)cases.size() < T) {
        // 4) Coincident lines
        genCoincidentCase(cs, false);
        cases.push_back(cs);
    }
    if ((int)cases.size() < T) {
        // 5) Axis-aligned (vertical & horizontal) intersection, small
        genVertHorizCase(cs, false);
        cases.push_back(cs);
    }
    if ((int)cases.size() < T) {
        // 6) Axis-aligned intersection with larger coordinates (if there is room)
        genVertHorizCase(cs, true);
        cases.push_back(cs);
    }

    // Fill remaining with random diverse cases
    while ((int)cases.size() < T) {
        genRandomCase(cs);
        cases.push_back(cs);
    }

    println(T);
    for (const auto &c : cases) {
        printf("%d %d %d %d %d %d %d %d\n",
               c.x1, c.y1, c.x2, c.y2, c.x3, c.y3, c.x4, c.y4);
    }

    return 0;
}
