#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 10, "n");
    inf.readEoln();

    vector<pair<int, int>> points;
    set<pair<int, int>> seen;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-1000000, 1000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-1000000, 1000000, "y_i");
        inf.readEoln();

        pair<int, int> point = {x, y};
        ensuref(seen.insert(point).second,
                "duplicate point at index %d: (%d, %d)", i + 1, x, y);
        points.push_back(point);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                long long x1 = points[j].first - points[i].first;
                long long y1 = points[j].second - points[i].second;
                long long x2 = points[k].first - points[i].first;
                long long y2 = points[k].second - points[i].second;
                ensuref(x1 * y2 != x2 * y1,
                        "collinear points at indices %d, %d, %d",
                        i + 1, j + 1, k + 1);
            }
        }
    }

    inf.readEof();
}
