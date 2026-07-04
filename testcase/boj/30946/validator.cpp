#include "testlib.h"

#include <cstdlib>
#include <string>
#include <utility>
#include <vector>
using namespace std;

long long cross(const pair<int, int>& a, const pair<int, int>& b, const pair<int, int>& c) {
    long long abx = b.first - a.first;
    long long aby = b.second - a.second;
    long long acx = c.first - a.first;
    long long acy = c.second - a.second;
    return abx * acy - aby * acx;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50, "N");
    inf.readEoln();

    string s = inf.readToken("[BG]{2,50}", "S");
    inf.readEoln();
    ensuref((int)s.size() == n, "S length must be N");

    int boys = 0;
    int girls = 0;
    for (char c : s) {
        if (c == 'B') {
            ++boys;
        } else {
            ++girls;
        }
    }
    ensuref(boys % 2 == 0, "number of boys must be even");
    ensuref(girls % 2 == 0, "number of girls must be even");

    vector<pair<int, int>> p(n);
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-10000, 10000, "X_i");
        inf.readSpace();
        int y = inf.readInt(-10000, 10000, "Y_i");
        inf.readEoln();
        p[i] = {x, y};
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ensuref(p[i] != p[j], "duplicate point at indices %d and %d", i + 1, j + 1);
        }
    }

    // CHECK: The bounds explicitly allow N = 2, although a strictly convex polygon needs at least 3 points.
    if (n >= 3) {
        long long direction = 0;
        for (int i = 0; i < n; ++i) {
            long long turn = cross(p[i], p[(i + 1) % n], p[(i + 2) % n]);
            ensuref(turn != 0, "consecutive points %d, %d, %d are collinear",
                    i + 1, (i + 1) % n + 1, (i + 2) % n + 1);
            if (direction == 0) {
                direction = turn > 0 ? 1 : -1;
            } else {
                ensuref((turn > 0 ? 1 : -1) == direction,
                        "polygon is not strictly convex at point %d", (i + 1) % n + 1);
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    long long area = cross(p[i], p[j], p[k]);
                    ensuref(area != 0, "points %d, %d, %d are collinear", i + 1, j + 1, k + 1);
                    ensuref((area > 0 ? 1 : -1) == direction,
                            "points are not listed in convex perimeter order");
                }
            }
        }
    }

    inf.readEof();
}
