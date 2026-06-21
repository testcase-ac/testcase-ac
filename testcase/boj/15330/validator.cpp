#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

long long cross(const pair<int, int>& a,
                const pair<int, int>& b,
                const pair<int, int>& c) {
    long long abx = b.first - a.first;
    long long aby = b.second - a.second;
    long long acx = c.first - a.first;
    long long acy = c.second - a.second;
    return abx * acy - aby * acx;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(2, 16, "m");
    inf.readEoln();
    ensuref(m % 2 == 0, "m must be even: %d", m);

    vector<pair<int, int>> points;
    set<pair<int, int>> seen;
    for (int i = 0; i < m; ++i) {
        int x = inf.readInt(-1000, 1000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-1000, 1000, "y_i");
        inf.readEoln();

        pair<int, int> point = {x, y};
        ensuref(seen.insert(point).second,
                "duplicate point at index %d: (%d, %d)",
                i + 1,
                x,
                y);
        points.push_back(point);
    }

    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            for (int k = j + 1; k < m; ++k) {
                ensuref(cross(points[i], points[j], points[k]) != 0,
                        "points %d, %d, and %d are collinear",
                        i + 1,
                        j + 1,
                        k + 1);
            }
        }
    }

    inf.readEof();
}
