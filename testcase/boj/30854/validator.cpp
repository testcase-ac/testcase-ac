#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(4, 100000, "m");
    inf.readSpace();
    int n = inf.readInt(0, 100000, "n");
    inf.readEoln();
    ensuref(m % 2 == 0, "m must be even, found %d", m);

    vector<long long> v = inf.readLongs(m, 0LL, 1000000LL, "v");
    inf.readEoln();

    ensuref(v.front() == 0LL, "v1 must be 0, found %lld", v.front());
    ensuref(v.back() == 0LL, "v_m must be 0, found %lld", v.back());

    int spans = m / 2 - 1;
    vector<long long> xs(spans + 1);
    vector<long long> heights(spans);
    for (int i = 0; i <= spans; ++i) {
        xs[i] = v[2 * i];
        if (i > 0) {
            ensuref(xs[i - 1] < xs[i],
                    "vertical edge x-coordinates must be strictly increasing: x_%d=%lld, x_%d=%lld",
                    i, xs[i - 1], i + 1, xs[i]);
        }
    }
    for (int i = 0; i < spans; ++i) {
        heights[i] = v[2 * i + 1];
        ensuref(1 <= heights[i] && heights[i] <= 1000000LL,
                "upper horizontal edge y-coordinate %d must be positive, found %lld",
                i + 1, heights[i]);
    }

    for (int i = 0; i < n; i++) {
        long long x = inf.readLong(0LL, 1000000LL, "x");
        inf.readSpace();
        long long y = inf.readLong(0LL, 1000000LL, "y");
        inf.readEoln();

        ensuref(xs.front() <= x && x <= xs.back(),
                "point %d x-coordinate %lld is outside farm x-range [%lld, %lld]",
                i + 1, x, xs.front(), xs.back());

        auto it = lower_bound(xs.begin(), xs.end(), x);
        long long maxY = 0;
        if (it != xs.end() && *it == x) {
            int idx = int(it - xs.begin());
            if (idx > 0) {
                maxY = max(maxY, heights[idx - 1]);
            }
            if (idx < spans) {
                maxY = max(maxY, heights[idx]);
            }
        } else {
            int right = int(it - xs.begin());
            ensuref(0 < right && right <= spans,
                    "point %d x-coordinate %lld is not covered by any farm span",
                    i + 1, x);
            maxY = heights[right - 1];
        }
        ensuref(y <= maxY,
                "point %d (%lld, %lld) is outside farm boundary; maximum y at x=%lld is %lld",
                i + 1, x, y, x, maxY);
    }

    inf.readEof();
    return 0;
}
