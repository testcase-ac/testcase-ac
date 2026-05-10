#include "testlib.h"
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read n
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // 2. Read p
    int p = inf.readInt(20, 100, "p");
    inf.readEoln();

    // 3. Read n points, all distinct, 0 <= x, y <= 1e9
    set<pair<int, int>> points;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(0, 1000000000, "x");
        inf.readSpace();
        int y = inf.readInt(0, 1000000000, "y");
        inf.readEoln();

        pair<int, int> pt = make_pair(x, y);
        ensuref(points.count(pt) == 0, "Duplicate point at index %d: (%d, %d)", i+1, x, y);
        points.insert(pt);
    }

    inf.readEof();
}
