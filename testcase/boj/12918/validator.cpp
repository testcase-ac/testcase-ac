#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // 2. Read N points, check constraints and uniqueness
    set<pair<int, int>> points;
    for (int i = 0; i < N; ++i) {
        int x = inf.readInt(-1000, 1000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-1000, 1000, "y_i");
        inf.readEoln();

        pair<int, int> pt = make_pair(x, y);
        ensuref(points.count(pt) == 0, "Duplicate point at index %d: (%d, %d)", i+1, x, y);
        points.insert(pt);
    }

    inf.readEof();
}
