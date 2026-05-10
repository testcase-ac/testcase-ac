#include "testlib.h"
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // 2. Read N points, check bounds and uniqueness
    set<pair<int, int>> points;
    for (int i = 1; i <= N; ++i) {
        int x = inf.readInt(-100000000, 100000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-100000000, 100000000, "y_i");
        inf.readEoln();

        pair<int, int> pt = make_pair(x, y);
        ensuref(points.count(pt) == 0, "Duplicate point detected at line %d: (%d, %d)", i + 1, x, y);
        points.insert(pt);
    }

    inf.readEof();
}
