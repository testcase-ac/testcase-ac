#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    set<pair<int, int>> points;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-1000, 1000, "X_i");
        inf.readSpace();
        int y = inf.readInt(-1000, 1000, "Y_i");
        inf.readEoln();

        // CHECK: the statement describes one image entry per star position.
        ensuref(points.insert({x, y}).second,
                "duplicate star position at line %d: (%d, %d)", i + 2, x, y);
    }

    inf.readEof();
}
