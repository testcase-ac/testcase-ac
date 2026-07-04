#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Rational {
    long long numerator;
    long long denominator;
};

struct Interval {
    Rational left;
    Rational right;
};

static bool lessThan(const Rational& a, const Rational& b) {
    return static_cast<__int128>(a.numerator) * b.denominator <
           static_cast<__int128>(b.numerator) * a.denominator;
}

static bool equalTo(const Rational& a, const Rational& b) {
    return static_cast<__int128>(a.numerator) * b.denominator ==
           static_cast<__int128>(b.numerator) * a.denominator;
}

static Rational shadowPoint(int x, int y, int xL, int yL) {
    return Rational{
        static_cast<long long>(yL) * x - static_cast<long long>(y) * xL,
        yL - y,
    };
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: the statement gives no test-case count bound; cap aggregate segments for practical validation.
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    int totalSegments = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(0, 100, "n");
        inf.readEoln();
        totalSegments += n;
        ensuref(totalSegments <= 100000, "sum of n exceeds practical cap: %d", totalSegments);

        int xL = inf.readInt(-100, 100, "x_L");
        inf.readSpace();
        int yL = inf.readInt(1, 1000, "y_L");
        inf.readEoln();
        ensuref(n == 0 || yL >= 2, "positive segment count requires y_L at least 2");

        set<pair<int, int>> endpoints;
        vector<Interval> shadows;

        for (int i = 1; i <= n; ++i) {
            int x = inf.readInt(-100, 100, "x_i");
            inf.readSpace();
            int y = inf.readInt(1, yL - 1, "y_i");
            inf.readSpace();
            int u = inf.readInt(-100, 100, "u_i");
            inf.readSpace();
            int v = inf.readInt(1, yL - 1, "v_i");
            inf.readEoln();

            ensuref(endpoints.insert({x, y}).second,
                    "duplicate endpoint at segment %d: (%d, %d)", i, x, y);
            ensuref(endpoints.insert({u, v}).second,
                    "duplicate endpoint at segment %d: (%d, %d)", i, u, v);

            Rational first = shadowPoint(x, y, xL, yL);
            Rational second = shadowPoint(u, v, xL, yL);
            ensuref(!equalTo(first, second), "segment %d has a point shadow", i);

            if (lessThan(second, first)) {
                swap(first, second);
            }
            shadows.push_back({first, second});
        }

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                ensuref(!equalTo(shadows[i].right, shadows[j].left) &&
                            !equalTo(shadows[j].right, shadows[i].left),
                        "shadows %d and %d touch at one point", i + 1, j + 1);
            }
        }
    }

    inf.readEof();
}
