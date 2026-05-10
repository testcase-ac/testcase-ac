#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;

struct Circle {
    int x, y, r;
};

long long sqr(long long x) { return x * x; }

// Returns true if c1 and c2 intersect (touch or overlap at any point)
bool circles_intersect(const Circle& c1, const Circle& c2) {
    long long dx = c1.x - c2.x;
    long long dy = c1.y - c2.y;
    long long d2 = sqr(dx) + sqr(dy);
    long long rsum = c1.r + c2.r;
    long long rdiff = abs(c1.r - c2.r);

    // If distance between centers is less than sum of radii, they overlap/touch
    // If distance between centers is equal to sum of radii, they touch externally
    // If distance between centers is equal to abs(r1 - r2), they touch internally
    // If distance between centers is less than abs(r1 - r2), one is inside the other (possibly coincident centers)
    // But if distance between centers is 0 and radii are equal, they coincide (degenerate)
    // Problem says: "임의의 두개의 원을 선택했을 때 내접, 외접 등 교점이 존재하지 않도록 존재한다."
    // So, NO intersection (including touching), only possible inclusion or disjoint.

    // If distance between centers is less than sum of radii and greater than abs(r1 - r2), they intersect
    if (d2 < sqr(rsum) && d2 > sqr(rdiff)) return true;
    // If distance between centers is exactly sum of radii or exactly abs(r1 - r2), they touch (tangent)
    if (d2 == sqr(rsum) || d2 == sqr(rdiff)) return true;
    return false;
}

// Returns true if c2 is strictly inside c1 (not touching)
bool circle_contains(const Circle& c1, const Circle& c2) {
    long long dx = c1.x - c2.x;
    long long dy = c1.y - c2.y;
    long long d2 = sqr(dx) + sqr(dy);
    long long rdiff = c1.r - c2.r;
    // c2 is inside c1 if distance between centers + r2 < r1
    // i.e., sqrt(d2) + c2.r < c1.r
    // To avoid sqrt, (sqrt(d2) + c2.r < c1.r) <=> sqrt(d2) < c1.r - c2.r
    // <=> d2 < (c1.r - c2.r)^2, and c1.r > c2.r
    return (c1.r > c2.r) && (d2 < sqr(rdiff));
}

// Returns true if c1 and c2 are exactly the same circle (coincident)
bool circles_coincide(const Circle& c1, const Circle& c2) {
    return c1.x == c2.x && c1.y == c2.y && c1.r == c2.r;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 5000, "N");
    inf.readEoln();

    vector<Circle> circles(N);
    set<tuple<int,int,int>> uniq_circles;
    for (int i = 0; i < N; ++i) {
        int x = inf.readInt(-1000000, 1000000, "x");
        inf.readSpace();
        int y = inf.readInt(-1000000, 1000000, "y");
        inf.readSpace();
        int r = inf.readInt(1, 10000, "r");
        inf.readEoln();

        ensuref(uniq_circles.insert({x, y, r}).second, 
            "Duplicate circle detected at index %d: (%d, %d, %d)", i, x, y, r);

        circles[i] = {x, y, r};
    }

    // Check for no intersection (including tangent) between any two circles
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            ensuref(!circles_coincide(circles[i], circles[j]), 
                "Coincident circles at indices %d and %d: (%d, %d, %d)", i, j, circles[i].x, circles[i].y, circles[i].r);
            ensuref(!circles_intersect(circles[i], circles[j]),
                "Circles at indices %d and %d intersect or are tangent: (%d, %d, %d) and (%d, %d, %d)",
                i, j, circles[i].x, circles[i].y, circles[i].r, circles[j].x, circles[j].y, circles[j].r);
        }
    }

    inf.readEof();
}
