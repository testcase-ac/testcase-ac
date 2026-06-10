#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

struct Case {
    double r;
    double h;
    double d1;
    double a1;
    double d2;
    double a2;
};

double realIn(double lo, double hi) {
    return lo + (hi - lo) * rnd.next();
}

double angleNear(double center, double radius) {
    double value = center + realIn(-radius, radius);
    while (value < 0.0) value += 360.0;
    while (value >= 360.0) value -= 360.0;
    return value;
}

Case makeCase(int mode) {
    double r = realIn(0.1, 30.0);
    double h = realIn(0.1, 30.0);

    if (mode == 1) {
        r = realIn(0.1, 1.0);
        h = realIn(20.0, 100.0);
    } else if (mode == 2) {
        r = realIn(20.0, 100.0);
        h = realIn(0.1, 1.0);
    } else if (mode == 5) {
        r = realIn(1e5, 1e8);
        h = realIn(1e5, 1e8);
    }

    double slant = hypot(r, h);
    double d1 = realIn(0.001, slant);
    double d2 = realIn(0.001, slant);
    double a1 = realIn(0.0, 360.0);
    double a2 = realIn(0.0, 360.0);

    if (mode == 0) {
        a2 = a1;
    } else if (mode == 1) {
        a1 = angleNear(0.0, 0.2);
        a2 = angleNear(360.0, 0.2);
    } else if (mode == 2) {
        a2 = angleNear(a1 + 180.0, 0.5);
    } else if (mode == 3) {
        d1 = realIn(max(0.001, slant * 0.95), slant);
        d2 = realIn(max(0.001, slant * 0.95), slant);
    } else if (mode == 4) {
        d1 = realIn(0.001, min(slant, 0.05));
        d2 = realIn(0.001, slant);
    }

    d1 = min(d1, slant);
    d2 = min(d2, slant);
    if (a1 >= 360.0) a1 = nextafter(360.0, 0.0);
    if (a2 >= 360.0) a2 = nextafter(360.0, 0.0);
    return {r, h, d1, a1, d2, a2};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCaseCount = rnd.next(4, 12);
    vector<Case> cases;
    for (int i = 0; i < testCaseCount; ++i) {
        cases.push_back(makeCase(i % 6));
    }
    shuffle(cases.begin(), cases.end());

    for (const Case& tc : cases) {
        printf("%.6f %.6f %.6f %.6f %.6f %.6f\n", tc.r, tc.h, tc.d1, tc.a1, tc.d2, tc.a2);
    }

    return 0;
}
