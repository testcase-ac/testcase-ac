#include "testlib.h"
#include <set>
#include <utility>
#include <vector>
using namespace std;

using Point = pair<int, int>;

long long dist2(const Point& p) {
    return 1LL * p.first * p.first + 1LL * p.second * p.second;
}

long long dist2(const Point& a, const Point& b) {
    long long dx = 1LL * a.first - b.first;
    long long dy = 1LL * a.second - b.second;
    return dx * dx + dy * dy;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int rs = inf.readInt(1, 9999, "R_s");
        inf.readSpace();
        int rh = inf.readInt(rs + 1, 10000, "R_h");
        inf.readEoln();

        vector<Point> stones;
        set<long long> centerDistances;

        int n = inf.readInt(0, 8, "N");
        inf.readEoln();
        for (int i = 0; i < n; ++i) {
            int x = inf.readInt(-20000, 20000, "X_i");
            inf.readSpace();
            int y = inf.readInt(-20000, 20000, "Y_i");
            inf.readEoln();

            Point p{x, y};
            ensuref(centerDistances.insert(dist2(p)).second,
                    "stone %d has a duplicate distance from the house center", i + 1);
            stones.push_back(p);
        }

        int m = inf.readInt(0, 8, "M");
        inf.readEoln();
        for (int i = 0; i < m; ++i) {
            int z = inf.readInt(-20000, 20000, "Z_i");
            inf.readSpace();
            int w = inf.readInt(-20000, 20000, "W_i");
            inf.readEoln();

            Point p{z, w};
            ensuref(centerDistances.insert(dist2(p)).second,
                    "yellow stone %d has a duplicate distance from the house center", i + 1);
            stones.push_back(p);
        }

        long long minCenterDistance = 2LL * rs;
        minCenterDistance *= minCenterDistance;
        for (int i = 0; i < (int)stones.size(); ++i) {
            for (int j = i + 1; j < (int)stones.size(); ++j) {
                ensuref(dist2(stones[i], stones[j]) >= minCenterDistance,
                        "stones %d and %d overlap", i + 1, j + 1);
            }
        }
    }

    inf.readEof();
    return 0;
}
