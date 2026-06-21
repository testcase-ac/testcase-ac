#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace {

constexpr double kPi = 3.14159265358979323846;
constexpr double kGravity = 9.81;

struct Case {
    double v0;
    double theta;
    double x1;
    double h1;
    double h2;
};

double trajectoryHeight(double v0, double theta, double x1) {
    double radians = theta * kPi / 180.0;
    double t = x1 / (v0 * cos(radians));
    return v0 * t * sin(radians) - 0.5 * kGravity * t * t;
}

double randReal(double low, double high) {
    return rnd.next(static_cast<int>(low * 1000), static_cast<int>(high * 1000)) /
           1000.0;
}

string formatNumber(double value) {
    if (value < 0.001) value = 0.001;
    if (value > 999.999) value = 999.999;

    long long scaled = llround(value * 1000.0);
    int whole = static_cast<int>(scaled / 1000);
    int frac = static_cast<int>(scaled % 1000);

    if (frac == 0) return to_string(whole);

    string tail = to_string(frac + 1000).substr(1);
    while (!tail.empty() && tail.back() == '0') tail.pop_back();
    return to_string(whole) + "." + tail;
}

Case makeSafeCase() {
    for (int attempt = 0; attempt < 200; ++attempt) {
        double v0 = randReal(12.0, 90.0);
        double theta = randReal(15.0, 75.0);
        double radians = theta * kPi / 180.0;
        double range = v0 * v0 * sin(2.0 * radians) / kGravity;
        double xLimit = min(120.0, max(2.0, range * 0.7));
        double x1 = randReal(1.0, xLimit);
        double y = trajectoryHeight(v0, theta, x1);
        if (y <= 2.5 || y >= 996.0) continue;

        double lowerMargin = randReal(1.0, min(8.0, y - 0.001));
        double upperMargin = randReal(1.0, min(8.0, 999.999 - y));
        return {v0, theta, x1, y - lowerMargin, y + upperMargin};
    }

    return {20.0, 45.0, 20.0, 9.0, 12.0};
}

Case makeNotSafeCase() {
    Case base = makeSafeCase();
    double y = trajectoryHeight(base.v0, base.theta, base.x1);

    int mode = rnd.next(4);
    if (mode == 0 && y > 2.1) {
        double h1 = randReal(max(0.001, y - 0.9), y);
        double h2 = min(999.999, h1 + randReal(1.1, 8.0));
        return {base.v0, base.theta, base.x1, h1, h2};
    }
    if (mode == 1 && y < 998.0) {
        double h2 = randReal(y, min(999.999, y + 0.9));
        double h1 = max(0.001, h2 - randReal(1.1, 8.0));
        return {base.v0, base.theta, base.x1, h1, h2};
    }
    if (mode == 2) {
        double h1 = min(998.5, max(y + 1.1, 0.001));
        return {base.v0, base.theta, base.x1, h1, min(999.999, h1 + randReal(0.1, 1.4))};
    }

    double h2 = max(0.002, min(y - 1.1, 999.999));
    double h1 = max(0.001, h2 - randReal(0.1, min(5.0, h2 - 0.001)));
    return {base.v0, base.theta, base.x1, h1, h2};
}

Case makeBoundaryCase() {
    vector<Case> cases = {
        {0.1, 0.1, 0.1, 0.1, 0.2},
        {200.0, 89.999, 999.999, 999.998, 999.999},
        {99.999, 1.0, 0.001, 0.001, 999.999},
        {1.5, 45.25, 10.0, 1.0, 2.5},
    };
    return rnd.any(cases);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 20);
    println(n);

    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(100);
        Case tc;
        if (mode < 45) {
            tc = makeSafeCase();
        } else if (mode < 90) {
            tc = makeNotSafeCase();
        } else {
            tc = makeBoundaryCase();
        }

        cout << formatNumber(tc.v0) << ' ' << formatNumber(tc.theta) << ' '
             << formatNumber(tc.x1) << ' ' << formatNumber(tc.h1) << ' '
             << formatNumber(tc.h2) << '\n';
    }

    return 0;
}
