#include "testlib.h"

#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "N");
    inf.readEoln();

    vector<pair<int, int>> points;
    points.reserve(3 * n);
    set<pair<int, int>> seen;

    for (int i = 0; i < 3 * n; ++i) {
        int x = inf.readInt(-1000000, 1000000, "x");
        inf.readSpace();
        int y = inf.readInt(-1000000, 1000000, "y");
        inf.readEoln();

        ensuref(seen.insert({x, y}).second,
                "duplicate point at index %d: (%d, %d)", i + 1, x, y);
        points.push_back({x, y});
    }

    for (int i = 0; i < 3 * n; ++i) {
        set<pair<int, int>> slopes;
        for (int j = i + 1; j < 3 * n; ++j) {
            int dx = points[j].first - points[i].first;
            int dy = points[j].second - points[i].second;
            int g = gcd(abs(dx), abs(dy));
            dx /= g;
            dy /= g;
            if (dx < 0 || (dx == 0 && dy < 0)) {
                dx = -dx;
                dy = -dy;
            }

            ensuref(slopes.insert({dx, dy}).second,
                    "points %d, %d, and another previous point are collinear",
                    i + 1, j + 1);
        }
    }

    inf.readEof();
    return 0;
}
